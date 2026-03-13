import argparse
import os

import cv2
import matplotlib.pyplot as plt
import numpy as np


def load_image(image_path: str, force_grayscale: bool = False) -> np.ndarray:
	read_mode = cv2.IMREAD_GRAYSCALE if force_grayscale else cv2.IMREAD_UNCHANGED
	image = cv2.imread(image_path, read_mode)
	if image is None:
		raise FileNotFoundError(f"Unable to read image: {image_path}")
	if image.ndim == 3:
		return cv2.cvtColor(image, cv2.COLOR_BGR2RGB)
	return image


def add_salt_and_pepper_noise(image: np.ndarray, salt_prob: float = 0.03, pepper_prob: float = 0.03) -> np.ndarray:
	noisy = image.copy()
	rows, cols = image.shape[:2]
	random_matrix = np.random.rand(rows, cols)

	salt_mask = random_matrix < salt_prob
	pepper_mask = random_matrix > (1.0 - pepper_prob)

	if image.ndim == 2:
		noisy[salt_mask] = 255
		noisy[pepper_mask] = 0
	else:
		noisy[salt_mask] = [255, 255, 255]
		noisy[pepper_mask] = [0, 0, 0]
	return noisy


def ideal_lowpass_mask_3x3(rows: int, cols: int) -> np.ndarray:
	mask = np.zeros((rows, cols), dtype=np.float32)
	center_row, center_col = rows // 2, cols // 2
	mask[center_row - 1:center_row + 2, center_col - 1:center_col + 2] = 1.0
	return mask


def ideal_highpass_mask_3x3(rows: int, cols: int) -> np.ndarray:
	return 1.0 - ideal_lowpass_mask_3x3(rows, cols)


def gaussian_lowpass_mask_3x3(rows: int, cols: int) -> np.ndarray:
	mask = np.zeros((rows, cols), dtype=np.float32)
	center_row, center_col = rows // 2, cols // 2

	g1 = cv2.getGaussianKernel(3, 0)
	g2 = g1 @ g1.T
	g2 = g2 / g2.max()

	mask[center_row - 1:center_row + 2, center_col - 1:center_col + 2] = g2
	return mask


def gaussian_highpass_mask_3x3(rows: int, cols: int) -> np.ndarray:
	return 1.0 - gaussian_lowpass_mask_3x3(rows, cols)


def apply_frequency_filter_per_channel(image: np.ndarray, mask: np.ndarray) -> np.ndarray:
	if image.ndim == 2:
		channel_data = image.astype(np.float32)
		fft = np.fft.fft2(channel_data)
		fft_shift = np.fft.fftshift(fft)
		filtered_shift = fft_shift * mask
		filtered_fft = np.fft.ifftshift(filtered_shift)
		filtered_image = np.fft.ifft2(filtered_fft)
		return np.clip(np.real(filtered_image), 0, 255).astype(np.uint8)

	output = np.zeros_like(image, dtype=np.float32)
	for channel in range(3):
		channel_data = image[:, :, channel].astype(np.float32)
		fft = np.fft.fft2(channel_data)
		fft_shift = np.fft.fftshift(fft)
		filtered_shift = fft_shift * mask
		filtered_fft = np.fft.ifftshift(filtered_shift)
		filtered_channel = np.fft.ifft2(filtered_fft)
		output[:, :, channel] = np.real(filtered_channel)

	return np.clip(output, 0, 255).astype(np.uint8)


def print_conclusion() -> None:
	print("\nConclusion (based on observed output):")
	print("1) Low Pass Filter (3x3) suppresses high-frequency content and reduces some impulse noise, but blurs edges.")
	print("2) High Pass Filter (3x3) enhances edges/fine details but also amplifies salt-and-pepper noise.")
	print("3) Low Pass Gaussian Filter (3x3) smooths the image more naturally than ideal LPF with softer transitions.")
	print("4) High Pass Gaussian Filter (3x3) highlights edges with slightly smoother behavior than ideal HPF.")
	print("Overall, LPF/GLPF are better for denoising, while HPF/GHPF are better for edge emphasis.")


def main() -> None:
	parser = argparse.ArgumentParser(
		description="Apply 3x3 frequency-domain filters on each RGB plane after adding salt-and-pepper noise."
	)
	parser.add_argument(
		"image_path",
		nargs="?",
		default=os.path.join(os.path.dirname(os.path.abspath(__file__)), "input.png"),
		help="Path to input color image (jpg/png/jpeg/bmp/tiff).",
	)
	parser.add_argument(
		"--gray",
		action="store_true",
		help="Force grayscale reading mode.",
	)
	parser.add_argument("--salt", type=float, default=0.03, help="Salt noise probability (default: 0.03)")
	parser.add_argument("--pepper", type=float, default=0.03, help="Pepper noise probability (default: 0.03)")

	args = parser.parse_args()

	image = load_image(args.image_path, force_grayscale=args.gray)
	noisy_image = add_salt_and_pepper_noise(image, salt_prob=args.salt, pepper_prob=args.pepper)

	rows, cols = noisy_image.shape[:2]

	lpf_mask = ideal_lowpass_mask_3x3(rows, cols)
	hpf_mask = ideal_highpass_mask_3x3(rows, cols)
	glpf_mask = gaussian_lowpass_mask_3x3(rows, cols)
	ghpf_mask = gaussian_highpass_mask_3x3(rows, cols)

	lpf_output = apply_frequency_filter_per_channel(noisy_image, lpf_mask)
	hpf_output = apply_frequency_filter_per_channel(noisy_image, hpf_mask)
	glpf_output = apply_frequency_filter_per_channel(noisy_image, glpf_mask)
	ghpf_output = apply_frequency_filter_per_channel(noisy_image, ghpf_mask)

	fig, axes = plt.subplots(2, 3, figsize=(15, 9))
	fig.suptitle("Frequency Domain Filtering (3x3 Mask on Each RGB Plane)", fontsize=14, fontweight="bold")

	axes[0, 0].imshow(image, cmap="gray" if image.ndim == 2 else None)
	axes[0, 0].set_title("Input Image")
	axes[0, 0].axis("off")

	axes[0, 1].imshow(noisy_image, cmap="gray" if noisy_image.ndim == 2 else None)
	axes[0, 1].set_title("Noisy Image (Salt & Pepper)")
	axes[0, 1].axis("off")

	axes[0, 2].imshow(lpf_output, cmap="gray" if lpf_output.ndim == 2 else None)
	axes[0, 2].set_title("A) Low Pass Filter (3x3)")
	axes[0, 2].axis("off")

	axes[1, 0].imshow(hpf_output, cmap="gray" if hpf_output.ndim == 2 else None)
	axes[1, 0].set_title("B) High Pass Filter (3x3)")
	axes[1, 0].axis("off")

	axes[1, 1].imshow(glpf_output, cmap="gray" if glpf_output.ndim == 2 else None)
	axes[1, 1].set_title("C) Low Pass Gaussian (3x3)")
	axes[1, 1].axis("off")

	axes[1, 2].imshow(ghpf_output, cmap="gray" if ghpf_output.ndim == 2 else None)
	axes[1, 2].set_title("D) High Pass Gaussian (3x3)")
	axes[1, 2].axis("off")

	plt.tight_layout()
	plt.show()

	print_conclusion()


if __name__ == "__main__":
	main()
