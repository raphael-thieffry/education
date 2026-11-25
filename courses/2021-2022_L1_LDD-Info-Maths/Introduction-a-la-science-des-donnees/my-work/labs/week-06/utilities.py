from typing import Union
import numpy as np
from PIL import Image  # type: ignore
import math

def foreground_filter(
    img: Union[Image.Image, np.ndarray], theta: int = 150
) -> np.ndarray:
    """Create a black and white image outlining the foreground."""
    M = np.array(img)  # In case this is not yet a Numpy array
    G = np.min(M[:, :, 0:3], axis=2)
    F = G < theta
    return F

def foreground_filter_alreadygrey(
    img: Union[Image.Image, np.ndarray], theta: int = 150
) -> np.ndarray:
    """Create a black and white image outlining the foreground."""
    M = np.array(img)  # In case this is not yet a Numpy array
    F = M > theta
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
    M = np.array(img, dtype='float64')
    Y = M[:, :, 0:1] + M[:, :, 1:2] -  M[:, :, 2:3] 
    return Y[:, :, 0]

def color_correlation_filter(
    img: Union[Image.Image, np.ndarray], color: np.ndarray
) -> np.ndarray:
    """Return a grey-level image measuring the correlation of the pixels
    with the given color."""
    N = np.array(img, dtype='float64')
    r = np.array([[np.corrcoef(linPix[i][0:3], color)[0, 1] for i in range(len(linPix))] for linPix in N])
    return r

def zonecolorpicker(
    img_carree : Image.Image, xy : [int, int], radius : float
) -> [float, float, float]:
    zone = []
    for y, pixL in enumerate(np.array(img_carree)):
        for x, val in enumerate(pixL):
            if radius>math.sqrt((x-xy[0])**2+(y-xy[1])**2):
                zone.append(np.array([val[i] for i in range(0,3)]))
    zonenp = np.array(zone)
    newyellow = [zonenp[:,0].mean(), zonenp[:,1].mean(), zonenp[:,2].mean()]
    return newyellow



