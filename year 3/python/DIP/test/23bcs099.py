import cv2
import os
import numpy as np
import matplotlib.pyplot as plt
from numpy.lib.stride_tricks import sliding_window_view


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

    if image.ndim == 2:
        windows = sliding_window_view(pimg, (ksize, ksize))
        out = windows.mean(axis=(-2, -1))
    else:
        windows = sliding_window_view(pimg, (ksize, ksize), axis=(0, 1))
        out = windows.mean(axis=(-2, -1))

    return np.clip(out, 0, 255).astype(np.uint8)

def median_filter(image, ksize=3):
    pimg = _pad(image, ksize)

    if image.ndim == 2:
        windows = sliding_window_view(pimg, (ksize, ksize))
        out = np.median(windows, axis=(-2, -1))
    else:
        windows = sliding_window_view(pimg, (ksize, ksize), axis=(0, 1))
        out = np.median(windows, axis=(-2, -1))

    return np.clip(out, 0, 255).astype(np.uint8)


def laplacian_filter(image):
    kernel = np.array([[0, -1, 0], [-1, 4, -1], [0, -1, 0]], dtype=np.int32)
    pimg = _pad(image, 3).astype(np.int32)

    if image.ndim == 2:
        windows = sliding_window_view(pimg, (3, 3))
        out = np.sum(windows * kernel, axis=(-2, -1))
    else:
        windows = sliding_window_view(pimg, (3, 3), axis=(0, 1))
        out = np.sum(windows * kernel[..., None], axis=(-3, -2))

    return np.clip(np.abs(out), 0, 255).astype(np.uint8)


def mse(a, b):
    a = a.astype(np.float32)
    b = b.astype(np.float32)
    return float(np.mean((a - b) ** 2))

script_dir = os.path.dirname(os.path.abspath(__file__))
image_path = os.path.join(script_dir, 'input.png')
image = cv2.imread(image_path)

original = image.copy()
noisy = add_salt_pepper_noise(original, amount=0.05, salt_ratio=0.5, seed=42)
mean_img = mean_filter(noisy, ksize=3)
median_img = median_filter(noisy, ksize=3)
laplacian_img = laplacian_filter(noisy)

print("Comparison (MSE with Original image):")
print(f"Mean Filter MSE     : {mse(original, mean_img):.2f}")
print(f"Median Filter MSE   : {mse(original, median_img):.2f}")
print(f"Laplacian Filter MSE: {mse(original, laplacian_img):.2f}")

images = [original, noisy, mean_img, median_img, laplacian_img]
titles = ["Original", "Salt & Pepper Noise", "Mean Filter", "Median Filter", "Laplacian Filter"]

plt.figure(figsize=(18, 4))
for i, (img, title) in enumerate(zip(images, titles), start=1):
    plt.subplot(2, 3, i)
    plot_img = img
    if plot_img.ndim == 2:
        plt.imshow(plot_img, cmap="gray")
    else:
        plt.imshow(cv2.cvtColor(plot_img, cv2.COLOR_BGR2RGB))
    plt.title(title)
    plt.axis("off")

plt.tight_layout()
plt.show()