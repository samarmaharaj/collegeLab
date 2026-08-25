"""Spatial Filtering:
1. Add Salt-and-Pepper noise
2. Apply mean and median filters
3. Apply Laplacian filter
4. Compare results (without built-in filtering functions)
"""

import os
import cv2
import numpy as np


def add_salt_pepper_noise(image, amount=0.05, salt_ratio=0.5, seed=None):
    rng = np.random.default_rng(seed)
    noisy = image.copy()
    h, w = image.shape[:2]
    n = int(amount * h * w)

    ys = rng.integers(0, h, n)
    xs = rng.integers(0, w, n)
    salt = rng.random(n) < salt_ratio

    if image.ndim == 2:
        noisy[ys[salt], xs[salt]] = 255
        noisy[ys[~salt], xs[~salt]] = 0
    else:
        noisy[ys[salt], xs[salt], :] = 255
        noisy[ys[~salt], xs[~salt], :] = 0

    return noisy


def _pad(img, k):
    p = k // 2
    if img.ndim == 2:
        return np.pad(img, ((p, p), (p, p)), mode="edge")
    return np.pad(img, ((p, p), (p, p), (0, 0)), mode="edge")


def mean_filter(image, ksize=3):
    pimg = _pad(image, ksize)
    out = np.zeros_like(image, dtype=np.float32)

    if image.ndim == 2:
        for y in range(image.shape[0]):
            for x in range(image.shape[1]):
                out[y, x] = np.mean(pimg[y:y + ksize, x:x + ksize])
    else:
        for y in range(image.shape[0]):
            for x in range(image.shape[1]):
                for c in range(image.shape[2]):
                    out[y, x, c] = np.mean(pimg[y:y + ksize, x:x + ksize, c])

    return np.clip(out, 0, 255).astype(np.uint8)


def median_filter(image, ksize=3):
    pimg = _pad(image, ksize)
    out = np.zeros_like(image, dtype=np.float32)

    if image.ndim == 2:
        for y in range(image.shape[0]):
            for x in range(image.shape[1]):
                out[y, x] = np.median(pimg[y:y + ksize, x:x + ksize])
    else:
        for y in range(image.shape[0]):
            for x in range(image.shape[1]):
                for c in range(image.shape[2]):
                    out[y, x, c] = np.median(pimg[y:y + ksize, x:x + ksize, c])

    return np.clip(out, 0, 255).astype(np.uint8)


def laplacian_filter(image):
    kernel = np.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]], dtype=np.int32)
    pimg = _pad(image, 3).astype(np.int32)
    out = np.zeros_like(image, dtype=np.int32)

    if image.ndim == 2:
        for y in range(image.shape[0]):
            for x in range(image.shape[1]):
                region = pimg[y:y + 3, x:x + 3]
                out[y, x] = np.sum(region * kernel)
    else:
        for y in range(image.shape[0]):
            for x in range(image.shape[1]):
                for c in range(image.shape[2]):
                    region = pimg[y:y + 3, x:x + 3, c]
                    out[y, x, c] = np.sum(region * kernel)

    return np.clip(np.abs(out), 0, 255).astype(np.uint8)


def mse(a, b):
    d = a.astype(np.float32) - b.astype(np.float32)
    return float(np.mean(d * d))
