from typing import Union
import numpy as np
from PIL import Image  # type: ignore


def foreground_filter(
    img: Union[Image.Image, np.ndarray], theta: int = 150
) -> np.ndarray:
    """Create a black and white image outlining the foreground."""
    M = np.array(img)  # In case this is not yet a Numpy array
    G = np.min(M[:, :, 0:3], axis=2)
    F = G < theta
    return F


def transparent_background_filter(
    img: Union[Image.Image, np.ndarray], foreground: np.ndarray
) -> Image.Image:
    """Make all pixels not in the foreground transparent."""
    M = np.array(img)
    N = np.zeros([M.shape[0], M.shape[1], 4], dtype=M.dtype)
    N[:, :, :3] = M[:, :, :3]
    N[:, :, 3] = foreground * 255
    return Image.fromarray(N)


def yellowness_filter(img: Union[Image.Image, np.ndarray]) -> np.ndarray:
    """Return a grey-level image measuring the yellowness of each pixel."""
    M = np.array(img)
    return np.array(M[:,:,0]+M[:,:,1]-M[:,:,2], dtype="float64")


def color_correlation_filter(
    img: Union[Image.Image, np.ndarray], color: np.ndarray
) -> np.ndarray:
    """Return a grey-level image measuring the correlation of the pixels
    with the given color."""
    M = np.array(img)
    height, width, col = M.shape
    return [[np.corrcoef(M[i, j], color)[0, 1] for j in range(width)] for i in range(height)]
