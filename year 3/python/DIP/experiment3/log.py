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

# Apply log transform.
# Convert img to float32 to prevent overflow/underflow issues
img_float = np.float32(img)
c = 255 / (np.log(1 + np.max(img_float)))
log_transformed = c * np.log(1 + img_float)

# Specify the data type.
log_transformed = np.array(log_transformed, dtype = np.uint8)

# Save the output.
cv2.imwrite('log_transformed.jpg', log_transformed)

# Display using matplotlib
plt.figure(figsize=(10, 5))

plt.subplot(1, 2, 1)
plt.imshow(img, cmap='gray')
plt.title('Original Image')
plt.axis('off')

plt.subplot(1, 2, 2)
plt.imshow(log_transformed, cmap='gray')
plt.title('Log Transformed')
plt.axis('off')

plt.show()