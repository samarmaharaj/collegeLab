import cv2
import matplotlib.pyplot as plt
import os

def downsample_image(img, k):
    """
    Samples the image by taking every k-th pixel.
    """
    # Using numpy slicing: [start:stop:step]
    sampled_img = img[::k, ::k]
    return sampled_img

# Load original image in grayscale using a relative path
script_dir = os.path.dirname(os.path.abspath(__file__))
img_path = os.path.join(script_dir, 'Grayscale.png')
img = cv2.imread(img_path, 0)
if img is None:
    print("Error: Could not load image 'Grayscale.png'. Check file path.")
    exit()

# Apply sampling with different factors
sampled_2 = downsample_image(img, 2)
sampled_8 = downsample_image(img, 8)
sampled_16 = downsample_image(img, 16)

# Visualization
images = [img, sampled_2, sampled_8, sampled_16]
labels = ['Original', 'Sampled (Factor 2)', 'Sampled (Factor 8)', 'Sampled (Factor 16)']

plt.figure(figsize=(10, 10))
plt.suptitle('Image Sampling', fontsize=16) # Main Title

for i in range(4):
    plt.subplot(2, 2, i+1)
    plt.imshow(images[i], cmap='gray')
    
    # Get dimensions dynamically
    h, w = images[i].shape
    plt.title(f"{labels[i]}\nDimensions: {w} x {h}")
    plt.axis('off')

plt.tight_layout()
plt.show()