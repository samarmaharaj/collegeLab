import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

def create_dummy_images():
    """
    Create dummy input and reference images for demonstration
    """
    # Create a low-contrast input image (dark scene)
    input_img = np.random.normal(60, 25, (300, 300))
    input_img = np.clip(input_img, 0, 255).astype(np.uint8)
    
    # Create a reference image with desired histogram characteristics (bright scene)
    reference_img = np.random.normal(180, 40, (300, 300))
    reference_img = np.clip(reference_img, 0, 255).astype(np.uint8)
    
    return input_img, reference_img

def histogram_specification_manual(image, reference_image):
    """
    Perform histogram specification (matching) manually using the algorithm steps:
    1. Compute histograms and CDFs for both images
    2. Create mapping function from input CDF to reference CDF
    3. Apply the mapping
    
    Args:
        image: Input image (grayscale)
        reference_image: Reference image whose histogram we want to match
    
    Returns:
        output_image: Image with matched histogram
        mapping: The intensity mapping function used
    """
    # Get image dimensions
    h1, w1 = image.shape
    h2, w2 = reference_image.shape
    
    # Calculate histograms manually
    input_hist = np.zeros(256)
    ref_hist = np.zeros(256)
    
    # Count pixel intensities
    for i in range(h1):
        for j in range(w1):
            input_hist[image[i, j]] += 1
    
    for i in range(h2):
        for j in range(w2):
            ref_hist[reference_image[i, j]] += 1
    
    # Normalize histograms
    input_hist = input_hist / (h1 * w1)
    ref_hist = ref_hist / (h2 * w2)
    
    # Calculate CDFs
    input_cdf = np.zeros(256)
    ref_cdf = np.zeros(256)
    
    input_cdf[0] = input_hist[0]
    ref_cdf[0] = ref_hist[0]
    
    for i in range(1, 256):
        input_cdf[i] = input_cdf[i-1] + input_hist[i]
        ref_cdf[i] = ref_cdf[i-1] + ref_hist[i]
    
    # Create mapping function
    mapping = np.zeros(256, dtype=np.uint8)
    
    for i in range(256):
        # Find the intensity in reference CDF closest to input_cdf[i]
        diff = np.abs(ref_cdf - input_cdf[i])
        j = np.argmin(diff)
        mapping[i] = j
    
    # Apply mapping
    output_image = np.zeros_like(image)
    for i in range(h1):
        for j in range(w1):
            output_image[i, j] = mapping[image[i, j]]
    
    return output_image, mapping

def histogram_specification_opencv(image, reference_image):
    """
    Perform histogram specification using OpenCV's built-in functions
    """
    # Flatten images
    img_flat = image.flatten()
    ref_flat = reference_image.flatten()
    
    # Calculate histograms
    img_hist, _ = np.histogram(img_flat, bins=256, range=(0, 256))
    ref_hist, _ = np.histogram(ref_flat, bins=256, range=(0, 256))
    
    # Calculate CDFs
    img_cdf = img_hist.cumsum()
    img_cdf = img_cdf / img_cdf[-1]
    
    ref_cdf = ref_hist.cumsum()
    ref_cdf = ref_cdf / ref_cdf[-1]
    
    # Create mapping
    mapping = np.zeros(256, dtype=np.uint8)
    for i in range(256):
        j = np.argmin(np.abs(ref_cdf - img_cdf[i]))
        mapping[i] = j
    
    # Apply mapping using OpenCV LUT (Look-Up Table)
    output_image = cv2.LUT(image, mapping)
    return output_image, mapping

def analyze_histogram_statistics(image, title):
    """
    Calculate and return histogram statistics
    """
    stats = {
        'mean': np.mean(image),
        'std': np.std(image),
        'min': np.min(image),
        'max': np.max(image),
        'median': np.median(image)
    }
    return stats

# Get script directory for relative paths
script_dir = os.path.dirname(os.path.abspath(__file__))

# Try to load real images, create dummy ones if not available
input_path = os.path.join(script_dir, 'input.jpg')
ref_path = os.path.join(script_dir, 'moon.jpeg')

# Load input image (try different filenames)
input_image = None
ref_image = None

# Try various possible filenames for input image
input_names = ['input.jpg', 'input.jpeg', 'input.png', '1.jpg', '1.jpeg', '1.png']
for name in input_names:
    path = os.path.join(script_dir, name)
    if os.path.exists(path):
        input_image = cv2.imread(path, 0)
        if input_image is not None:
            print(f"Loaded input image: {name}")
            break

# Try various possible filenames for reference image
ref_names = ['moon.jpeg', 'reference.jpg', 'reference.jpeg', 'reference.png', '2.jpg', '2.jpeg', '2.png']
for name in ref_names:
    path = os.path.join(script_dir, name)
    if os.path.exists(path):
        ref_image = cv2.imread(path, 0)
        if ref_image is not None:
            print(f"Loaded reference image: {name}")
            break

# Create dummy images if real ones not found
if input_image is None or ref_image is None:
    print("Creating dummy images for demonstration...")
    input_image, ref_image = create_dummy_images()
    print("Using generated dummy images (dark input, bright reference)")

# Ensure both images are the same size for fair comparison
if input_image.shape != ref_image.shape:
    # Resize reference to match input
    ref_image = cv2.resize(ref_image, (input_image.shape[1], input_image.shape[0]))

# Apply histogram specification using both methods
result_manual, mapping_manual = histogram_specification_manual(input_image, ref_image)
result_opencv, mapping_opencv = histogram_specification_opencv(input_image, ref_image)

# Calculate statistics
input_stats = analyze_histogram_statistics(input_image, "Input")
ref_stats = analyze_histogram_statistics(ref_image, "Reference")
result_manual_stats = analyze_histogram_statistics(result_manual, "Manual Result")
result_opencv_stats = analyze_histogram_statistics(result_opencv, "OpenCV Result")

# Create comprehensive visualization
plt.figure(figsize=(18, 12))

# Row 1: Images
plt.subplot(4, 4, 1)
plt.imshow(input_image, cmap='gray')
plt.title('Input Image')
plt.axis('off')

plt.subplot(4, 4, 2)
plt.imshow(ref_image, cmap='gray')
plt.title('Reference Image')
plt.axis('off')

plt.subplot(4, 4, 3)
plt.imshow(result_manual, cmap='gray')
plt.title('Result (Manual)')
plt.axis('off')

plt.subplot(4, 4, 4)
plt.imshow(result_opencv, cmap='gray')
plt.title('Result (OpenCV)')
plt.axis('off')

# Row 2: Histograms
plt.subplot(4, 4, 5)
plt.hist(input_image.ravel(), 256, [0, 256], alpha=0.7, color='blue', density=True)
plt.title('Input Histogram')
plt.xlabel('Intensity')
plt.ylabel('Probability')

plt.subplot(4, 4, 6)
plt.hist(ref_image.ravel(), 256, [0, 256], alpha=0.7, color='green', density=True)
plt.title('Reference Histogram')
plt.xlabel('Intensity')
plt.ylabel('Probability')

plt.subplot(4, 4, 7)
plt.hist(result_manual.ravel(), 256, [0, 256], alpha=0.7, color='red', density=True)
plt.title('Manual Result Histogram')
plt.xlabel('Intensity')
plt.ylabel('Probability')

plt.subplot(4, 4, 8)
plt.hist(result_opencv.ravel(), 256, [0, 256], alpha=0.7, color='purple', density=True)
plt.title('OpenCV Result Histogram')
plt.xlabel('Intensity')
plt.ylabel('Probability')

# Row 3: CDFs
input_hist, _ = np.histogram(input_image.ravel(), 256, range=(0, 256))
ref_hist, _ = np.histogram(ref_image.ravel(), 256, range=(0, 256))
manual_hist, _ = np.histogram(result_manual.ravel(), 256, range=(0, 256))
opencv_hist, _ = np.histogram(result_opencv.ravel(), 256, range=(0, 256))

input_cdf = input_hist.cumsum() / input_hist.sum()
ref_cdf = ref_hist.cumsum() / ref_hist.sum()
manual_cdf = manual_hist.cumsum() / manual_hist.sum()
opencv_cdf = opencv_hist.cumsum() / opencv_hist.sum()

plt.subplot(4, 4, 9)
plt.plot(input_cdf, color='blue', label='Input')
plt.title('Input CDF')
plt.xlabel('Intensity')
plt.ylabel('Cumulative Probability')

plt.subplot(4, 4, 10)
plt.plot(ref_cdf, color='green', label='Reference')
plt.title('Reference CDF')
plt.xlabel('Intensity')
plt.ylabel('Cumulative Probability')

plt.subplot(4, 4, 11)
plt.plot(manual_cdf, color='red', label='Manual')
plt.plot(ref_cdf, color='green', linestyle='--', alpha=0.5, label='Target')
plt.title('Manual Result CDF vs Target')
plt.xlabel('Intensity')
plt.ylabel('Cumulative Probability')
plt.legend()

plt.subplot(4, 4, 12)
plt.plot(opencv_cdf, color='purple', label='OpenCV')
plt.plot(ref_cdf, color='green', linestyle='--', alpha=0.5, label='Target')
plt.title('OpenCV Result CDF vs Target')
plt.xlabel('Intensity')
plt.ylabel('Cumulative Probability')
plt.legend()

# Row 4: Analysis plots
plt.subplot(4, 4, 13)
plt.plot(mapping_manual, color='red', label='Manual Mapping')
plt.plot(mapping_opencv, color='purple', alpha=0.7, label='OpenCV Mapping')
plt.title('Intensity Mapping Functions')
plt.xlabel('Input Intensity')
plt.ylabel('Output Intensity')
plt.legend()

plt.subplot(4, 4, 14)
# Compare histograms
x = np.arange(5)
metrics = ['Mean', 'Std', 'Min', 'Max', 'Median']
input_vals = [input_stats['mean'], input_stats['std'], input_stats['min'], input_stats['max'], input_stats['median']]
ref_vals = [ref_stats['mean'], ref_stats['std'], ref_stats['min'], ref_stats['max'], ref_stats['median']]

plt.bar(x - 0.2, input_vals, 0.4, label='Input', alpha=0.7)
plt.bar(x + 0.2, ref_vals, 0.4, label='Reference', alpha=0.7)
plt.xlabel('Metrics')
plt.ylabel('Values')
plt.title('Statistical Comparison')
plt.xticks(x, metrics, rotation=45)
plt.legend()

plt.subplot(4, 4, 15)
# Difference analysis
diff_manual = np.abs(result_manual.astype(float) - input_image.astype(float))
diff_opencv = np.abs(result_opencv.astype(float) - input_image.astype(float))
plt.hist(diff_manual.ravel(), 50, alpha=0.7, label='Manual vs Input', color='red')
plt.hist(diff_opencv.ravel(), 50, alpha=0.7, label='OpenCV vs Input', color='purple')
plt.title('Intensity Change Distribution')
plt.xlabel('Absolute Difference')
plt.ylabel('Frequency')
plt.legend()

plt.subplot(4, 4, 16)
# Method comparison
method_diff = np.abs(result_manual.astype(float) - result_opencv.astype(float))
plt.imshow(method_diff, cmap='hot')
plt.title('Manual vs OpenCV Difference')
plt.colorbar(label='Absolute Difference')
plt.axis('off')

plt.tight_layout()
plt.show()

# Print comprehensive analysis
print("\n" + "="*60)
print("HISTOGRAM SPECIFICATION ANALYSIS")
print("="*60)

print(f"\nInput Image Statistics:")
print(f"  Mean: {input_stats['mean']:.2f}")
print(f"  Std Dev: {input_stats['std']:.2f}")
print(f"  Range: [{input_stats['min']}, {input_stats['max']}]")
print(f"  Median: {input_stats['median']:.2f}")

print(f"\nReference Image Statistics:")
print(f"  Mean: {ref_stats['mean']:.2f}")
print(f"  Std Dev: {ref_stats['std']:.2f}")
print(f"  Range: [{ref_stats['min']}, {ref_stats['max']}]")
print(f"  Median: {ref_stats['median']:.2f}")

print(f"\nManual Result Statistics:")
print(f"  Mean: {result_manual_stats['mean']:.2f}")
print(f"  Std Dev: {result_manual_stats['std']:.2f}")
print(f"  Range: [{result_manual_stats['min']}, {result_manual_stats['max']}]")
print(f"  Median: {result_manual_stats['median']:.2f}")

print(f"\nOpenCV Result Statistics:")
print(f"  Mean: {result_opencv_stats['mean']:.2f}")
print(f"  Std Dev: {result_opencv_stats['std']:.2f}")
print(f"  Range: [{result_opencv_stats['min']}, {result_opencv_stats['max']}]")
print(f"  Median: {result_opencv_stats['median']:.2f}")

# Calculate how well the results match the reference
manual_mean_diff = abs(result_manual_stats['mean'] - ref_stats['mean'])
opencv_mean_diff = abs(result_opencv_stats['mean'] - ref_stats['mean'])
manual_std_diff = abs(result_manual_stats['std'] - ref_stats['std'])
opencv_std_diff = abs(result_opencv_stats['std'] - ref_stats['std'])

print(f"\nMatching Quality Analysis:")
print(f"  Manual Method - Mean difference: {manual_mean_diff:.2f}")
print(f"  Manual Method - Std difference: {manual_std_diff:.2f}")
print(f"  OpenCV Method - Mean difference: {opencv_mean_diff:.2f}")
print(f"  OpenCV Method - Std difference: {opencv_std_diff:.2f}")

# Method comparison
method_difference = np.mean(method_diff)
print(f"\nImplementation Verification:")
print(f"  Average difference between Manual and OpenCV: {method_difference:.2f}")
if method_difference < 5.0:
    print("  ✓ Manual implementation closely matches OpenCV!")
else:
    print("  ⚠ Manual implementation differs from OpenCV")

# Histogram matching success
ref_mean = ref_stats['mean']
manual_achieved_mean = result_manual_stats['mean']
opencv_achieved_mean = result_opencv_stats['mean']

print(f"\nHistogram Specification Success:")
print(f"  Target mean brightness: {ref_mean:.2f}")
print(f"  Manual method achieved: {manual_achieved_mean:.2f} ({(manual_achieved_mean/ref_mean)*100:.1f}% of target)")
print(f"  OpenCV method achieved: {opencv_achieved_mean:.2f} ({(opencv_achieved_mean/ref_mean)*100:.1f}% of target)")

print("\nExperiment completed successfully! 🎯")