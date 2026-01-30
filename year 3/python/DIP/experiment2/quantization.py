import numpy as np
import matplotlib.pyplot as plt
import cv2
import os

def quantize_image(img, bits):
    """
    Reduces the number of intensity levels to 2^bits.
    """
    levels = 2**bits
    interval_size = 256 // levels
    
    # Quantize: integer division followed by multiplication
    quantized_img = (img // interval_size) * interval_size
    return quantized_img

# Load original image in grayscale using a relative path
script_dir = os.path.dirname(os.path.abspath(__file__))
img_path = os.path.join(script_dir, 'Grayscale.png')
img = cv2.imread(img_path, 0)

if img is None:
    print("Error: Could not load image 'Grayscale.png'. Check file path.")
    exit()

# Apply quantization for different bit depths
q_4 = quantize_image(img, 4) # 16 levels
q_2 = quantize_image(img, 2)
q_1 = quantize_image(img, 1) 

# Visualization
# Specific titles with information about levels
qtitled = [
    'Original Image (8-bit)\n256 Intensity Levels',
    'Quantized to 4-bit\n16 Intensity Levels', 
    'Quantized to 2-bit\n4 Intensity Levels', 
    'Quantized to 1-bit\n2 Intensity Levels'
]
qimages = [img, q_4, q_2, q_1]

plt.figure(figsize=(10, 10))
# Add a main title for the entire figure
plt.suptitle('Image Quantization: Reducing Intensity Levels', fontsize=16)

for i in range(4):
    plt.subplot(2, 2, i+1)
    plt.imshow(qimages[i], cmap='gray')
    plt.title(qtitled[i])
    plt.axis('off')

plt.tight_layout()
plt.show()