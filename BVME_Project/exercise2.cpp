#include "CImage.h"
#include "CColor.h"
#include <iostream>

using namespace bvme;

void exercise2() {
	CImage imageText("Images/text1.bmp");


	CColor tmpPoint = imageText.getPointValue(1, 1);
	int imageHeight = imageText.getHeight();
	int imageWidth = imageText.getWidth();

	int greyvalue = 0;
	int red;
	int blue;
	int green;
	int sum=0;
	double mean = 0;

	int mSmallCounter = 0;//number of mSmall
	int mSmallGesamt = 0;
	double mSmallMean = 0;

	int mBigCounter = 0;
	int mBigGesamt = 0;
	double mBigMean = 0;

	//1.
	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageText.getPointValue(i, n).getRed();
			green = imageText.getPointValue(i, n).getGreen();
			blue = imageText.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			sum += greyvalue;
		}
	}
	mean = sum / (imageHeight * imageWidth); //mean value of all gray values

	//2. set mSmall and mBig

	double mNew = 0;
	double mOld = 255;
	int x = 0;
	int loopCounter=0;

	do{
		mSmallCounter = 0;
		mSmallGesamt = 0;
		mBigCounter = 0;
		mBigGesamt = 0;
		mSmallMean = 0;
		mBigMean = 0;

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageText.getPointValue(i, n).getRed();
			green = imageText.getPointValue(i, n).getGreen();
			blue = imageText.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			
			if (greyvalue < mean) {
				mSmallCounter++;
				mSmallGesamt += greyvalue;
			}
			else {
				mBigCounter++;
				mBigGesamt += greyvalue;
			}

		}
	}
	//3.mean value of mSmall and mBig
	mSmallMean = mSmallGesamt / mSmallCounter;
	mBigMean = mBigGesamt / mBigCounter;
	//4.
	mNew = (mSmallMean + mBigMean) / 2;
	loopCounter++;
	std::cout << "round "<<loopCounter<<": m="<<mNew<<"\n";
	if (mOld - mNew < 1) {
		x = 1;
	}
	mean = mNew;
	mOld = mNew;
	} while (x ==0);

	std::cout << "\n";

	//5.
	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageText.getPointValue(i, n).getRed();
			green = imageText.getPointValue(i, n).getGreen();
			blue = imageText.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			sum += greyvalue;
			if (greyvalue >= mNew) {
				tmpPoint.setRed(255);
				tmpPoint.setGreen(255);
				tmpPoint.setBlue(255);

				imageText.setPointValue(i, n, tmpPoint);
			}
			else {
				tmpPoint.setRed(0);
				tmpPoint.setGreen(0);
				tmpPoint.setBlue(0);

				imageText.setPointValue(i, n, tmpPoint);
			}
		}
	}
	//imageText.showImage();

	//Task 2
	//Histogram
	CImage imageHistogram("Images/rose_flau.bmp");
	imageHeight = imageHistogram.getHeight();
	imageWidth = imageHistogram.getWidth();
	int histogramm[255];//Position,Number
	float cumulativeHistogram[255];
	int wertegesamt = 0;;
	x = 0;

	for (int i = 0; i < 255; i++)
	{
		histogramm[i] = 0;
		cumulativeHistogram[i] = 0;
	}

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			x = 0;
			red = imageHistogram.getPointValue(i, n).getRed();
			green = imageHistogram.getPointValue(i, n).getGreen();
			blue = imageHistogram.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			do {
				if (x == greyvalue) {
					histogramm[x]=histogramm[x]+1;
					x = 255;
					wertegesamt++;
				}
					x++;
			} while (x<=255);
		}
	}
	x = 0;
	do {
		std::cout <<"Histogram: \n" << x << " -> " << histogramm[x] << "\n";//Histogram normal
		x++;
	} while (x < 255);

	//cumulative Histogram 
	std::cout << "cumulative Histogram\n";
	for (int i = 0; i < 255; i++)
	{

		if (i > 0) {
			cumulativeHistogram[i] =cumulativeHistogram[i-1]+ histogramm[i];
		}
		else {
			cumulativeHistogram[i] += histogramm[i];
		}
		//std::cout <<"Position: "<<i <<" "<< cumulativeHistogram[i] << "\n";
	}
	
	float newGreyValue=0;

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageHistogram.getPointValue(i, n).getRed();
			green = imageHistogram.getPointValue(i, n).getGreen();
			blue = imageHistogram.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			newGreyValue = (cumulativeHistogram[greyvalue] / wertegesamt) * 255;

			//std::cout << "New grey value at position: "<<greyvalue <<" = "<<newGreyValue<< "\n";

			tmpPoint.setRed(newGreyValue);
			tmpPoint.setGreen(newGreyValue);
			tmpPoint.setBlue(newGreyValue);

			imageHistogram.setPointValue(i, n, tmpPoint);
		}
	}
	imageHistogram.showImage();

}