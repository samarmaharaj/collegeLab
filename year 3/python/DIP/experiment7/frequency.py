import cv2
import numpy as np
import matplotlib.pyplot as plt
import os

# ---------------------------------------------------------
# Filter Mask Generators (Masks sized to match the image)
# ---------------------------------------------------------

def get_ideal_lpf(shape, d0):
    """Ideal Low Pass Filter Mask"""
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = (D <= d0).astype(np.float32)
    return mask

def get_ideal_hpf(shape, d0):
    """Ideal High Pass Filter Mask"""
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = (D > d0).astype(np.float32)
    return mask

def get_gaussian_lpf(shape, d0):
    """Gaussian Low Pass Filter Mask"""
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = np.exp(-(D**2) / (2 * (d0**2))).astype(np.float32)
    return mask

def get_gaussian_hpf(shape, d0):
    """Gaussian High Pass Filter Mask"""
    rows, cols = shape
    crow, ccol = rows // 2, cols // 2
    U, V = np.ogrid[:rows, :cols]
    D = np.sqrt((U - crow)**2 + (V - ccol)**2)
    mask = (1 - np.exp(-(D**2) / (2 * (d0**2)))).astype(np.float32)
    return mask

# ---------------------------------------------------------
# Frequency Domain Application
# ---------------------------------------------------------

def apply_frequency_filter(image, filter_generator, d0):
    """
    Applies a frequency domain filter separately on each of the 3 planes (R, G, B)
    """
    # Split the image into its 3 channels
    b, g, r = cv2.split(image)
    channels = [b, g, r]
    filtered_channels = []
    
    for channel in channels:
        # 1. Transform to frequency domain using Fast Fourier Transform (FFT)
        f_transform = np.fft.fft2(channel)
        
        # 2. Shift the zero-frequency component to the center of the spectrum
        f_shift = np.fft.fftshift(f_transform)
        
        # 3. Generate the 2D mask matching the channel's shape and apply it
        mask = filter_generator(channel.shape, d0)
        filtered_shift = f_shift * mask
        
        # 4. Inverse shift, then Inverse FFT back to spatial domain
        f_ishift = np.fft.ifftshift(filtered_shift)
        img_back = np.fft.ifft2(f_ishift)
        
        # 5. Extract magnitude and clip values to valid image range [0, 255]
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
    image_path = os.path.join(current_dir, 'input.png')
    
    # Load the image
    img = cv2.imread(image_path)
    if img is None:
        print(f"Error: Could not load image at '{image_path}'.")
        print("Please ensure an image named 'input_image.jpg' exists in the script directory.")
        return
    
    # Convert BGR (OpenCV format) to RGB for Matplotlib visualization
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    
    # Define a cutoff frequency (D0)
    # 50 is a good baseline. Lower values = stronger blur (LPF) or darker edges (HPF)
    D0 = 50 
    
    print("Applying Ideal Low Pass Filter...")
    img_ideal_lpf = apply_frequency_filter(img_rgb, get_ideal_lpf, D0)

    # D0 = 30
    
    print("Applying Ideal High Pass Filter...")
    img_ideal_hpf = apply_frequency_filter(img_rgb, get_ideal_hpf, D0)

    # D0 = 100
    
    print("Applying Gaussian Low Pass Filter...")
    img_gauss_lpf = apply_frequency_filter(img_rgb, get_gaussian_lpf, D0)

    # D0 = 30
    
    print("Applying Gaussian High Pass Filter...")
    img_gauss_hpf = apply_frequency_filter(img_rgb, get_gaussian_hpf, D0)
    
    # Display the results
    plt.figure(figsize=(15, 10))
    
    plt.subplot(2, 3, 2)
    plt.title("Original Clean Image")
    plt.imshow(img_rgb)
    plt.axis('off')
    
    plt.subplot(2, 3, 4)
    plt.title(f"A) Ideal LPF (D0={D0})")
    plt.imshow(img_ideal_lpf)
    plt.axis('off')
    
    plt.subplot(2, 3, 5)
    plt.title(f"C) Gaussian LPF (D0={D0})")
    plt.imshow(img_gauss_lpf)
    plt.axis('off')
    
    plt.subplot(2, 3, 6)
    plt.title("Comparison: LPFs")
    plt.text(0.5, 0.5, "Notice the ringing\nin Ideal vs Smooth\nin Gaussian", 
             horizontalalignment='center', verticalalignment='center', fontsize=12)
    plt.axis('off')
    
    plt.figure(figsize=(10, 5))
    
    plt.subplot(1, 2, 1)
    plt.title(f"B) Ideal HPF (D0={D0})")
    plt.imshow(img_ideal_hpf)
    plt.axis('off')
    
    plt.subplot(1, 2, 2)
    plt.title(f"D) Gaussian HPF (D0={D0})")
    plt.imshow(img_gauss_hpf)
    plt.axis('off')
    
    plt.tight_layout()
    plt.show()

if __name__ == "__main__":
    main()