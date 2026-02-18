import cv2
import os

# Get the directory where this script is located
script_dir = os.path.dirname(os.path.abspath(__file__))

# Create the full path to the image
image_path = os.path.join(script_dir, 'testOpenCv.jpg')

# Load the image using the full path
image = cv2.imread(image_path)

if image is None:
    print(f"Error: Could not find image at {image_path}")
else:
    gray_image = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    cv2.imshow('Grayscale', gray_image)
    # View a 5x5 matrix of pixels starting from (100, 100)
    region = gray_image[100:105, 100:105]

    print("Pixel values in the 5x5 region:")
    print(region)
    cv2.waitKey(0)
    cv2.destroyAllWindows()

# # View a 5x5 matrix of pixels starting from (100, 100)
# region = image[100:105, 100:105]

# print("Pixel values in the 5x5 region:")
# print(region)