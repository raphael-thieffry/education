##############################################################################
# Imports

import glob
import inspect
import os
import math
from numbers import Number
from typing import Callable, List, Optional, Iterable, Union, Any
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
from matplotlib.axes import Axes  # type: ignore
from matplotlib.colors import LinearSegmentedColormap  # type: ignore
import matplotlib.pyplot as plt

import seaborn as sns  # type: ignore
import subprocess
sns.set()
warnings.simplefilter(action="ignore", category=FutureWarning)

##############################################################################
# Traitement d'images

black_red_cmap = LinearSegmentedColormap.from_list(
    "black_red_cmap", ["black", "red"])
black_green_cmap = LinearSegmentedColormap.from_list(
    "black_green_cmap", ["black", "green"]
)
black_blue_cmap = LinearSegmentedColormap.from_list(
    "black_blue_cmap", ["black", "blue"]
)


def load_images(datadir: str, pattern: str = "*.png") -> pd.Series:
    """
    Return all the images in `datadir` whose name match the pattern

    The images are returned as a Panda Series, with the image file
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
    images: Iterable[Image.Image], columns: int = 5, titles: Optional[Iterable] = None
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


def show_color_channels(img: Image.Image) -> Figure:
    """
    Return a figure displaying the image together with its red, green, and blue layers
    """
    M = np.array(img)
    # Remplacer la ligne suivante par le code adéquat
    # Échelles de couleur (colormap) allant du noir à la couleur primaire correspondante
    black_red_cmap = LinearSegmentedColormap.from_list('black_red_cmap', ["black", "red"])
    black_green_cmap = LinearSegmentedColormap.from_list('black_green_cmap', ["black", "green"])
    black_blue_cmap = LinearSegmentedColormap.from_list('black_blue_cmap', ["black", "blue"])

    fig = Figure(figsize=(30, 5));
    (subplot, subplotr, subplotg, subplotb) = fig.subplots(1, 4)  # Quatre zones de dessin
    # Dessin de l'image et de ses trois couches
    subplot.imshow(M)
    imgr = subplotr.imshow(M[:, :, 0], cmap=black_red_cmap,   vmin=0, vmax=255)
    imgg = subplotg.imshow(M[:, :, 1], cmap=black_green_cmap, vmin=0, vmax=255)
    imgb = subplotb.imshow(M[:, :, 2], cmap=black_blue_cmap,  vmin=0, vmax=255)
    # Ajout des barres d'échelle de couleur aux images
    fig.colorbar(imgr, ax=subplotr);
    fig.colorbar(imgg, ax=subplotg);
    fig.colorbar(imgb, ax=subplotb);
    fig
    return fig


def color_histogram(img: Image.Image) -> Figure:
    """
    Return a histogram of the color channels of the image
    """
    M = np.array(img)
    n, p, m = M.shape
    MM = np.reshape(M, (n * p, m))
    if m == 4:  # Discard transparency channel if present
        MM = MM[:, 0:3]
    colors = ["red", "green", "blue"]
    fig = Figure(figsize=(12, 6))
    ax = fig.add_subplot()
    ax.hist(MM, bins=10, density=True, histtype="bar", color=colors, label=colors)
    ax.set_xlabel("Pixel amplitude in each color channel")
    ax.set_ylabel("Pixel density")
    return fig


def foreground_filter(
    img: Union[Image.Image, np.ndarray], theta: int = 150
) -> np.ndarray:
    """Create a black and white image outlining the foreground."""
    M = np.array(img)
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


def transparent_background(img: Image.Image) -> Image.Image:
    """Sets the white background of an image to transparent"""
    data = img.getdata()  # Get a list of tuples
    newData = []
    for a in data:
        a = a[:3]  # Shorten to RGB
        if np.mean(np.array(a)) == 255:  # the background is white
            a = a + (0,)  # Put a transparent value in A channel (the fourth one)
        else:
            a = a + (255,)  # Put a non- transparent value in A channel
        newData.append(a)
    img.putdata(newData)  # Get new img ready
    return img

##############################################################################
# Attributs


def redness(img: Image.Image) -> float:
    """Return the redness of a PIL image."""
    M = np.array(img)
    F = foreground_filter(img)
    R = M[:, :, 0] * 1.0
    G = M[:, :, 1] * 1.0
    return R[F].mean()-G[F].mean()


def elongation(img: Image.Image) -> float:
    """Extract the scalar value elongation from a PIL image."""
    F = foreground_filter(img)
    # Build the cloud of points given by the foreground image pixels
    xy = np.argwhere(F)
    # Center the data
    C = np.mean(xy, axis=0)
    Cxy = xy - np.tile(C, [xy.shape[0], 1])
    # Apply singular value decomposition
    U, s, V = np.linalg.svd(Cxy)
    return s[0] / s[1]


def elongation_plot(img: Image.Image, subplot: Axes) -> None:
    """Plot the principal axes of the SVD when computing the elongation"""
    # Build the cloud of points defined by the foreground image pixels
    F = foreground_filter(img)
    xy = np.argwhere(F)
    # Center the data
    C = np.mean(xy, axis=0)
    Cxy = xy - np.tile(C, [xy.shape[0], 1])
    # Apply singular value decomposition
    U, s, V = np.linalg.svd(Cxy)

    N = len(xy)
    a0 = s[0] / np.sqrt(N)
    a1 = s[1] / np.sqrt(N)

    # Plot the center
    subplot.plot(
        C[1], C[0], "ro", linewidth=50, markersize=10
    )  # x and y are j and i in matrix coord.
    # Plot the principal axes
    subplot.plot(
        [C[1], C[1] + a0 * V[0, 1]], [C[0], C[0] + a0 * V[0, 0]], "r-", linewidth=3
    )
    subplot.plot(
        [C[1], C[1] - a0 * V[0, 1]], [C[0], C[0] - a0 * V[0, 0]], "r-", linewidth=3
    )
    subplot.plot(
        [C[1], C[1] + a1 * V[1, 1]], [C[0], C[0] + a1 * V[1, 0]], "g-", linewidth=3
    )
    subplot.plot(
        [C[1], C[1] - a1 * V[1, 1]], [C[0], C[0] - a1 * V[1, 0]], "g-", linewidth=3
    )


##############################################################################
# Nouveaux attributs

# Remplacer la ligne suivante par le code adéquat
def dist(x1, y1, x2, y2) :
    return math.sqrt((x1 - x2)**2 + (y1 - y2)**2)


def barycentre(F : np.ndarray) -> tuple:
    """Renvoit le barycentre d'un np.ndarray de booléens"""
    xy = np.argwhere(F)
    C = np.mean(xy, axis=0)
    return tuple(C)


def rayon(F : np.ndarray):
    x, y = round(barycentre(F)[0]), round(barycentre(F)[1])
    y1 = y
    y_neg = 0
    while F[y1][x] and y1 > 0:
        y1 -= 1
    y_neg = y1
    y1 = y
    while y1 < F.shape[1] and F[y1][x] :
        y1 += 1
    y_pos = y1
    return max([abs(y - y_pos), abs(y - y_neg)])


def croix(F : np.ndarray, x : float, y : float):
    x, y = round(x), round(y)
    F[y, x] = True
    F[y - 1, x - 1] = True
    F[y - 1, x + 1] = True
    F[y + 1, x - 1] = True
    F[y + 1, x + 1] = True
    F[y + 1, x] = False
    F[y - 1, x] = False
    F[y, x + 1] = False
    F[y, x - 1] = False


def count_ligne(F, y):
    counter = 0
    for x in range(len(F[y])):
        counter += F[y, x]
    return counter


def extraction_sourire(
    img: Union[Image.Image, np.ndarray], theta_red: int = 200, theta_blue : int = 230
) -> np.ndarray:
    """Create a black and white image outlining the foreground."""
#   color = np.array([M[0, 0, :], M[-1, 0, :], M[0, -1, :], M[-1, -1, :]]).mean()
#   -> methode artisanale pour savoir la couleur du fond, inutilisée
    MR = np.array(img)
    MB = np.array(img)
    MG = np.array(img)
#    print(color)
    for i in range(0, 4):
        MR[:, :, i] = MR[:, :, 0]
        MB[:, :, i] = MB[:, :, 2]
        MG[:, :, i] = MG[:, :, 1]
    R = np.min(MR[:, :, 0:3] * 1., axis=2)
    B = np.min(MB[:, :, 0:3] * 1., axis=2)
    FB = B < theta_blue
    F = R < theta_red
    Fvisages = FB ^ F
#   seuillage bleu et seuillage rouge -> permet de fusioner les details de chacun des 2 calques
    b = barycentre(FB)
    r = rayon(FB)
    b2 = barycentre(Fvisages)
    for y in range(len(Fvisages)):
        for x in range(len(Fvisages[y])):
            Fvisages[y, x] = not Fvisages[y][x] if (dist(x, y, *b) < r * 0.79 and y > b2[1] + 1) else False
#            filtre pour attenuer les elements trop bleus
#            if MB[y, x, 1] > 50 and MG[y, x, 1] > 50 and MR[y, x, 1] < 150:
#                Fvisages[y, x] = False
    statut = 0
    y_fin = 0
#   scan de la bouche (en partant du bas)
    for y in range(len(Fvisages) - 1, -1, -1):
        if statut == 0 and count_ligne(Fvisages, y) > 0:
            statut = 1
        elif statut == 1:
            if count_ligne(Fvisages, y) <= 0:
                y_fin = y
                break
#   efface ce qui se trouve au dessus
    for y in range(y_fin):
        for x in range(len(Fvisages[y])):
            Fvisages[y, x] = False
    return Fvisages


def bonheur(img):
    fig = extraction_sourire(img)
    xl, yl = [], []
    for y in range(len(fig)):
        for x in range(len(fig[y])):
            if fig[y, x]:
                xl.append(x)
                yl.append(-y)
    p2 = np.poly1d(np.polyfit(xl, yl, 2))
#   xp = np.linspace(0, len(fig), len(fig[1]))
#   plt.plot(xp, p2(xp), c='blue')
#   print(p2)
    return (p2[2])


class MatchedFilter:
    ''' Matched filter class to extract a feature from a template'''
    def __init__(self, examples: Iterable[Image.Image]):
        ''' Create the template for a matched filter; use only grayscale'''
        # Compute the average of all images after conversion to grayscale
        M = np.mean([np.asarray(img.convert('L'))
                     for img in examples], axis=0)
        # Standardize
        self.template = (M - M.mean()) / M.std()

    def show(self):
        """Show the template"""
        fig = Figure(figsize=(3, 3))
        ax = fig.add_subplot()
        ax.imshow(self.template, cmap='gray')
        return fig

    def match(self, img: Image.Image) -> Number:
        '''Extract the matched filter value for a PIL image.'''
        # Convert to grayscale and standardize
        M = np.asarray(img.convert('L'))
        M = (M - M.mean()) / M.std()
        # Compute scalar product with the template
        # This reinforce black and white if they agree
        return np.mean(np.multiply(self.template, M))

##############################################################################
# Analyse de performance


def error_rate(solutions: pd.Series, predictions: pd.Series) -> Any:
    """
    Return the error rate between two vectors.
    """
    return (solutions != predictions).mean()


def split_data(X, Y, verbose=True, seed=0):
    """Make a 50/50 training/test data split (stratified).
    Return the indices of the split train_idx and test_idx."""
    SSS = StratifiedShuffleSplit(n_splits=1, test_size=0.5, random_state=seed)
    ((train_index, test_index),) = SSS.split(X, Y)
    if verbose:
        print("TRAIN:", train_index, "TEST:", test_index)
    return (train_index, test_index)


def make_scatter_plot(
    df,
    images,
    train_index=[],
    test_index=[],
    filter=None,
    predicted_labels=[],
    show_diag=False,
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


##############################################################################
# Revue de code

def show_source(function: Callable) -> None:
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
