#include "CImage.h"
#include "CColor.h"
#include <iostream>
#include <cmath>

using namespace bvme;
void exercise3() {
	CImage imageMoonBlur("Images/mond.bmp");
	CImage imageCopy("Images/mond.bmp");
	imageMoonBlur = imageMoonBlur.getGreyscaleImage();
	imageCopy = imageMoonBlur.getGreyscaleImage();

	int imageHeight = imageMoonBlur.getHeight();
	int imageWidth = imageMoonBlur.getWidth();

	float greyvalue=0.0;
	float sum= 0.0;
	float maskSize = 49;
	float element = sqrt(maskSize);
	int positionWidth=0;
	int positionHeight=0;
	CColor tmpPoint(0);
	imageMoonBlur.showImage();
	int verschiebenN=0;
	int verschiebenI=0;

	//Blur

	for (size_t x = 0; x < imageHeight-element; x++)//height
	{
		for (size_t y = 0; y < imageWidth-element; y++)//width
		{
			for (size_t i = 0; i < element; i++)
			{
				for (size_t n = 0; n < element; n++)
				{
					greyvalue = imageCopy.getPointValue(i+x,n+y).getGrey();
					sum += 1.0/maskSize * greyvalue;
					if (i == 1 && n == 1) {
						positionHeight = i+x;
						positionWidth = n+y;
					}
				}
			}
			tmpPoint.setGrey(sum);
			imageMoonBlur.setPointValue(positionHeight, positionWidth, tmpPoint);
			sum = 0;
		}
	}
	imageMoonBlur.showImage();

	
	//sharpness filter
	
	CImage imageMoon("Images/mond.bmp");
	imageMoon = imageMoon.getGreyscaleImage();
	CImage imageMoonSharp(imageMoon.getHeight(), imageMoon.getWidth(), true);
	element = 3;

	int mask[3][3] = { {1,1,1},{1,-8,1},{1,1,1} };
	int tmp = 0;
	CColor tmpPoint2(0);
	int tmpImagePoint = 0;

	int offsetX = sizeof(mask) / sizeof(mask[0]) / 2;
	int offsetY = sizeof(mask[0]) / sizeof(int) / 2;


	for (int x = offsetX; x < imageMoon.getHeight() - offsetX; x++)
	{
		for (int y = offsetY; y < imageMoon.getWidth() - offsetY; y++)
		{
			for (int i = 0; i < sizeof(mask) / sizeof(mask[0]); i++)
			{
				for (int j = 0; j < sizeof(mask[0]) / sizeof(int); j++)
				{
					tmp += mask[i][j] * imageMoon.getPointValue(x - offsetX + i, y - offsetY + j).getGrey();
				}
			}
			tmpImagePoint = imageMoon.getPointValue(x, y).getGrey();
			tmpPoint2.setGrey((tmpImagePoint - tmp));

			imageMoonSharp.setPointValue(x, y, tmpPoint2);
			tmp = 0;
		}
	}
	imageMoonSharp.showImage();
}