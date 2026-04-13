import os

import cv2
import matplotlib.pyplot as plt
import numpy as np


def resolve_image_path(preferred_names):
	"""Return first existing image path from candidate names in script directory."""
	script_dir = os.path.dirname(os.path.abspath(__file__))
	for name in preferred_names:
		candidate = os.path.join(script_dir, name)
		if os.path.exists(candidate):
			return candidate
	return None


def load_rgb_image(image_path):
	bgr = cv2.imread(image_path, cv2.IMREAD_COLOR)
	if bgr is None:
		raise FileNotFoundError(f"Could not read image: {image_path}")
	return cv2.cvtColor(bgr, cv2.COLOR_BGR2RGB)


def add_noise_if_needed(image):
	"""Generate a noisy image when a dedicated noisy file is unavailable."""
	noise = np.random.normal(0, 15, image.shape).astype(np.float32)
	noisy = image.astype(np.float32) + noise
	return np.clip(noisy, 0, 255).astype(np.uint8)


def rgb_to_hsi(rgb):
	"""Convert RGB image [0..255] to HSI where H,S,I are in [0..1]."""
	rgb_f = rgb.astype(np.float32) / 255.0
	r = rgb_f[:, :, 0]
	g = rgb_f[:, :, 1]
	b = rgb_f[:, :, 2]

	intensity = (r + g + b) / 3.0

	min_rgb = np.minimum(np.minimum(r, g), b)
	sum_rgb = r + g + b
	saturation = np.zeros_like(intensity)
	valid = sum_rgb > 1e-8
	saturation[valid] = 1.0 - (3.0 * min_rgb[valid] / sum_rgb[valid])

	numerator = 0.5 * ((r - g) + (r - b))
	denominator = np.sqrt((r - g) ** 2 + (r - b) * (g - b)) + 1e-8
	theta = np.arccos(np.clip(numerator / denominator, -1.0, 1.0))

	hue = np.where(b <= g, theta, 2.0 * np.pi - theta)
	hue = hue / (2.0 * np.pi)

	hsi = np.stack([hue, saturation, intensity], axis=2)
	return np.clip(hsi, 0.0, 1.0)


def hsi_to_rgb(hsi):
	"""Convert HSI image (H,S,I in [0..1]) back to RGB [0..255]."""
	h = (hsi[:, :, 0] * 2.0 * np.pi).astype(np.float32)
	s = np.clip(hsi[:, :, 1], 0.0, 1.0).astype(np.float32)
	i = np.clip(hsi[:, :, 2], 0.0, 1.0).astype(np.float32)

	r = np.zeros_like(i)
	g = np.zeros_like(i)
	b = np.zeros_like(i)

	# Sector RG: 0 <= H < 2pi/3
	m1 = (h >= 0) & (h < 2.0 * np.pi / 3.0)
	b[m1] = i[m1] * (1.0 - s[m1])
	r[m1] = i[m1] * (1.0 + (s[m1] * np.cos(h[m1])) / (np.cos(np.pi / 3.0 - h[m1]) + 1e-8))
	g[m1] = 3.0 * i[m1] - (r[m1] + b[m1])

	# Sector GB: 2pi/3 <= H < 4pi/3
	m2 = (h >= 2.0 * np.pi / 3.0) & (h < 4.0 * np.pi / 3.0)
	h2 = h[m2] - 2.0 * np.pi / 3.0
	r[m2] = i[m2] * (1.0 - s[m2])
	g[m2] = i[m2] * (1.0 + (s[m2] * np.cos(h2)) / (np.cos(np.pi / 3.0 - h2) + 1e-8))
	b[m2] = 3.0 * i[m2] - (r[m2] + g[m2])

	# Sector BR: 4pi/3 <= H < 2pi
	m3 = (h >= 4.0 * np.pi / 3.0) & (h <= 2.0 * np.pi)
	h3 = h[m3] - 4.0 * np.pi / 3.0
	g[m3] = i[m3] * (1.0 - s[m3])
	b[m3] = i[m3] * (1.0 + (s[m3] * np.cos(h3)) / (np.cos(np.pi / 3.0 - h3) + 1e-8))
	r[m3] = 3.0 * i[m3] - (g[m3] + b[m3])

	rgb = np.stack([r, g, b], axis=2)
	rgb = np.clip(rgb, 0.0, 1.0)
	return (rgb * 255.0).astype(np.uint8)


def split_planes(image):
	return [image[:, :, 0], image[:, :, 1], image[:, :, 2]]


def smooth_planes_3x3(plane_list):
	"""Apply 3x3 Gaussian mask on each plane."""
	return [cv2.GaussianBlur(p, (3, 3), 0) for p in plane_list]


def combine_rgb_planes(plane_list):
	"""Combine R, G, B planes into one RGB image."""
	return np.stack(plane_list, axis=2).astype(np.uint8)


def combine_hsi_planes(plane_list):
	"""Combine H, S, I planes and convert to RGB for display."""
	hsi = np.stack(plane_list, axis=2)
	return hsi_to_rgb(hsi)


def normalize_plane(plane):
	return cv2.normalize(plane, None, 0, 255, cv2.NORM_MINMAX).astype(np.uint8)


def show_part1_rgb_to_hsi(rgb_img, hsi_img):
	r, g, b = split_planes(rgb_img)
	h = normalize_plane(hsi_img[:, :, 0])
	s = normalize_plane(hsi_img[:, :, 1])
	i = normalize_plane(hsi_img[:, :, 2])
    
	rgb_combined = combine_rgb_planes([r, g, b])

	fig, axes = plt.subplots(2, 4, figsize=(16, 8))
	fig.suptitle("Part 1: RGB Input Planes and HSI Output Planes", fontsize=13, fontweight="bold")

	axes[0, 0].imshow(rgb_img)
	axes[0, 0].set_title("Input RGB Image")
	axes[0, 0].axis("off")

	axes[0, 1].imshow(r, cmap="gray")
	axes[0, 1].set_title("R Plane")
	axes[0, 1].axis("off")
	axes[0, 2].imshow(g, cmap="gray")
	axes[0, 2].set_title("G Plane")
	axes[0, 2].axis("off")
	axes[0, 3].imshow(b, cmap="gray")
	axes[0, 3].set_title("B Plane")
	axes[0, 3].axis("off")

	axes[1, 0].imshow(rgb_combined)
	axes[1, 0].set_title("Combined RGB (from R,G,B)")
	axes[1, 0].axis("off")

	axes[1, 1].imshow(h, cmap="gray")
	axes[1, 1].set_title("H Plane")
	axes[1, 1].axis("off")
	axes[1, 2].imshow(s, cmap="gray")
	axes[1, 2].set_title("S Plane")
	axes[1, 2].axis("off")
	axes[1, 3].imshow(i, cmap="gray")
	axes[1, 3].set_title("I Plane")
	axes[1, 3].axis("off")

	plt.tight_layout()
	plt.show()


def show_part2_model(title, input_planes, output_planes, plane_names, input_combined, output_combined):
	fig, axes = plt.subplots(2, 4, figsize=(16, 8))
	fig.suptitle(title, fontsize=13, fontweight="bold")

	axes[0, 0].imshow(input_combined)
	axes[0, 0].set_title("Input (Combined Planes)")
	axes[0, 0].axis("off")

	for idx in range(3):
		axes[0, idx + 1].imshow(input_planes[idx], cmap="gray")
		axes[0, idx + 1].set_title(f"Input {plane_names[idx]}")
		axes[0, idx + 1].axis("off")

	axes[1, 0].imshow(output_combined)
	axes[1, 0].set_title("Output (Combined Planes)")
	axes[1, 0].axis("off")

	for idx in range(3):
		axes[1, idx + 1].imshow(output_planes[idx], cmap="gray")
		axes[1, idx + 1].set_title(f"Output {plane_names[idx]}")
		axes[1, idx + 1].axis("off")

	plt.tight_layout()
	plt.show()


def print_conclusions():
	print("\nConclusion:")
	print("1) RGB to HSI separates chromatic information (H,S) from brightness (I), making intensity behavior easier to interpret.")
	print("2) 3x3 Gaussian smoothing in RGB blurs all channels directly, so fine details and color edges are reduced together.")
	print("3) 3x3 Gaussian smoothing in HSI smooths H, S, and I separately; this often preserves perceptual color structure better when compared to direct RGB smoothing.")
	print("4) In noisy images, both models reduce noise, but HSI-domain processing provides better control over brightness and color components.")


def main():
	base_path = resolve_image_path([
		"Jupitermoon.jpg",
		"Jupitermoon.jpeg",
		"jupitermoon.jpg",
		"jupitermoon.jpeg",
		"jupiter.jpeg",
	])
	if base_path is None:
		raise FileNotFoundError("No base image found. Place Jupitermoon.jpg (or jupiter.jpeg) in experiment10 folder.")

	noisy_path = resolve_image_path([
		"JupitermoonNoise.jpg",
		"JupitermoonNoise.jpeg",
		"jupitermoonnoise.jpg",
		"jupitermoonnoise.jpeg",
	])

	rgb_img = load_rgb_image(base_path)
	hsi_img = rgb_to_hsi(rgb_img)
	show_part1_rgb_to_hsi(rgb_img, hsi_img)

	noisy_rgb = load_rgb_image(noisy_path) if noisy_path else add_noise_if_needed(rgb_img)

	# RGB model smoothing on each plane
	rgb_in_planes = split_planes(noisy_rgb)
	rgb_out_planes = smooth_planes_3x3(rgb_in_planes)
	rgb_input_combined = combine_rgb_planes(rgb_in_planes)
	rgb_output_combined = combine_rgb_planes(rgb_out_planes)
	show_part2_model(
		"Part 2A: 3x3 Gaussian Smoothing in RGB Model",
		rgb_in_planes,
		rgb_out_planes,
		["R", "G", "B"],
		rgb_input_combined,
		rgb_output_combined,
	)

	# HSI model smoothing on each plane
	noisy_hsi = rgb_to_hsi(noisy_rgb)
	hsi_in_planes_f = split_planes(noisy_hsi)
	hsi_out_planes_f = smooth_planes_3x3(hsi_in_planes_f)

	hsi_in_planes = [normalize_plane(p) for p in hsi_in_planes_f]
	hsi_out_planes = [normalize_plane(p) for p in hsi_out_planes_f]
	hsi_input_combined = combine_hsi_planes(hsi_in_planes_f)
	hsi_output_combined = combine_hsi_planes(hsi_out_planes_f)
	show_part2_model(
		"Part 2B: 3x3 Gaussian Smoothing in HSI Model",
		hsi_in_planes,
		hsi_out_planes,
		["H", "S", "I"],
		hsi_input_combined,
		hsi_output_combined,
	)

	# Reconstructed image from smoothed HSI for visual understanding
	hsi_smoothed_img = np.stack(hsi_out_planes_f, axis=2)
	rgb_from_hsi_smoothed = hsi_to_rgb(hsi_smoothed_img)
	plt.figure(figsize=(10, 4))
	plt.suptitle("Reconstructed Images After Smoothing", fontsize=12, fontweight="bold")
	plt.subplot(1, 2, 1)
	plt.imshow(cv2.merge(rgb_out_planes))
	plt.title("RGB-Plane Smoothed")
	plt.axis("off")
	plt.subplot(1, 2, 2)
	plt.imshow(rgb_from_hsi_smoothed)
	plt.title("HSI-Plane Smoothed (Reconstructed RGB)")
	plt.axis("off")
	plt.tight_layout()
	plt.show()

	print(f"Base image used: {os.path.basename(base_path)}")
	if noisy_path:
		print(f"Noisy image used: {os.path.basename(noisy_path)}")
	else:
		print("Noisy image file not found. Generated noisy image from base image.")

	print_conclusions()


if __name__ == "__main__":
	main()
