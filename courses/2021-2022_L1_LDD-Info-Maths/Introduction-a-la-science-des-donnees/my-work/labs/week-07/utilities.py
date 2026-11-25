import numpy as np  # type: ignore
import pandas as pd  # type: ignore
from PIL import Image  # type: ignore
from sklearn.model_selection import StratifiedShuffleSplit  # type: ignore


def crop_image(img: Image.Image, crop_size: int = 32) -> Image.Image:
    """Crop a PIL image to crop_size x crop_size."""
    # First determine the bounding box
    width, height = img.size
    new_width = 1.0 * crop_size
    new_height = 1.0 * crop_size
    left = round((width - new_width) / 2)
    top = round((height - new_height) / 2)
    right = round((width + new_width) / 2)
    bottom = round((height + new_height) / 2)
    # Then crop the image to that box
    cropped_img = img.crop((left, top, right, bottom))
    return cropped_img


def image_to_vector(img: Image.Image) -> np.ndarray:
    """Return the values of all the pixels of the Image as a vector"""
    return np.array(img).ravel()


def image_to_series(img: Image.Image) -> np.ndarray:
    """Return the values of all the pixels of the Image as a series"""
    return pd.Series(np.array(img).ravel())


def df_cross_validate(df, sklearn_model, sklearn_metric, n=10, verbose=False):
    """Compute the performance and error bars of a classifier by cross validation

    Input:
    - a data table whose last column contains the ground truth
    - a Scikit-learn model; or anything that quacks like it
    - a Scikit-learn performance metric;
      it can either be an loss (error rate) or an accuracy (success rate).
    """
    X = df.iloc[:, :-1].to_numpy()
    Y = df.iloc[:, -1].to_numpy()
    SSS = StratifiedShuffleSplit(n_splits=n, test_size=0.5, random_state=5)
    Perf_tr = np.zeros([n, 1])
    Perf_te = np.zeros([n, 1])
    k = 0
    for train_index, test_index in SSS.split(X, Y):
        # if verbose:
        #    print("TRAIN:", train_index, "TEST:", test_index)
        Xtrain, Xtest = X[train_index], X[test_index]
        Ytrain, Ytest = Y[train_index], Y[test_index]
        sklearn_model.fit(Xtrain, Ytrain.ravel())
        Ytrain_predicted = sklearn_model.predict(Xtrain)
        perf_tr = sklearn_metric(Ytrain.ravel(), Ytrain_predicted.ravel())
        # if verbose:
        #    print("TRAINING PERFORMANCE METRIC", perf_tr)
        Perf_tr[k] = perf_tr
        Ytest_predicted = sklearn_model.predict(Xtest)
        perf_te = sklearn_metric(Ytest.ravel(), Ytest_predicted.ravel())
        # if verbose:
        #    print("TEST PERFORMANCE METRIC:", perf_te)
        Perf_te[k] = perf_te
        k = k + 1

    perf_tr_ave = np.mean(Perf_tr)
    perf_te_ave = np.mean(Perf_te)
    sigma_tr = np.std(Perf_tr)
    sigma_te = np.std(Perf_te)
    if verbose:
        metric_name = sklearn_metric.__name__.upper()
        print(
            "*** AVERAGE TRAINING {0:s} +- STD: {1:.2f} +- {2:.2f} ***".format(
                metric_name, perf_tr_ave, sigma_tr
            )
        )
        print(
            "*** AVERAGE TEST {0:s} +- STD: {1:.2f} +- {2:.2f} ***".format(
                metric_name, perf_te_ave, sigma_te
            )
        )
    return (perf_tr_ave, sigma_tr, perf_te_ave, sigma_te)


def check_na(df):
    """Finds whether there are missing values."""
    # I used this post
    # https://dzone.com/articles/pandas-find-rows-where-columnfield-is-null
    na_columns = df.columns[df.isna().any()]
    found_na = df[df.isna().any(axis=1)][na_columns]
    print(found_na.head())
    return found_na


def standardize_df(df):
    """Standardize all the columns except the last one (target values)."""
    df_scaled = (df - df.mean()) / df.std()
    df_scaled.iloc[:, -1] = df.iloc[:, -1]
    return df_scaled
