# Load general libraries
import glob
import inspect
import os
import math
import subprocess
from typing import Any, Callable, Iterable, List, Optional, Sized, Tuple, Union
import warnings

from pygments import highlight  # type: ignore
from pygments.lexers import PythonLexer  # type: ignore
from pygments.formatters import HtmlFormatter  # type: ignore
from IPython.display import display, HTML  # type: ignore

from PIL import Image  # type: ignore
import numpy as np
import pandas as pd  # type: ignore

from sklearn.model_selection import StratifiedShuffleSplit  # type: ignore

from matplotlib.offsetbox import OffsetImage, AnnotationBbox  # type: ignore
from matplotlib.figure import Figure  # type: ignore

import seaborn as sns  # type: ignore

sns.set()
warnings.simplefilter(action="ignore", category=FutureWarning)


def error_rate(solutions: pd.Series, predictions: pd.Series) -> Any:
    """
    Return the error rate between two vectors.
    """
    return (predictions != solutions).mean()


def load_images(datadir: str, pattern: str = "*.png") -> pd.Series:
    """
    Return all the images in `datadir` whose name match the pattern

    The images are returned as a `Pandas` series, with the image file
    names as indices.

    Example:

    This returns all png images in `dataset/` whose name starts
    with `a`:

        >>> images = load_images('dataset', 'a*.png')

    The names of the files serve as index:

        >>> images.index
    """
    paths = sorted(glob.glob(os.path.join(datadir, pattern)))
    images = [Image.open(path) for path in paths]
    names = [os.path.basename(path) for path in paths]
    return pd.Series(images, names)


def image_grid(
    images: List[Image.Image], columns: int = 5, titles: Optional[Iterable] = None
) -> Figure:
    """
    Return a figure holding the images arranged in a grid

    Optionally the number of columns and/or image titles can be provided.

    Example:

         >>> image_grid(images)
         >>> image_grid(images, titles=[....])

    """
    rows = math.ceil(1.0 * len(images) / columns)
    fig = Figure(figsize=(10, 10.0 * rows / columns))
    if titles is None:
        titles = range(len(images))
    for k, (img, title) in enumerate(zip(images, titles)):
        ax = fig.add_subplot(rows, columns, k + 1)
        ax.imshow(img)
        ax.tick_params(axis="both", labelsize=0, length=0)
        ax.grid(b=False)
        ax.set_xlabel(title, labelpad=-4)
    return fig


def split_data(
    X: pd.Series, Y: pd.Series, verbose: bool = False, seed: int = 0
) -> Tuple:
    """Make a 50/50 training/test data split (stratified).
    Return the indices of the split train_idx and test_idx."""
    SSS = StratifiedShuffleSplit(n_splits=1, test_size=0.5, random_state=seed)
    ((train_index, test_index),) = SSS.split(X, Y)
    if verbose:
        print("TRAIN:", train_index, "TEST:", test_index)
    return (train_index, test_index)


def make_scatter_plot(
    df: pd.DataFrame,
    images: List[Image.Image],
    train_index: Sized = [],
    test_index: Sized = [],
    filter=None,
    predicted_labels=[],
    show_diag: bool = False,
    axis="normal",
    feat=None,
    theta=None,
) -> Figure:
    """This scatter plot function allows us to show the images.

    predicted_labels can either be:
                    - None (queries shown as question marks)
                    - a vector of +-1 predicted values
                    - the string "GroundTruth" (to display the test images).
    Other optional arguments:
            show_diag: add diagonal dashed line if True.
            feat and theta: add horizontal or vertical line at position theta
            axis: make axes identical if 'square'."""
    fruit = np.array(["B", "A"])

    fig = Figure(figsize=(10, 10))
    ax = fig.add_subplot()

    nsample, nfeat = df.shape
    if len(train_index) == 0:
        train_index = range(nsample)
    # Plot training examples
    x = df.iloc[train_index, 0]
    y = df.iloc[train_index, 1]
    f = images.iloc[train_index]
    ax.scatter(x, y, s=750, marker="o", c="w")

    for x0, y0, img in zip(x, y, f):
        ab = AnnotationBbox(OffsetImage(img), (x0, y0), frameon=False)
        ax.add_artist(ab)

    # Plot test examples
    x = df.iloc[test_index, 0]
    y = df.iloc[test_index, 1]

    if len(predicted_labels) > 0 and not (predicted_labels == "GroundTruth"):
        label = (predicted_labels + 1) / 2
        ax.scatter(x, y, s=250, marker="s", color="c")
        for x0, y0, lbl in zip(x, y, label):
            ax.text(
                x0 - 0.03,
                y0 - 0.03,
                fruit[int(lbl)],
                color="w",
                fontsize=12,
                weight="bold",
            )
    elif predicted_labels == "GroundTruth":
        f = images.iloc[test_index]
        ax.scatter(x, y, s=500, marker="s", color="c")
        for x0, y0, img in zip(x, y, f):
            ab = AnnotationBbox(OffsetImage(img), (x0, y0), frameon=False)
            ax.add_artist(ab)
    else:  # Plot UNLABELED test examples
        f = images[test_index]
        ax.scatter(x, y, s=250, marker="s", c="c")
        ax.scatter(x, y, s=100, marker="$?$", c="w")

    if axis == "square":
        ax.set_aspect("equal", adjustable="box")
    ax.set_xlim(-2, 2)
    ax.set_ylim(-2, 2)
    ax.set_xlabel(f"$x_1$ = {df.columns[0]}")
    ax.set_ylabel(f"$x_2$ = {df.columns[1]}")

    # Add line on the diagonal
    if show_diag:
        ax.plot([-3, 3], [-3, 3], "k--")

    # Add separating line along one of the axes
    if theta is not None:
        if feat == 0:  # vertical line
            ax.plot([theta, theta], [-3, 3], "k--")
        else:  # horizontal line
            ax.plot([-3, 3], [theta, theta], "k--")

    return fig


def foreground_filter(
    img: Union[Image.Image, np.ndarray], theta: int = 150
) -> np.ndarray:
    """Create a black and white image outlining the foreground."""
    M = np.array(img)  # In case this is not yet a Numpy array
    G = np.min(M[:, :, 0:3], axis=2)
    F = G < theta
    return F


def transparent_background_filter(
    img: Union[Image.Image, np.ndarray], theta: int = 150
) -> Image.Image:
    """Create a cropped image with transparent background."""
    F = foreground_filter(img, theta=theta)
    M = np.array(img)
    N = np.zeros([M.shape[0], M.shape[1], 4], dtype=M.dtype)
    N[:, :, :3] = M[:, :, :3]
    N[:, :, 3] = F * 255
    return Image.fromarray(N)


def show_source(function: Callable) -> None:
    """
    Show the source code of the function, with syntax highlighting

    This is meant to be called from a Jupyter notebook.
    """
    code = inspect.getsource(function)
    lexer = PythonLexer()
    formatter = HtmlFormatter(cssclass="pygments")
    html_code = highlight(code, lexer, formatter)
    css = formatter.get_style_defs(".pygments")
    html = f"<style>{css}</style>{html_code}"
    display(HTML(html))


def run_without_error(shell_command: str) -> bool:
    """
    Run the given shell command

    Print the command ouput (even in Jupyter) and return whether the
    command ran without error (exit code 0)
    """
    status = subprocess.run(shell_command.split(), capture_output=True)
    print(status.stdout.decode())
    return status.returncode == 0
