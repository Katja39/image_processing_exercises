#include <iostream>
#include "CImage.h"
#include "CColor.h"

using namespace bvme;

void exercise() {
	CImage imageRose("Images/rose.bmp");
	CImage imageGrau("Images/rose.bmp");
	CImage imageBinaer("Images/rose.bmp");
	CImage imagePixel("Images/rose.bmp");

	imageRose.showImage();

	int red;
	int green;
	int blue;

	CColor tmpPoint = imageRose.getPointValue(1, 1);
	int imageHeight = imageRose.getHeight();
	int imageWidth = imageRose.getWidth();

	//Grauwertbild

	int greyvalue=0;

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red=imageRose.getPointValue(i, n).getRed();
			green=imageRose.getPointValue(i, n).getGreen();
			blue= imageRose.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;

			tmpPoint.setRed(greyvalue);
			tmpPoint.setGreen(greyvalue);
			tmpPoint.setBlue(greyvalue);

			imageGrau.setPointValue(i,n,tmpPoint);
		}
	}

	imageGrau.showImage();

	//Binaerbild
	int t = 150;

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageRose.getPointValue(i, n).getRed();
			green = imageRose.getPointValue(i, n).getGreen();
			blue = imageRose.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			
			if (greyvalue < t) {
				tmpPoint.setRed(0);
				tmpPoint.setGreen(0);
				tmpPoint.setBlue(0);
			}
			else {
				tmpPoint.setRed(255);
				tmpPoint.setGreen(255);
				tmpPoint.setBlue(255);
			}
			imageBinaer.setPointValue(i, n, tmpPoint);
		}
	}
	imageBinaer.showImage();

	//Maximal und Minimal Grauwert Pixel

	int max=0;
	int maxX = 0;
	int maxY = 0;
	int min=255;
	int minX = 0;
	int minY = 0;

	tmpPoint.setBlue(0);
	tmpPoint.setGreen(0);
	tmpPoint.setRed(200);

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageRose.getPointValue(i, n).getRed();
			green = imageRose.getPointValue(i, n).getGreen();
			blue = imageRose.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;

			if (greyvalue > max) {
				max = greyvalue;
				maxX = i;
				maxY = n;
			}
			if (greyvalue < min) {
				min = greyvalue;
				minX = i;
				minY = n;
			}
			
		}
	}

	for (int i = 0; i < 5; i++)
	{
		imagePixel.setPointValue(maxX, maxY + i, tmpPoint);
		imagePixel.setPointValue(minX, minY + i, tmpPoint);

		imagePixel.setPointValue(maxX, maxY, tmpPoint);
		imagePixel.setPointValue(minX, minY, tmpPoint);

		imagePixel.setPointValue(maxX+i, maxY, tmpPoint);
		imagePixel.setPointValue(minX+i, minY, tmpPoint);

		imagePixel.setPointValue(maxX+i, maxY + i, tmpPoint);
		imagePixel.setPointValue(minX+i, minY + i, tmpPoint);
	}
	imagePixel.showImage();
}