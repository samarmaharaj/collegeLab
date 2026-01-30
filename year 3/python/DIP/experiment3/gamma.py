import cv2
import numpy as np
import os
import matplotlib.pyplot as plt

# Open the image.
# Load original image in grayscale using a relative path
script_dir = os.path.dirname(os.path.abspath(__file__))
img_path = os.path.join(script_dir, 'Grayscale.png')
img = cv2.imread(img_path, 0)
if img is None:
    print("Error: Could not load image 'Grayscale.png'. Check file path.")
    exit()

gamma_values = [0.1, 0.5, 1.2, 2.2]
plt.figure(figsize=(12, 8))

# Show original image
plt.subplot(2, 3, 1)
plt.imshow(img, cmap='gray')
plt.title('Original Image')
plt.axis('off')

# Trying 4 gamma values.
for i, gamma in enumerate(gamma_values):
    
    # Apply gamma correction.
    gamma_corrected = np.array(255*(img / 255) ** gamma, dtype = 'uint8')

    # Save edited images.
    cv2.imwrite('gamma_transformed'+str(gamma)+'.jpg', gamma_corrected)

    # Plot the result
    plt.subplot(2, 3, i + 2)
    plt.imshow(gamma_corrected, cmap='gray')
    plt.title(f'Gamma = {gamma}')
    plt.axis('off')

plt.tight_layout()
plt.show()