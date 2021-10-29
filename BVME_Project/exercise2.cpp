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
	int gesamt=0;
	double mean = 0;

	int mSmallCounter = 0;//Anzahl mSmall
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
			gesamt += greyvalue;
		}
	}
	mean = gesamt / (imageHeight * imageWidth); //Mittelwert aller Grauwerte

	//2. Mengen mSmall und mBig

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
	//3.
	mSmallMean = mSmallGesamt / mSmallCounter;
	mBigMean = mBigGesamt / mBigCounter;
	//4.
	mNew = (mSmallMean + mBigMean) / 2;
	loopCounter++;
	std::cout << "Durchgang "<<loopCounter<<": m="<<mNew<<"\n";
	if (mOld - mNew < 1) {
		x = 1;
	}
	mean = mNew;
	mOld = mNew;
	} while (x ==0);

	//5.
	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageText.getPointValue(i, n).getRed();
			green = imageText.getPointValue(i, n).getGreen();
			blue = imageText.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			gesamt += greyvalue;
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

	//Aufgabe 2
	//Histogramm
	CImage imageHistogramm("Images/rose_flau.bmp");
	imageHeight = imageHistogramm.getHeight();
	imageWidth = imageHistogramm.getWidth();
	int histogramm[255];//Position,Anzahl
	float histogrammKumuliert[255];
	int wertegesamt = 0;;
	x = 0;

	for (int i = 0; i < 255; i++)
	{
		histogramm[i] = 0;
		histogrammKumuliert[i] = 0;
	}

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			x = 0;
			red = imageHistogramm.getPointValue(i, n).getRed();
			green = imageHistogramm.getPointValue(i, n).getGreen();
			blue = imageHistogramm.getPointValue(i, n).getBlue();
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
		std::cout <<"Histogramm: \n" << x << " -> " << histogramm[x] << "\n";//Histogramm normal
		x++;
	} while (x < 255);

	//Histogramm kumuliert
	std::cout << "Histogramm kumuliert";
	for (int i = 0; i < 255; i++)
	{

		if (i > 0) {
			histogrammKumuliert[i] =histogrammKumuliert[i-1]+ histogramm[i];
		}
		else {
			histogrammKumuliert[i] += histogramm[i];
		}
		//std::cout <<"Position: "<<i <<" "<< histogrammKumuliert[i] << "\n";
	}
	
	float newGreyValue=0;

	for (int i = 0; i < imageHeight; i++)
	{
		for (int n = 0; n < imageWidth; n++)
		{
			red = imageHistogramm.getPointValue(i, n).getRed();
			green = imageHistogramm.getPointValue(i, n).getGreen();
			blue = imageHistogramm.getPointValue(i, n).getBlue();
			greyvalue = (red + green + blue) / 3;
			newGreyValue = (histogrammKumuliert[greyvalue] / wertegesamt) * 255;

			//std::cout << "NeuerGrauwert an Position: "<<greyvalue <<" = "<<newGreyValue<< "\n";

			tmpPoint.setRed(newGreyValue);
			tmpPoint.setGreen(newGreyValue);
			tmpPoint.setBlue(newGreyValue);

			imageHistogramm.setPointValue(i, n, tmpPoint);
		}
	}
	imageHistogramm.showImage();

}