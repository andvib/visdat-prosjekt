import numpy as np
from scipy import misc
import matplotlib.pyplot as plt
import matplotlib.patches as mpatches
import matplotlib
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
from skimage.exposure import adjust_gamma

from skimage import data
from skimage.filters import threshold_otsu
from skimage.segmentation import clear_border
from skimage.measure import label
from skimage.morphology import closing, opening, square, disk
from skimage.measure import regionprops
from skimage.color import label2rgb, rgb2gray

import math

image = misc.imread('image_processing/images/easy01.png', True)
image_rgb = misc.imread('image_processing/images/easy01.png')
checkerboard = [[{} for x in range(image.shape[1]/100)] for y in range(image.shape[0]/100)]
debug = 1
pos = 0

def main():
	star()
	v()
	rectangle()
	pacman()
	triangle()
	hexagon()

	for i in range(len(checkerboard)):	
		print checkerboard[i]

	if debug:
		plt.show()


def triangle():
	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig.suptitle('Triangle')
	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i:i + 99, j:j + 99]

			edges = canny(square, sigma=1.0, low_threshold=15, high_threshold=50)
			edges = skimage.morphology.closing(edges, skimage.morphology.square(1))
			h, angles, d = hough_line(edges)

			dilated = ndi.binary_dilation(edges, skimage.morphology.square(3))
			edges = dilated

			no_lines = 0

			ax[i / 100, j / 100].set_axis_off()
			ax[i / 100, j / 100].imshow(edges, cmap=plt.cm.gray)


			label_image = label(edges)
			image_label_overlay = label2rgb(label_image, image=edges)

			ax[i / 100, j / 100].imshow(image_label_overlay)
			ax[i / 100, j / 100].set_axis_off()

			var = False

			for region in regionprops(label_image):

				if region.area < 450: #or region.area > 270:
					continue
				min_row = region.bbox[0]
				min_col = region.bbox[1]
				max_row = region.bbox[2]
				max_col = region.bbox[3]

				size = (max_row-min_row)*(max_col-min_col)
				if size > 8000:
					continue

				if (region.eccentricity < 0.54) or (region.eccentricity > 0.64):
					continue
				var = True

			for _, angle, dist in zip(*hough_line_peaks(h, angles, d,
		                            threshold=0.55*np.max(h), num_peaks=10)):
				no_lines += 1
				y0 = (dist - 0 * np.cos(angle)) / np.sin(angle)
				y1 = (dist - image.shape[1] * np.cos(angle)) / np.sin(angle)

				ax[i/100,j/100].plot((0, image.shape[1]), (y0, y1), '-r')

				ax[i/100,j/100].set_xlim((0, edges.shape[1]))
				ax[i/100,j/100].set_ylim((edges.shape[0], 0))

				if(no_lines == 3 and var == True):
					# TRIANGLE FOUND
					checkerboard[i/100][j/100] = "T"

def hexagon():
	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig.suptitle('Hexagon')

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i:i + 99, j:j + 99]

			edges = canny(square, sigma=1.0, low_threshold=15, high_threshold=50)
			edges = skimage.morphology.closing(edges, skimage.morphology.square(1))

			dilated = ndi.binary_dilation(edges, skimage.morphology.square(3))
			edges = dilated
			filled = ndi.binary_fill_holes(edges)
			edges = filled

			label_image = label(edges)
			image_label_overlay = label2rgb(label_image, image=edges)

			ax[i / 100, j / 100].imshow(image_label_overlay)
			ax[i / 100, j / 100].set_axis_off()

			for region in regionprops(label_image):

				if region.area < 3900: 
					continue
				min_row = region.bbox[0]
				min_col = region.bbox[1]
				max_row = region.bbox[2]
				max_col = region.bbox[3]

				size = (max_row-min_row)*(max_col-min_col)
				if size > 8000:
					continue

				if (region.eccentricity > 0.40):
					continue
		
				# draw rectangle around segmented objects
				minr, minc, maxr, maxc = region.bbox
				hex = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
								          fill=False, edgecolor='red', linewidth=2)
				ax[i / 100, j / 100].add_patch(hex)

				current_square = image_rgb.copy()[i:i + 99, j:j + 99]
				r, g, b = 0, 0, 0
				for x in range(current_square.shape[0]):
					for y in range(current_square.shape[1]):
						r += current_square[x, y, 0]
						g += current_square[x, y, 1]
						b += current_square[x, y, 2]
				r, g, b = r / (current_square.shape[0] * current_square.shape[1]), g / (current_square.shape[0] * current_square.shape[1]), b / (
				current_square.shape[0] * current_square.shape[1])
				color_threshold = 90
				mean_color = (r + g + b) / 3

				if mean_color > color_threshold:
					fig = "W"
				else:
					fig = "B"
				if pos:
					x, y = region.centroid
					checkerboard[i/100][j/100] = (fig,x,y)
				else:
					checkerboard[i/100][j/100] = fig

def star():
	ig, ac = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig.suptitle('Star')

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i:i+99, j:j+99]
			
			edges = canny(square, sigma=1.0, low_threshold=20, high_threshold=50)

			closed = skimage.morphology.closing(edges, skimage.morphology.square(2))

			thresh = threshold_otsu(square)
			edges = square > thresh
			edges = np.invert(edges)

			ac[i/100,j/100].set_axis_off()
			ac[i/100,j/100].imshow(edges, cmap=plt.cm.gray)
			
			label_image = label(edges)
			image_label_overlay = label2rgb(label_image, image=edges)
			
			ac[i/100,j/100].imshow(image_label_overlay)
			ac[i/100,j/100].set_axis_off()
			
			for region in regionprops(label_image):
				if region.area < 2650 or region.area > 3000:
					continue
			
				minr, minc, maxr, maxc = region.bbox
				rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
							              fill=False, edgecolor='red', linewidth=2)
				ac[i/100,j/100].add_patch(rect)

				# STAR FOUND
				if pos:
					x, y = region.centroid
					checkerboard[i/100][j/100] = ("S",x,y)
				else:
					checkerboard[i/100][j/100] = "S"

def v():
	ig, ac = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig.suptitle('V')

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i:i+99, j:j+99]
			edges = canny(square, sigma=1.0, low_threshold=10, high_threshold=50)
			thresh = threshold_otsu(square)
			edges = square > thresh
			
			ac[i/100,j/100].set_axis_off()
			ac[i/100,j/100].imshow(edges, cmap=plt.cm.gray)

			label_image = label(edges)
			image_label_overlay = label2rgb(label_image, image=edges)

			ac[i/100,j/100].imshow(image_label_overlay)
			ac[i/100,j/100].set_axis_off()
			
			for region in regionprops(label_image):
				if region.area < 1500 or region.area > 2000:
					continue
			
				minr, minc, maxr, maxc = region.bbox
				rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
							              fill=False, edgecolor='red', linewidth=2)
				ac[i/100,j/100].add_patch(rect)

				# PACMAN FOUND
				if pos:
					x, y = region.centroid
					checkerboard[i/100][j/100] = ("V",x,y)
				else:
					checkerboard[i/100][j/100] = "V"

def rectangle():
	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig.suptitle('Rectangle')
	ig, ab = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))	
	ig.suptitle('Rectangle')

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i:i+99, j:j+99]

			thresh = threshold_otsu(square)
			edges = square > thresh

			edges = skimage.morphology.opening(edges, skimage.morphology.square(3))
			edges = skimage.morphology.closing(edges, skimage.morphology.square(1))
			
			eroded = ndi.binary_erosion(edges)
			edges = edges - eroded

			h_w, angles_w, d_w = hough_line(edges)

			ab[i/100,j/100].imshow(edges, cmap = plt.cm.Greys_r)
			ab[i/100,j/100].set_axis_off()
			
			no_lines = 0

			ax[i/100,j/100].set_axis_off()
			ax[i/100,j/100].imshow(edges, cmap=plt.cm.gray)

			label_image = label(edges)
			image_label_overlay = label2rgb(label_image, image=edges)

			ax[i/100,j/100].imshow(image_label_overlay)
			ax[i/100,j/100].set_axis_off()
			
			is_rectangle = False
			
			for region in regionprops(label_image):
				if region.area < 230 or region.area > 270:
					continue
			
				minr, minc, maxr, maxc = region.bbox
				rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
							              fill=False, edgecolor='red', linewidth=2)
				ax[i/100,j/100].add_patch(rect)
				is_rectangle = True

			for _, angle, dist in zip(*hough_line_peaks(h_w, angles_w, d_w,
														threshold=0.5*np.max(h_w),
														min_distance=35)):
								
				if(angle < 1.57) and (angle != 0.0):
					no_lines += 1
					y0 = (dist - 0 * np.cos(angle)) / np.sin(angle)
					y1 = (dist - image.shape[1] * np.cos(angle)) / np.sin(angle)

					ab[i/100,j/100].plot((0, image.shape[1]), (y0, y1), '-r')

				ab[i/100,j/100].set_xlim((0, edges.shape[1]))
				ab[i/100,j/100].set_ylim((edges.shape[0], 0))

			if(no_lines == 4) and is_rectangle:
				# RECTANGLE FOUND
				checkerboard[i/100][j/100] = "R"

def pacman():
	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))	
	ig.suptitle('Pacman')

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i+2:i+98, j+2:j+98]

			edges = canny(square, sigma=1.0, low_threshold=10, high_threshold=50)
			closed = skimage.morphology.closing(edges, skimage.morphology.square(2))

			label_image = label(closed)
			image_label_overlay = label2rgb(label_image, image=closed)

			ax[i/100,j/100].imshow(image_label_overlay)
			ax[i/100,j/100].set_axis_off()

			for region in regionprops(label_image):
				if region.area < 320 or region.area > 440:
					continue

				if (region.eccentricity > 0.70) or (region.eccentricity < 0.58):
					continue

				minr, minc, maxr, maxc = region.bbox
				rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
							              fill=False, edgecolor='red', linewidth=2)
				ax[i/100,j/100].add_patch(rect)

				# PACMAN FOUND
				if pos:
					x, y = region.centroid
					checkerboard[i/100][j/100] = ("P",x,y)
				else:
					checkerboard[i/100][j/100] = "P"
				


if __name__ == "__main__":
	main()
