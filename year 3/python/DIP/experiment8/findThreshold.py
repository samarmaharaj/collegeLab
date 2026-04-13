import cv2
import matplotlib.pyplot as plt
import numpy as np


def canny_edge_detection(image, low_threshold=100, high_threshold=200):
    """
    Custom implementation of Canny Edge Detection Algorithm.
    
    Steps:
    1. Gaussian Blur - Reduce noise
    2. Gradient Calculation - Sobel derivatives
    3. Non-Maximum Suppression - Thin edges
    4. Double Thresholding - Classify edges
    5. Hysteresis - Track and connect edges
    """
    # Step 1: Gaussian Blur (Noise Reduction)
    blurred = cv2.GaussianBlur(image, (5, 5), 1.4)
    
    # Step 2: Gradient Calculation (Sobel)
    gx = cv2.Sobel(blurred, cv2.CV_64F, 1, 0, ksize=3)  # Vertical edges
    gy = cv2.Sobel(blurred, cv2.CV_64F, 0, 1, ksize=3)  # Horizontal edges
    
    # Magnitude and Direction
    magnitude = np.sqrt(gx**2 + gy**2)
    direction = np.arctan2(gy, gx)  # In radians
    
    # Step 3: Non-Maximum Suppression (Thin edges)
    suppressed = non_max_suppression(magnitude, direction)
    
    # Step 4: Double Thresholding
    edges = np.zeros_like(suppressed)
    edges[suppressed > high_threshold] = 255  # Strong edges
    edges[(suppressed <= high_threshold) & (suppressed > low_threshold)] = 127  # Weak edges
    
    # Step 5: Hysteresis (Edge Tracking)
    edges = hysteresis(edges, low_threshold, high_threshold)
    
    return edges.astype(np.uint8)


def non_max_suppression(magnitude, direction):
    """
    Non-Maximum Suppression: Keep only local maxima along gradient direction.
    This thins the edges.
    """
    h, w = magnitude.shape
    suppressed = np.zeros_like(magnitude)
    
    # Convert direction from radians to degrees
    direction_deg = np.degrees(direction)
    direction_deg = (direction_deg + 180) % 180  # Normalize to [0, 180]
    
    for i in range(1, h - 1):
        for j in range(1, w - 1):
            angle = direction_deg[i, j]
            mag = magnitude[i, j]
            
            # Determine neighbors along gradient direction
            if (0 <= angle < 22.5) or (157.5 <= angle <= 180):
                # Horizontal direction
                neighbor1 = magnitude[i, j + 1]
                neighbor2 = magnitude[i, j - 1]
            elif 22.5 <= angle < 67.5:
                # Diagonal /
                neighbor1 = magnitude[i + 1, j - 1]
                neighbor2 = magnitude[i - 1, j + 1]
            elif 67.5 <= angle < 112.5:
                # Vertical direction
                neighbor1 = magnitude[i + 1, j]
                neighbor2 = magnitude[i - 1, j]
            else:  # 112.5 <= angle < 157.5
                # Diagonal \
                neighbor1 = magnitude[i - 1, j - 1]
                neighbor2 = magnitude[i + 1, j + 1]
            
            # Keep if local maximum along gradient direction
            if mag >= neighbor1 and mag >= neighbor2:
                suppressed[i, j] = mag
    
    return suppressed


def hysteresis(edges, low_threshold, high_threshold):
    """
    Edge Tracking by Hysteresis: Connect weak edges to strong edges.
    Discard weak edges that are not connected to strong ones.
    """
    h, w = edges.shape
    output = np.zeros_like(edges)
    
    # Mark strong edges
    strong_edges = edges == 255
    output[strong_edges] = 255
    
    # For each weak edge, check if connected to strong edge (8-connectivity)
    weak_edges = edges == 127
    for i in range(h):
        for j in range(w):
            if weak_edges[i, j]:
                # Check 8 neighbors
                if is_connected_to_strong_edge(output, i, j, strong_edges, h, w):
                    output[i, j] = 255
    
    return output


def is_connected_to_strong_edge(output, i, j, strong_edges, h, w):
    """
    Check if pixel (i, j) is 8-connected to any strong edge.
    """
    for di in [-1, 0, 1]:
        for dj in [-1, 0, 1]:
            if di == 0 and dj == 0:
                continue
            ni, nj = i + di, j + dj
            if 0 <= ni < h and 0 <= nj < w:
                if output[ni, nj] == 255:  # Connected to strong edge
                    return True
    
    return False


def show_page(image, edge_image, image_name):
    fig, axes = plt.subplots(2, 2, figsize=(10, 8))
    fig.suptitle(f"{image_name}: Original, Canny Output, and Histograms", fontsize=13, fontweight="bold")

    axes[0, 0].imshow(image, cmap="gray")
    axes[0, 0].set_title("Original")
    axes[0, 0].axis("off")

    axes[0, 1].imshow(edge_image, cmap="gray")
    axes[0, 1].set_title("Processed (Canny)")
    axes[0, 1].axis("off")

    axes[1, 0].hist(image.ravel(), bins=256, range=(0, 256), color="gray")
    axes[1, 0].set_title("Histogram - Original")
    axes[1, 0].set_xlabel("Intensity")
    axes[1, 0].set_ylabel("Count")

    axes[1, 1].hist(edge_image.ravel(), bins=256, range=(0, 256), color="black")
    axes[1, 1].set_title("Histogram - Processed")
    axes[1, 1].set_xlabel("Intensity")
    axes[1, 1].set_ylabel("Count")

    plt.tight_layout()
    plt.show()


# Main execution
img1 = cv2.imread("house.jpeg", cv2.IMREAD_GRAYSCALE)
img2 = cv2.imread("brain.jpeg", cv2.IMREAD_GRAYSCALE)

if img1 is None:
    raise FileNotFoundError("house.jpeg not found in current folder")
if img2 is None:
    raise FileNotFoundError("brain.jpeg not found in current folder")


thresholds = [(50, i) for i in range(51, 151)]  # 100 pairs: low=50, high=51..150

# Calculate grid size dynamically
num_thresholds = len(thresholds)
cols = 5
rows = (num_thresholds + cols - 1) // cols  # Ceiling division

fig, axes = plt.subplots(rows, cols, figsize=(15, 3*rows))
axes = axes.flatten()  # Flatten to 1D for easy indexing

for idx, (low, high) in enumerate(thresholds):
    img_edges = canny_edge_detection(img1, low, high)
    axes[idx].imshow(img_edges, cmap="gray")
    axes[idx].set_title(f"Low={low}, High={high}", fontsize=8)
    axes[idx].axis("off")

# Hide unused subplots
for idx in range(num_thresholds, len(axes)):
    axes[idx].axis("off")

plt.tight_layout()
plt.show()