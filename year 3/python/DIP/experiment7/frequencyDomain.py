import cv2
import numpy as np
import matplotlib.pyplot as plt
import os
import random

def add_salt_and_pepper_noise(image, prob=0.05):
    """
    Adds salt and pepper noise to an image.
    prob: Probability of the noise (percentage of pixels affected)
    """
    noisy_image = np.copy(image)
    row, col, ch = noisy_image.shape
    
    # Generate random matrix to determine salt and pepper positions
    num_salt = np.ceil(prob * image.size * 0.5)
    num_pepper = np.ceil(prob * image.size * 0.5)
    
    # Add Salt (white pixels)
    coords = [np.random.randint(0, i - 1, int(num_salt)) for i in image.shape[:2]]
    noisy_image[coords[0], coords[1], :] = 255
    
    # Add Pepper (black pixels)
    coords = [np.random.randint(0, i - 1, int(num_pepper)) for i in image.shape[:2]]
    noisy_image[coords[0], coords[1], :] = 0
    
    return noisy_image

# ---------------------------------------------------------
# Filter Mask Generators
# ---------------------------------------------------------

def get_ideal_lpf(shape, d0):
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = D <= d0
    return mask.astype(np.float32)

def get_ideal_hpf(shape, d0):
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = D > d0
    return mask.astype(np.float32)

def get_gaussian_lpf(shape, d0):
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = np.exp(-(D**2) / (2 * (d0**2)))
    return mask.astype(np.float32)

def get_gaussian_hpf(shape, d0):
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = 1 - np.exp(-(D**2) / (2 * (d0**2)))
    return mask.astype(np.float32)

# ---------------------------------------------------------
# Frequency Domain Application
# ---------------------------------------------------------

def apply_frequency_filter(image, filter_generator, d0):
    """
    Applies a frequency domain filter separately on each of the 3 planes (R, G, B)
    """
    # Split the image into its 3 channels (Blue, Green, Red)
    b, g, r = cv2.split(image)
    channels = [b, g, r]
    filtered_channels = []
    
    # Generate the 2D mask (same size as a single channel)
    mask = filter_generator(b.shape, d0)
    
    # Process each plane independently
    for channel in channels:
        # 1. Transform to frequency domain
        f_transform = np.fft.fft2(channel)
        # 2. Shift the zero-frequency component to the center
        f_shift = np.fft.fftshift(f_transform)
        
        # 3. Apply the mask (multiply)
        filtered_shift = f_shift * mask
        
        # 4. Inverse shift, then inverse FFT back to spatial domain
        f_ishift = np.fft.ifftshift(filtered_shift)
        img_back = np.fft.ifft2(f_ishift)
        
        # 5. Extract magnitude and clip to [0, 255]
        img_back = np.abs(img_back)
        img_back = np.clip(img_back, 0, 255).astype(np.uint8)
        
        filtered_channels.append(img_back)
    
    # Merge the filtered channels back into an RGB image
    filtered_image = cv2.merge((filtered_channels[0], filtered_channels[1], filtered_channels[2]))
    return filtered_image

# ---------------------------------------------------------
# Main Execution
# ---------------------------------------------------------
def main():
    # Use os.path for relative image positioning
    current_dir = os.path.dirname(os.path.abspath(__file__))
    # Assuming the image is in the same directory and named 'input_image.jpg'
    image_path = os.path.join(current_dir, 'input.png')
    
    # Load the image
    img = cv2.imread(image_path)
    if img is None:
        print(f"Error: Could not load image at {image_path}.")
        print("Please ensure an image named 'input_image.jpg' exists in the script directory.")
        return
    
    # Convert BGR (OpenCV format) to RGB for Matplotlib visualization
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    
    # Add Salt and Pepper Noise
    noisy_img_rgb = add_salt_and_pepper_noise(img_rgb, prob=0.05)
    
    # Define a cutoff frequency (D0)
    # A smaller value means more blurring (LPF) or more edge extraction (HPF)
    D0 = 50 
    
    print("Applying Ideal Low Pass Filter...")
    img_ideal_lpf = apply_frequency_filter(noisy_img_rgb, get_ideal_lpf, D0)
    
    print("Applying Ideal High Pass Filter...")
    img_ideal_hpf = apply_frequency_filter(noisy_img_rgb, get_ideal_hpf, D0)
    
    print("Applying Gaussian Low Pass Filter...")
    img_gauss_lpf = apply_frequency_filter(noisy_img_rgb, get_gaussian_lpf, D0)
    
    print("Applying Gaussian High Pass Filter...")
    img_gauss_hpf = apply_frequency_filter(noisy_img_rgb, get_gaussian_hpf, D0)
    
    # Display the results
    plt.figure(figsize=(15, 10))
    
    plt.subplot(2, 3, 1)
    plt.title("Original Clean Image")
    plt.imshow(img_rgb)
    plt.axis('off')
    
    plt.subplot(2, 3, 2)
    plt.title("Input Image (Salt & Pepper Noise)")
    plt.imshow(noisy_img_rgb)
    plt.axis('off')
    
    plt.subplot(2, 3, 4)
    plt.title(f"A) Ideal LPF (D0={D0})")
    plt.imshow(img_ideal_lpf)
    plt.axis('off')
    
    plt.subplot(2, 3, 5)
    plt.title(f"B) Ideal HPF (D0={D0})")
    plt.imshow(img_ideal_hpf)
    plt.axis('off')
    
    plt.subplot(2, 3, 6)
    plt.title(f"C) Gaussian LPF (D0={D0})")
    plt.imshow(img_gauss_lpf)
    plt.axis('off')
    
    plt.figure(figsize=(5, 5)) # separate figure due to grid size
    plt.title(f"D) Gaussian HPF (D0={D0})")
    plt.imshow(img_gauss_hpf)
    plt.axis('off')
    
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()