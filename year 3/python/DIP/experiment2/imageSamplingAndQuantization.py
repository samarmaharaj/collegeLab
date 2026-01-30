import numpy as np
import matplotlib.pyplot as plt
from skimage.io import imshow, imread

def circle_image(x, y):
    X, Y = np.meshgrid(x, y)
    return X**2 + Y**2
factors = 2**np.arange(1, 5)
fig, ax = plt.subplots(1, len(factors), figsize=(15, 4))
for i, N in enumerate(factors):
    image = circle_image(np.linspace(-1, 1, num=N), np.linspace(-1, 1, num=N))
    ax[i].imshow(image, cmap='gray')
    ax[i].set_title('$N = {}$'.format(N))