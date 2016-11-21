import numpy as np
from scipy import misc
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
from scipy import signal
import scipy
import skimage.morphology
from skimage.transform import (hough_line, hough_line_peaks,
                               probabilistic_hough_line)
from skimage.feature import peak_local_max, canny
from scipy import ndimage as ndi
from skimage.filters import threshold_otsu
from skimage.transform import hough_circle
from skimage.draw import circle_perimeter


def test(image):
	image = misc.imread('./easy01.png', True)

	checkerboard = [[{} for x in range(image.shape[1]/100)] for y in range(image.shape[0]/100)] #np.zeros((image.shape[0]/100, image.shape[1]/100))

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i+2:i+98, j+2:j+98]
			edges = canny(square, sigma=1.0, low_threshold=10, high_threshold=50)
