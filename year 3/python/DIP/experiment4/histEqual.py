import os
import cv2
import matplotlib.pyplot as plt
import numpy as np

def manual_histogram_equalization(img):
    """
    Perform histogram equalization manually
    """
    # Get image dimensions
    h, w = img.shape
    total_pixels = h * w
    
    # Calculate histogram
    hist = np.zeros(256)
    for i in range(h):
        for j in range(w):
            hist[img[i, j]] += 1
    
    # Calculate cumulative distribution function (CDF)
    cdf = np.zeros(256)
    cdf[0] = hist[0]
    for i in range(1, 256):
        cdf[i] = cdf[i-1] + hist[i]
    
    # Normalize CDF
    cdf_normalized = (cdf * 255) / total_pixels
    
    # Create lookup table
    lookup_table = np.round(cdf_normalized).astype(np.uint8)
    
    # Apply histogram equalization
    equalized_img = np.zeros_like(img)
    for i in range(h):
        for j in range(w):
            equalized_img[i, j] = lookup_table[img[i, j]]
    
    return equalized_img, hist, cdf_normalized

# Load original image in grayscale using a relative path
script_dir = os.path.dirname(os.path.abspath(__file__))
img_path = os.path.join(script_dir, '1.jpeg')
original_img = cv2.imread(img_path, 0)

if original_img is None:
    print("Error: Could not load image '1.jpeg'. Check file path.")
    print("Creating a dummy image for demonstration...")
    # Create a dummy low-contrast image for demonstration
    original_img = np.random.randint(50, 150, (300, 300), dtype=np.uint8)

# Perform histogram equalization using OpenCV
equalized_opencv = cv2.equalizeHist(original_img)

# Perform manual histogram equalization
equalized_manual, original_hist, original_cdf = manual_histogram_equalization(original_img)
_, equalized_hist, equalized_cdf = manual_histogram_equalization(equalized_opencv)

# Create comprehensive visualization
plt.figure(figsize=(15, 12))

# Original image
plt.subplot(3, 4, 1)
plt.imshow(original_img, cmap='gray')
plt.title('Original Image')
plt.axis('off')

# Original histogram
plt.subplot(3, 4, 2)
plt.hist(original_img.ravel(), 256, [0, 256], density=True, alpha=0.7, color='blue')
plt.title('Original Histogram')
plt.xlabel('Intensity')
plt.ylabel('Probability')

# Original CDF
plt.subplot(3, 4, 3)
plt.plot(original_cdf, color='red')
plt.title('Original CDF')
plt.xlabel('Intensity')
plt.ylabel('Cumulative Probability')

# Equalized image (OpenCV)
plt.subplot(3, 4, 5)
plt.imshow(equalized_opencv, cmap='gray')
plt.title('Equalized (OpenCV)')
plt.axis('off')

# Equalized histogram (OpenCV)
plt.subplot(3, 4, 6)
plt.hist(equalized_opencv.ravel(), 256, [0, 256], density=True, alpha=0.7, color='green')
plt.title('Equalized Histogram (OpenCV)')
plt.xlabel('Intensity')
plt.ylabel('Probability')

# Equalized CDF (OpenCV)
plt.subplot(3, 4, 7)
plt.plot(equalized_cdf, color='orange')
plt.title('Equalized CDF (OpenCV)')
plt.xlabel('Intensity')
plt.ylabel('Cumulative Probability')

# Equalized image (Manual)
plt.subplot(3, 4, 9)
plt.imshow(equalized_manual, cmap='gray')
plt.title('Equalized (Manual)')
plt.axis('off')

# Equalized histogram (Manual)
plt.subplot(3, 4, 10)
plt.hist(equalized_manual.ravel(), 256, [0, 256], density=True, alpha=0.7, color='purple')
plt.title('Equalized Histogram (Manual)')
plt.xlabel('Intensity')
plt.ylabel('Probability')

# Comparison plot
plt.subplot(3, 4, 4)
plt.plot(original_hist, label='Original', alpha=0.7)
plt.plot(np.histogram(equalized_opencv.ravel(), 256, [0, 256])[0], label='Equalized', alpha=0.7)
plt.title('Histogram Comparison')
plt.xlabel('Intensity')
plt.ylabel('Frequency')
plt.legend()

# Statistics comparison
plt.subplot(3, 4, 8)
stats_data = {
    'Metric': ['Mean', 'Std Dev', 'Min', 'Max'],
    'Original': [np.mean(original_img), np.std(original_img), 
                np.min(original_img), np.max(original_img)],
    'Equalized': [np.mean(equalized_opencv), np.std(equalized_opencv),
                 np.min(equalized_opencv), np.max(equalized_opencv)]
}
x = np.arange(len(stats_data['Metric']))
width = 0.35
plt.bar(x - width/2, stats_data['Original'], width, label='Original', alpha=0.7)
plt.bar(x + width/2, stats_data['Equalized'], width, label='Equalized', alpha=0.7)
plt.xlabel('Metrics')
plt.ylabel('Values')
plt.title('Statistical Comparison')
plt.xticks(x, stats_data['Metric'])
plt.legend()

plt.tight_layout()
plt.show()

# Print statistical analysis
print("HISTOGRAM EQUALIZATION ANALYSIS")
print("=" * 40)
print(f"Original Image Statistics:")
print(f"  Mean: {np.mean(original_img):.2f}")
print(f"  Standard Deviation: {np.std(original_img):.2f}")
print(f"  Min Value: {np.min(original_img)}")
print(f"  Max Value: {np.max(original_img)}")

print(f"\nEqualized Image Statistics:")
print(f"  Mean: {np.mean(equalized_opencv):.2f}")
print(f"  Standard Deviation: {np.std(equalized_opencv):.2f}")
print(f"  Min Value: {np.min(equalized_opencv)}")
print(f"  Max Value: {np.max(equalized_opencv)}")

print(f"\nContrast Enhancement:")
print(f"  Original Contrast (std): {np.std(original_img):.2f}")
print(f"  Enhanced Contrast (std): {np.std(equalized_opencv):.2f}")
print(f"  Improvement Factor: {np.std(equalized_opencv)/np.std(original_img):.2f}x")

# Verify manual implementation matches OpenCV
difference = np.mean(np.abs(equalized_opencv.astype(float) - equalized_manual.astype(float)))
print(f"\nImplementation Verification:")
print(f"  Mean difference between OpenCV and Manual: {difference:.2f}")
if difference < 1.0:
    print("  ✓ Manual implementation is accurate!")
else:
    print("  ⚠ Manual implementation may need adjustment")