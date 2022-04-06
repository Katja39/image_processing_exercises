#include "CImage.h"
#include "CColor.h"
#include <iostream>
#include <cmath>

using namespace bvme;
void exercise4() {
	CImage imageRose("Images/rose_fourier.bmp");
	CImage image_grey = imageRose.getGreyscaleImage();
	CImage imageRoseLowPassFilter(image_grey.getHeight(), image_grey.getWidth(), true);
	Complex value;
	int m = image_grey.getHeight();
	int n = image_grey.getWidth();
	int radius = 50;

	//fourier transform
	imageRoseLowPassFilter = image_grey.FourierTransformation(false);
	
	//ideal low-pass filter
	for (int x = 0; x < m; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (pow(x - m / 2, 2) + pow(y - n / 2, 2) > pow(radius, 2)) {
				value.real(0);
				value.imag(0);
				imageRoseLowPassFilter.setComplexPointValue(x, y, value);
			}
			
		}
	}
	imageRoseLowPassFilter.showImage("fourier transform, ideal low-pass filter");
	//inverse Fourier transform
	imageRoseLowPassFilter = imageRoseLowPassFilter.FourierTransformation(true);
	imageRoseLowPassFilter.showImage("Ideal low-pass filter");
	
	//ideal high-pass filter
	imageRoseLowPassFilter = image_grey;
	imageRoseLowPassFilter = image_grey.FourierTransformation(false);

	for (int x = 0; x < m; x++)
	{
		for (int y = 0; y < n; y++)
		{
			if (pow(x - m / 2, 2) + pow(y - n / 2, 2) < pow(radius, 2)) {
				value.real(0);
				value.imag(0);
				imageRoseLowPassFilter.setComplexPointValue(x, y, value);
			}

		}
	}
	imageRoseLowPassFilter.showImage("fourier transform, ideal high-pass filter");

	//inverse Fourier transform
	imageRoseLowPassFilter = imageRoseLowPassFilter.FourierTransformation(true);
	imageRoseLowPassFilter.showImage("Ideal high-pass filter");

	//low-pass gaussian filter
	CImage imageRoseLowPassFilterGauss = image_grey;
	imageRoseLowPassFilterGauss = image_grey.FourierTransformation(false);
	float d= 0.0;
	float h = 0.0;
	float real;
	float imag;

	for (int x = 0; x < m; x++)
	{
		for (int y = 0; y < n; y++)
		{
			d = pow(x - m / 2, 2) + pow(y - n / 2, 2);
			h = exp(-d / (2 * pow(radius, 2)));
			value = imageRoseLowPassFilterGauss.getComplexPointValue(x, y);
			real = value.real();
			imag = value.imag();
			value.real(real * h);
			value.imag(imag * h);
			imageRoseLowPassFilterGauss.setComplexPointValue(x, y, value);
		}
	}
	imageRoseLowPassFilterGauss.showImage("fourier transform, low-pass gaussian filter");
	imageRoseLowPassFilterGauss = imageRoseLowPassFilterGauss.FourierTransformation(true);
	imageRoseLowPassFilterGauss.showImage("low-pass gaussian filter");


	//low-pass gaussian filter
	CImage imageRoseHighPassFilterGauss = image_grey;
	imageRoseHighPassFilterGauss = image_grey.FourierTransformation(false);
	d = 0.0;
	h = 0.0;

	for (int x = 0; x < m; x++)
	{
		for (int y = 0; y < n; y++)
		{
			d = pow(x - m / 2, 2) + pow(y - n / 2, 2);
			h = 2 - exp(-d / (2 * pow(radius, 2))); //1- = image of the edges, 2- = sharpened image
			value = imageRoseHighPassFilterGauss.getComplexPointValue(x, y);
			real = value.real();
			imag = value.imag();
			value.real(real * h);
			value.imag(imag * h);
			imageRoseHighPassFilterGauss.setComplexPointValue(x, y, value);
		}
	}
	imageRoseHighPassFilterGauss.showImage("fourier transform, high-pass gaussian filter");
	imageRoseHighPassFilterGauss = imageRoseHighPassFilterGauss.FourierTransformation(true);
	imageRoseHighPassFilterGauss.showImage("high-pass gaussian filter");
}