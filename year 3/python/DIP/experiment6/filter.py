"""
Digital Image Enhancement using Median and Laplacian Filters
Experiment 6: Noise Reduction and Edge Enhancement

HOW TO USE YOUR OWN IMAGES:
===========================

Method 1 - Command Line:
    python filter.py my_image.jpg
    python filter.py "C:/full/path/to/image.png"
    python filter.py ../images/test.jpg

Method 2 - Place in same folder:
    Put your image in the same folder as this script and name it:
    input.jpg, sample.jpg, test.jpg, or image.jpg (or .png, .jpeg)

Method 3 - Interactive Mode:
    Just run: python filter.py
    The program will ask you to enter the path interactively

Supported Formats: .jpg, .jpeg, .png, .bmp, .tiff

Author: Student
Date: February 20, 2026
"""

import cv2
import numpy as np
import matplotlib.pyplot as plt
from matplotlib.patches import Rectangle
import os
import sys
import argparse

class ImageFilterProcessor:
    def __init__(self):
        self.original_image = None
        self.noisy_image = None
        
    def load_image(self, image_path):
        """Load an image from the specified path"""
        # Clean up the path
        image_path = image_path.strip()
        
        if not os.path.exists(image_path):
            print(f"❌ Image not found at: {image_path}")
            return None
        
        # Check if it's a valid image format
        valid_extensions = ['.jpg', '.jpeg', '.png', '.bmp', '.tiff', '.tif']
        file_ext = os.path.splitext(image_path)[1].lower()
        
        if file_ext not in valid_extensions:
            print(f"❌ Unsupported file format: {file_ext}")
            print(f"Supported formats: {', '.join(valid_extensions)}")
            return None
        
        try:
            image = cv2.imread(image_path)
            if image is None:
                print(f"❌ Could not decode image: {image_path}")
                print("Please check if the file is a valid image.")
                return None
            
            # Convert BGR to RGB for matplotlib display
            image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
            self.original_image = image
            
            print(f"✅ Successfully loaded image: {os.path.basename(image_path)}")
            print(f"   Dimensions: {image.shape[1]}×{image.shape[0]} pixels")
            print(f"   File size: {os.path.getsize(image_path) / 1024:.1f} KB")
            
            return image
            
        except Exception as e:
            print(f"❌ Error loading image: {str(e)}")
            return None
    
    def create_sample_image(self):
        """Create a sample image with various features for testing"""
        # Create a 300x300x3 sample image
        image = np.zeros((300, 300, 3), dtype=np.uint8)
        
        # Add some geometric shapes with different colors
        cv2.rectangle(image, (50, 50), (150, 150), (255, 0, 0), -1)  # Red rectangle
        cv2.circle(image, (200, 100), 40, (0, 255, 0), -1)  # Green circle
        cv2.rectangle(image, (100, 200), (250, 280), (0, 0, 255), -1)  # Blue rectangle
        
        # Add some text-like patterns
        for i in range(5):
            cv2.line(image, (20, 20 + i*10), (80, 20 + i*10), (255, 255, 255), 2)
        
        self.original_image = image
        return image
    
    def add_salt_pepper_noise(self, image, salt_prob=0.05, pepper_prob=0.05):
        """Add salt and pepper noise to the image"""
        noisy_image = image.copy()
        
        # Generate random matrix
        random_matrix = np.random.random(image.shape[:2])
        
        # Add salt noise (white pixels)
        salt_mask = random_matrix < salt_prob
        noisy_image[salt_mask] = 255
        
        # Add pepper noise (black pixels)
        pepper_mask = random_matrix > (1 - pepper_prob)
        noisy_image[pepper_mask] = 0
        
        self.noisy_image = noisy_image
        return noisy_image
    
    def apply_median_filter(self, image, kernel_size=3):
        """
        Apply median filter to each plane (R, G, B) of the image
        Args:
            image: Input image (RGB format)
            kernel_size: Size of the median filter kernel (default: 3x3)
        Returns:
            filtered_image: Image after applying median filter
        """
        print(f"Applying median filter with {kernel_size}x{kernel_size} kernel...")
        
        # Apply median filter to each channel separately
        filtered_image = np.zeros_like(image)
        
        for channel in range(3):  # For R, G, B channels
            filtered_image[:, :, channel] = cv2.medianBlur(image[:, :, channel], kernel_size)
        
        return filtered_image
    
    def apply_laplacian_filter(self, image, apply_sharpening=True):
        """
        Apply Laplacian filter to each plane (R, G, B) of the image
        Args:
            image: Input image (RGB format)
            apply_sharpening: Whether to apply sharpening (default: True)
        Returns:
            result_image: Image after applying Laplacian filter and sharpening
        """
        print("Applying Laplacian filter with 3x3 kernel...")
        
        # Define 3x3 Laplacian kernel
        laplacian_kernel = np.array([[0, -1, 0],
                                   [-1, 4, -1],
                                   [0, -1, 0]], dtype=np.float32)
        
        laplacian_image = np.zeros_like(image, dtype=np.float32)
        
        # Apply Laplacian filter to each channel
        for channel in range(3):  # For R, G, B channels
            laplacian_image[:, :, channel] = cv2.filter2D(
                image[:, :, channel].astype(np.float32), -1, laplacian_kernel
            )
        
        if apply_sharpening:
            # Sharpening: Add Laplacian to original image
            sharpening_factor = 0.8
            result_image = image.astype(np.float32) + sharpening_factor * laplacian_image
            
            # Clip values to valid range [0, 255] and convert to uint8
            result_image = np.clip(result_image, 0, 255).astype(np.uint8)
            
            return result_image, laplacian_image
        else:
            # Just return the Laplacian filtered image (scaled for visualization)
            laplacian_scaled = np.clip(laplacian_image + 127, 0, 255).astype(np.uint8)
            return laplacian_scaled, laplacian_image
    
    def display_results(self, original, noisy, median_filtered, laplacian_sharpened, laplacian_only):
        """Display all images in a comprehensive layout"""
        fig, axes = plt.subplots(2, 3, figsize=(15, 10))
        fig.suptitle('Digital Image Enhancement using Median and Laplacian Filters', 
                    fontsize=14, fontweight='bold')
        
        # Original image
        axes[0, 0].imshow(original)
        axes[0, 0].set_title('Original Image')
        axes[0, 0].axis('off')
        
        # Noisy image
        axes[0, 1].imshow(noisy)
        axes[0, 1].set_title('Noisy Image\\n(Salt & Pepper Noise)')
        axes[0, 1].axis('off')
        
        # Median filtered
        axes[0, 2].imshow(median_filtered)
        axes[0, 2].set_title('Median Filter Applied\\n(3×3 kernel)')
        axes[0, 2].axis('off')
        
        # Laplacian filter result (for visualization)
        axes[1, 0].imshow(laplacian_only, cmap='gray')
        axes[1, 0].set_title('Laplacian Filter Result\\n(Edge Detection)')
        axes[1, 0].axis('off')
        
        # Laplacian sharpened
        axes[1, 1].imshow(laplacian_sharpened)
        axes[1, 1].set_title('Laplacian Sharpened\\n(Original + Laplacian)')
        axes[1, 1].axis('off')
        
        # Comparison plot
        axes[1, 2].imshow(np.hstack([median_filtered[:, :150], laplacian_sharpened[:, 150:]]))
        axes[1, 2].set_title('Comparison\\n(Left: Median | Right: Laplacian)')
        axes[1, 2].axis('off')
        
        # Add a dividing line for the comparison
        axes[1, 2].axvline(x=150, color='yellow', linewidth=2, linestyle='--')
        
        plt.tight_layout()
        plt.show()
    
    def calculate_image_quality_metrics(self, original, processed, filter_name):
        """Calculate and display image quality metrics"""
        # Convert to grayscale for metric calculation
        original_gray = cv2.cvtColor(original, cv2.COLOR_RGB2GRAY)
        processed_gray = cv2.cvtColor(processed, cv2.COLOR_RGB2GRAY)
        
        # Mean Squared Error (MSE)
        mse = np.mean((original_gray.astype(np.float32) - processed_gray.astype(np.float32)) ** 2)
        
        # Peak Signal-to-Noise Ratio (PSNR)
        if mse == 0:
            psnr = float('inf')
        else:
            max_pixel = 255.0
            psnr = 20 * np.log10(max_pixel / np.sqrt(mse))
        
        print(f"\\n{filter_name} Quality Metrics:")
        print(f"MSE: {mse:.2f}")
        print(f"PSNR: {psnr:.2f} dB")
        
        return mse, psnr

def get_user_image_path():
    """Interactive function to get image path from user"""
    print("\\nChoose an option to provide your image:")
    print("1. Enter full path to your image")
    print("2. Enter just filename (if image is in current directory)")
    print("3. Use sample image")
    
    choice = input("Enter your choice (1/2/3): ").strip()
    
    if choice == '1':
        return input("Enter full path to your image: ").strip().strip('"')
    elif choice == '2':
        filename = input("Enter image filename: ").strip()
        return os.path.join(os.getcwd(), filename)
    else:
        return None

def print_conclusions():
    """Print detailed conclusions based on filter observations"""
    print("\\n" + "="*80)
    print("CONCLUSIONS AND OBSERVATIONS")
    print("="*80)
    
    print("\\n1. MEDIAN FILTER ANALYSIS:")
    print("-" * 40)
    print("• Effectively removes salt and pepper noise while preserving edges")
    print("• Works by replacing each pixel value with the median of neighboring pixels")
    print("• Non-linear filter that maintains sharp edges unlike linear smoothing filters")
    print("• 3×3 kernel size provides good balance between noise removal and detail preservation")
    print("• Particularly effective for impulse noise (salt & pepper noise)")
    print("• Does not blur edges significantly, making it superior to Gaussian blur for noise reduction")
    
    print("\\n2. LAPLACIAN FILTER ANALYSIS:")
    print("-" * 40)
    print("• Emphasizes regions of rapid intensity change (edges and fine details)")
    print("• Acts as a high-pass filter, enhancing edges and suppressing smooth regions")
    print("• When added to original image (sharpening), it enhances image details")
    print("• Can amplify noise, so works best on less noisy images")
    print("• The 4-connected Laplacian kernel used: [[0,-1,0],[-1,4,-1],[0,-1,0]]")
    print("• Sharpening formula: Enhanced = Original + k × Laplacian (k = sharpening factor)")
    
    print("\\n3. COMPARATIVE ANALYSIS:")
    print("-" * 40)  
    print("• Median Filter: Better for noise reduction, preserves edges")
    print("• Laplacian Filter: Better for edge enhancement and detail sharpening")
    print("• Median filter should be applied before Laplacian for optimal results")
    print("• For images with both noise and blur: Use median filter first, then Laplacian sharpening")

def main(image_path_arg=None):
    """Main execution function"""
    print("Digital Image Enhancement using Median and Laplacian Filters")
    print("=" * 60)
    print("\\nSupported formats: .jpg, .jpeg, .png, .bmp, .tiff")
    
    # Initialize processor
    processor = ImageFilterProcessor()
    
    # Determine image path from various sources
    image_path = None
    
    # 1. Check command line argument
    if image_path_arg:
        image_path = image_path_arg
        print(f"\\nUsing image from command line: {image_path}")
    
    # 2. Try default image paths in current directory
    if not image_path:
        default_paths = [
            "input.jpg", "input.jpeg", "input.png",
            "sample.jpg", "sample.jpeg", "sample.png", 
            "test.jpg", "test.jpeg", "test.png",
            "image.jpg", "image.jpeg", "image.png"
        ]
        
        for path in default_paths:
            if os.path.exists(path):
                image_path = path
                print(f"\\nFound image: {path}")
                break
    
    # 3. Interactive input if no image found
    if not image_path:
        print("\\nNo default image found in current directory.")
        image_path = get_user_image_path()
    
    # 4. Load the image or create sample
    image_loaded = False
    if image_path and os.path.exists(image_path):
        original_image = processor.load_image(image_path)
        if original_image is not None:
            image_loaded = True
            print(f"Successfully loaded: {os.path.basename(image_path)}")
    
    if not image_loaded:
        print("\\nUsing generated sample image for demonstration...")
        original_image = processor.create_sample_image()
    
    print(f"Image dimensions: {original_image.shape}")
    
    # Add salt and pepper noise
    print("\\nAdding salt and pepper noise...")
    noisy_image = processor.add_salt_pepper_noise(original_image, 
                                                 salt_prob=0.05, 
                                                 pepper_prob=0.05)
    
    # Apply median filter
    print("\\n" + "-"*50)
    print("APPLYING MEDIAN FILTER")
    print("-"*50)
    median_filtered = processor.apply_median_filter(noisy_image, kernel_size=3)
    processor.calculate_image_quality_metrics(noisy_image, median_filtered, "Median Filter")
    
    # Apply Laplacian filter with sharpening
    print("\\n" + "-"*50)
    print("APPLYING LAPLACIAN FILTER WITH SHARPENING")
    print("-"*50)
    laplacian_sharpened, laplacian_only = processor.apply_laplacian_filter(original_image, 
                                                                          apply_sharpening=True)
    processor.calculate_image_quality_metrics(original_image, laplacian_sharpened, "Laplacian Sharpening")
    
    # Convert laplacian_only for display (scale to 0-255 range)
    laplacian_display = np.clip(laplacian_only + 127, 0, 255).astype(np.uint8)
    
    # Display all results
    print("\\nDisplaying results...")
    processor.display_results(original_image, noisy_image, median_filtered, 
                            laplacian_sharpened, laplacian_display)
    
    # Print detailed conclusions
    print_conclusions()
    
    # Save results
    try:
        # Generate output filenames based on input
        if image_path:
            base_name = os.path.splitext(os.path.basename(image_path))[0]
            median_output = f"{base_name}_median_filtered.jpg"
            laplacian_output = f"{base_name}_laplacian_sharpened.jpg"
        else:
            median_output = "sample_median_filtered.jpg"
            laplacian_output = "sample_laplacian_sharpened.jpg"
        
        cv2.imwrite(median_output, cv2.cvtColor(median_filtered, cv2.COLOR_RGB2BGR))
        cv2.imwrite(laplacian_output, cv2.cvtColor(laplacian_sharpened, cv2.COLOR_RGB2BGR))
        
        print(f"\\n💾 Results saved:")
        print(f"   📁 {median_output}")
        print(f"   📁 {laplacian_output}")
    except Exception as e:
        print(f"\\n⚠️ Could not save result images: {str(e)}")

if __name__ == "__main__":
    # Parse command line arguments
    parser = argparse.ArgumentParser(
        description='Digital Image Enhancement using Median and Laplacian Filters',
        formatter_class=argparse.RawDescriptionHelpFormatter,
        epilog='''Examples:
  python filter.py                          # Use interactive mode or default images
  python filter.py my_image.jpg            # Use specific image
  python filter.py "C:/path/to/image.png"   # Use full path with spaces
  python filter.py ../images/test.jpg      # Use relative path
        ''')
    parser.add_argument('image', nargs='?', help='Path to input image file')
    args = parser.parse_args()
    
    main(args.image)
