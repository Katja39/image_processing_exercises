#include <iostream>
#include "CImage.h"
#include "CColor.h"

using namespace bvme;

void exercise() {
	CImage imageRose("Images/rose.bmp");   //original image
	CImage imageGrau("Images/rose.bmp");   //gray value image
	CImage imageBinaer("Images/rose.bmp"); //binary image
	CImage imagePixel("Images/rose.bmp");  //max and min gray value marked

	imageRose.showImage(); 

	int red;
	int green;
	int blue;

	CColor tmpPoint = imageRose.getPointValue(1, 1);
	int imageHeight = imageRose.getHeight();
	int imageWidth = imageRose.getWidth();

	//gray value image

	int greyvalue=0;

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red=imageRose.getPointValue(i, n).getRed();
			green=imageRose.getPointValue(i, n).getGreen();
			blue= imageRose.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3; //Calculate average value to determine gray value

			tmpPoint.setRed(greyvalue);
			tmpPoint.setGreen(greyvalue);
			tmpPoint.setBlue(greyvalue);

			imageGrau.setPointValue(i,n,tmpPoint);
		}
	}

	imageGrau.showImage();

	//binary image
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

	//Maximum and minimum gray value pixel

	int max  = 0;
	int maxX = 0;//x,y values of the max gray value
	int maxY = 0;

	int min	 = 255;
	int minX = 0;//x,y values of the min gray value
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

		imagePixel.setPointValue(maxX, maxY, tmpPoint);
		imagePixel.setPointValue(maxX + 1, maxY, tmpPoint);
		imagePixel.setPointValue(maxX + 1, maxY + 1, tmpPoint);
		imagePixel.setPointValue(maxX, maxY + 1, tmpPoint);

		imagePixel.setPointValue(minX, minY, tmpPoint);
		imagePixel.setPointValue(minX + 1, minY, tmpPoint);
		imagePixel.setPointValue(minX + 1, minY + 1, tmpPoint);
		imagePixel.setPointValue(minX, minY + 1, tmpPoint);
	
	imagePixel.showImage();
}