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

	//Fouriertransformation
	imageRoseLowPassFilter = image_grey.FourierTransformation(false);
	
	//Idealer Tiefpassfilter
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
	imageRoseLowPassFilter.showImage();
	//inverse Fouriertransformation
	imageRoseLowPassFilter = imageRoseLowPassFilter.FourierTransformation(true);
	imageRoseLowPassFilter.showImage("Idealer Tiefpassfilter");
	
	//Idealer Hochpassfilter
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
	imageRoseLowPassFilter.showImage();
	//inverse Fouriertransformation
	imageRoseLowPassFilter = imageRoseLowPassFilter.FourierTransformation(true);
	imageRoseLowPassFilter.showImage("Idealer Hochpassfilter");


	//Gauß Tiefpassfilter
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
	imageRoseLowPassFilterGauss.showImage();
	imageRoseLowPassFilterGauss = imageRoseLowPassFilterGauss.FourierTransformation(true);
	imageRoseLowPassFilterGauss.showImage("Gaußscher Tiefpassfilter");


	//Gauß Hochpassfilter
	CImage imageRoseHighPassFilterGauss = image_grey;
	imageRoseHighPassFilterGauss = image_grey.FourierTransformation(false);
	d = 0.0;
	h = 0.0;

	for (int x = 0; x < m; x++)
	{
		for (int y = 0; y < n; y++)
		{
			d = pow(x - m / 2, 2) + pow(y - n / 2, 2);
			h = 2 - exp(-d / (2 * pow(radius, 2))); //1- = Kantenbild, 2- = geschärftes Bild
			value = imageRoseHighPassFilterGauss.getComplexPointValue(x, y);
			real = value.real();
			imag = value.imag();
			value.real(real * h);
			value.imag(imag * h);
			imageRoseHighPassFilterGauss.setComplexPointValue(x, y, value);
		}
	}
	imageRoseHighPassFilterGauss.showImage();
	imageRoseHighPassFilterGauss = imageRoseHighPassFilterGauss.FourierTransformation(true);
	imageRoseHighPassFilterGauss.showImage("Gaußscher Hochpassfilter");
}