#image negative transformation s=(L−1)−r
import cv2
import matplotlib.pyplot as plt
import os
import numpy as np

# Open the image.
# Load original image in grayscale using a relative path
script_dir = os.path.dirname(os.path.abspath(__file__))
img_path = os.path.join(script_dir, 'Grayscale.png')
img = cv2.imread(img_path, 0)
if img is None:
    print("Error: Could not load image 'Grayscale.png'. Check file path.")
    exit()

# Standard Image Negative (L-1 = 255)
negative_255 = 255 - img

# Negative with L-1 = 200 (Resulting values < 0 wrap around or clip depending on dtype handling)
# Using abs() to create a valid visual effect for demonstration
negative_200 = np.abs(200 - img)

# Negative with L-1 = 150
negative_150 = np.abs(150 - img)

# Display
plt.figure(figsize=(12, 4))

plt.subplot(2, 2, 1)
plt.title("Original Image")
plt.imshow(img, cmap='gray')
plt.axis('off')

plt.subplot(2, 2, 2)
plt.title("Negative (255 - r)")
plt.imshow(negative_255, cmap='gray', vmin=0, vmax=255)
plt.axis('off')

plt.subplot(2, 2, 3)
plt.title("Diff (200 - r)")
plt.imshow(negative_200, cmap='gray', vmin=0, vmax=255)
plt.axis('off')

plt.subplot(2, 2, 4)
plt.title("Diff (150 - r)")
plt.imshow(negative_150, cmap='gray', vmin=0, vmax=255)
plt.axis('off')

plt.show()