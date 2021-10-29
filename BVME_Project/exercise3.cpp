#include "CImage.h"
#include "CColor.h"
#include <iostream>
#include <cmath>

using namespace bvme;
void exercise3() {
	CImage imageMoonSoft("Images/mond.bmp");
	CImage imageCopy("Images/mond.bmp");
	imageMoonSoft = imageMoonSoft.getGreyscaleImage();
	imageCopy = imageMoonSoft.getGreyscaleImage();

	int imageHeight = imageMoonSoft.getHeight();
	int imageWidth = imageMoonSoft.getWidth();

	float greyvalue=0.0;
	float gesamt= 0.0;
	float maskengroesse = 49;
	float element = sqrt(maskengroesse);
	int positionWidth=0;
	int positionHeight=0;
	CColor tmpPoint(0);
	imageMoonSoft.showImage();
	int verschiebenN=0;
	int verschiebenI=0;

	//Weichzeichner

	for (size_t x = 0; x < imageHeight-element; x++)//Hoehe
	{
		for (size_t y = 0; y < imageWidth-element; y++)//Breite
		{
			for (size_t i = 0; i < element; i++)
			{
				for (size_t n = 0; n < element; n++)
				{
					greyvalue = imageCopy.getPointValue(i+x,n+y).getGrey();
					gesamt += 1.0/maskengroesse * greyvalue;
					if (i == 1 && n == 1) {
						positionHeight = i+x;
						positionWidth = n+y;
					}
				}
			}
			tmpPoint.setGrey(gesamt);
			imageMoonSoft.setPointValue(positionHeight, positionWidth, tmpPoint);
			gesamt = 0;
		}
	}
	imageMoonSoft.showImage();


	
	//Schärfefilter
	/*
	CImage imageMoon("Images/mond.bmp");
	CImage imageMoonSharp("Images/mond.bmp");
	imageMoonSharp = imageMoonSharp.getGreyscaleImage();
	imageMoon = imageMoonSharp.getGreyscaleImage();
	element = 3;

	int mask[2][2];

	for (int i = 0; i < 2; i++)
	{
		for (int n = 0; n < 2; n++)
		{
			if(i==1&&n==1){
			mask[i][n] = 8;
			}else{
			mask[i][n] = -1;
			}
		}
	}

	for (size_t x = 0; x < imageHeight - element; x++)//Hoehe
	{
		for (size_t y = 0; y < imageWidth - element; y++)//Breite
		{
			for (size_t i = 0; i < element; i++)
			{
				for (size_t n = 0; n < element; n++)
				{
					greyvalue = imageCopy.getPointValue(i + x, n + y).getGrey();
					gesamt=greyvalue*mask[i][n];
				}
			}
		}
			
	}
	*/
}