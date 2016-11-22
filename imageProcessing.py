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
from skimage.exposure import adjust_gamma

from skimage import data
from skimage.filters import threshold_otsu
from skimage.segmentation import clear_border
from skimage.measure import label
from skimage.morphology import closing, opening, square, disk
from skimage.measure import regionprops
from skimage.color import label2rgb, rgb2gray

def star():
	image = misc.imread('images/images/easy01.png', True)
	checkerboard = [[{} for x in range(image.shape[1]/100)] for y in range(image.shape[0]/100)]
	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig, ac = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i:i+99, j:j+99]
			edges = canny(square, sigma=1.0, low_threshold=10, high_threshold=50)
			#thresh = threshold_otsu(square)
			#edges = square > thresh
			
			ax[i/100,j/100].imshow(edges, cmap = plt.cm.Greys_r)
			ax[i/100,j/100].set_axis_off()
			
			ac[i/100,j/100].set_axis_off()
			ac[i/100,j/100].imshow(edges, cmap=plt.cm.gray)
			no_lines = 0
			h_w, angles_w, d_w = hough_line(edges)
			for _, angle, dist in zip(*hough_line_peaks(h_w, angles_w, d_w,
														threshold=0.5*np.max(h_w),
														min_distance=35)):
								
				if(angle < 1.57) and (angle != 0.0):
					no_lines += 1
					y0 = (dist - 0 * np.cos(angle)) / np.sin(angle)
					y1 = (dist - image.shape[1] * np.cos(angle)) / np.sin(angle)

					ac[i/100,j/100].plot((0, image.shape[1]), (y0, y1), '-r')

				ac[i/100,j/100].set_xlim((0, edges.shape[1]))
				ac[i/100,j/100].set_ylim((edges.shape[0], 0))

			if(no_lines == 9) or (no_lines == 10):
				print("Rectangle at ",i/100, j/100)
			
			#label_image = label(edges)
			#image_label_overlay = label2rgb(label_image, image=edges)
			#
			#ac[i/100,j/100].imshow(image_label_overlay)
			#ac[i/100,j/100].set_axis_off()
			#
			#is_rectangle = False
			#
			#for region in regionprops(label_image):
			#	if region.area < 1000 or region.area > 6000:
			#		continue
			#
			#	minr, minc, maxr, maxc = region.bbox
			#	rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
			#				              fill=False, edgecolor='red', linewidth=2)
			#	ac[i/100,j/100].add_patch(rect)
			#	is_rectangle = True
	plt.show()

def v():
	image = misc.imread('images/images/difficult02.png', True)
	checkerboard = [[{} for x in range(image.shape[1]/100)] for y in range(image.shape[0]/100)]
	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig, ac = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))

	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i:i+99, j:j+99]
			edges = canny(square, sigma=1.0, low_threshold=10, high_threshold=50)
			thresh = threshold_otsu(square)
			edges = square > thresh
			
			ax[i/100,j/100].imshow(edges, cmap = plt.cm.Greys_r)
			ax[i/100,j/100].set_axis_off()
			
			ac[i/100,j/100].set_axis_off()
			ac[i/100,j/100].imshow(edges, cmap=plt.cm.gray)

			label_image = label(edges)
			image_label_overlay = label2rgb(label_image, image=edges)

			ac[i/100,j/100].imshow(image_label_overlay)
			ac[i/100,j/100].set_axis_off()
			
			is_rectangle = False
			
			for region in regionprops(label_image):
				if region.area < 1500 or region.area > 2000:
					continue
			
				minr, minc, maxr, maxc = region.bbox
				rect = mpatches.Rectangle((minc, minr), maxc - minc, maxr - minr,
							              fill=False, edgecolor='red', linewidth=2)
				ac[i/100,j/100].add_patch(rect)
				is_rectangle = True
	plt.show()

def rectangle():
	image = misc.imread('images/images/difficult02.png', True)

	checkerboard = [[{} for x in range(image.shape[1]/100)] for y in range(image.shape[0]/100)]

	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig, a = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))	
	ig, ab = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))	

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

			a[i/100,j/100].imshow(edges, cmap = plt.cm.Greys_r)
			a[i/100,j/100].set_axis_off()

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
				print("Rectangle at ",i/100, j/100)
	plt.show()

def pacman():
	image = misc.imread('images/easy02.png', True)

	checkerboard = [[{} for x in range(image.shape[1]/100)] for y in range(image.shape[0]/100)]

	ig, ax = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))
	ig, a = plt.subplots(ncols=8, nrows=5, figsize=(6, 6))	


	for i in range(0, image.shape[0], 100):
		for j in range(0, image.shape[1], 100):
			square = image.copy()[i+2:i+98, j+2:j+98]

			edges = canny(square, sigma=1.0, low_threshold=10, high_threshold=50)
			closed = skimage.morphology.closing(edges, skimage.morphology.square(2))

			a[i/100,j/100].imshow(closed, cmap = plt.cm.Greys_r)
			a[i/100,j/100].set_axis_off()

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
	plt.show()


if __name__ == "__main__":
	#pacman()
	#rectangle()
	#v()
	star()