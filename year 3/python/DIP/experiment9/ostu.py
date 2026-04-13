import cv2
import numpy as np
from matplotlib import pyplot as plt
import os


def manual_otsu_threshold(gray_img):
    """Compute Otsu threshold manually by maximizing between-class variance."""
    hist = cv2.calcHist([gray_img], [0], None, [256], [0, 256]).ravel().astype(np.float64)
    total = gray_img.size
    prob = hist / total

    omega = np.cumsum(prob)
    mu = np.cumsum(prob * np.arange(256))
    mu_t = mu[-1]

    denom = omega * (1.0 - omega)
    denom[denom == 0] = np.nan
    sigma_b2 = ((mu_t * omega - mu) ** 2) / denom

    threshold = int(np.nanargmax(sigma_b2))
    binary = np.where(gray_img > threshold, 255, 0).astype(np.uint8)
    return threshold, binary


def otsu_objective_curve(gray_img):
    """Return Otsu between-class variance for every threshold k (0..255)."""
    hist = cv2.calcHist([gray_img], [0], None, [256], [0, 256]).ravel().astype(np.float64)
    prob = hist / gray_img.size

    omega = np.cumsum(prob)
    mu = np.cumsum(prob * np.arange(256))
    mu_t = mu[-1]

    sigma_b2 = np.zeros(256, dtype=np.float64)
    for k in range(256):
        w0 = omega[k]
        w1 = 1.0 - w0
        if w0 == 0.0 or w1 == 0.0:
            sigma_b2[k] = 0.0
            continue
        mu0 = mu[k] / w0
        mu1 = (mu_t - mu[k]) / w1
        sigma_b2[k] = w0 * w1 * (mu0 - mu1) ** 2

    optimal_k = int(np.argmax(sigma_b2))
    return np.arange(256), sigma_b2, optimal_k


def otsu_thresholding(image_path):
    """
    Apply Otsu's thresholding to an image
    
    Args:
        image_path: Path to the input image
    
    Returns:
        Original image, binary image, and optimal threshold value
    """
    # Read image in grayscale
    img = cv2.imread(image_path, cv2.IMREAD_GRAYSCALE)
    
    if img is None:
        raise FileNotFoundError(f"Could not read image: {image_path}")
    
    # Apply OpenCV Otsu thresholding
    threshold_value, binary_image = cv2.threshold(
        img, 0, 255, cv2.THRESH_BINARY + cv2.THRESH_OTSU
    )

    # Apply manual Otsu thresholding
    manual_threshold, manual_binary = manual_otsu_threshold(img)
    
    print(f"OpenCV Otsu Threshold: {threshold_value}")
    print(f"Manual Otsu Threshold: {manual_threshold}")
    
    return img, binary_image, threshold_value, manual_binary, manual_threshold

def display_results(img, binary_img, threshold_val, manual_binary, manual_threshold):
    """Display original/result images, histograms, and Otsu objective curve."""
    k_values, sigma_b2, optimal_k = otsu_objective_curve(img)

    fig, axes = plt.subplots(2, 3, figsize=(16, 9))
    fig.suptitle("Otsu Thresholding Analysis", fontsize=13, fontweight="bold")

    axes[0, 0].imshow(img, cmap="gray")
    axes[0, 0].set_title("Original Image")
    axes[0, 0].axis("off")

    axes[0, 1].imshow(binary_img, cmap="gray")
    axes[0, 1].set_title(f"OpenCV Otsu (T={threshold_val:.0f})")
    axes[0, 1].axis("off")

    axes[0, 2].imshow(manual_binary, cmap="gray")
    axes[0, 2].set_title(f"Manual Otsu (T={manual_threshold})")
    axes[0, 2].axis("off")

    axes[1, 0].hist(img.ravel(), bins=256, range=(0, 256), color="gray")
    axes[1, 0].axvline(manual_threshold, color="red", linewidth=2, label=f"Optimal k={manual_threshold}")
    axes[1, 0].set_title("Histogram with Optimal k")
    axes[1, 0].set_xlabel("Intensity k")
    axes[1, 0].set_ylabel("Count")
    axes[1, 0].legend()

    axes[1, 1].plot(k_values, sigma_b2, color="blue", linewidth=1.5)
    axes[1, 1].axvline(optimal_k, color="red", linewidth=2, label=f"Optimal k={optimal_k}")
    axes[1, 1].set_title("Otsu Objective: Between-Class Variance")
    axes[1, 1].set_xlabel("Threshold k")
    axes[1, 1].set_ylabel("sigma_b^2(k)")
    axes[1, 1].grid(alpha=0.3)
    axes[1, 1].legend()

    axes[1, 2].hist(binary_img.ravel(), bins=256, range=(0, 256), color="black")
    axes[1, 2].set_title("Histogram - Thresholded Output")
    axes[1, 2].set_xlabel("Intensity")
    axes[1, 2].set_ylabel("Count")

    plt.tight_layout()
    plt.show()


def resolve_image_path(image_name):
    """Resolve relative image path from the script directory."""
    if os.path.isabs(image_name):
        return image_name
    script_dir = os.path.dirname(os.path.abspath(__file__))
    candidate = os.path.join(script_dir, image_name)
    if os.path.exists(candidate):
        return candidate

    base_name, _ = os.path.splitext(image_name)
    for ext in [".jpg", ".jpeg", ".png", ".bmp", ".tif", ".tiff"]:
        trial = os.path.join(script_dir, base_name + ext)
        if os.path.exists(trial):
            return trial

    return candidate

# Main execution
if __name__ == "__main__":
    image_path = resolve_image_path("boat.jpg")
    try:
        img, binary_img, threshold, manual_binary, manual_threshold = otsu_thresholding(image_path)
        display_results(img, binary_img, threshold, manual_binary, manual_threshold)
    except FileNotFoundError as err:
        print(err)