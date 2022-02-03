#include "CImage.h"
#include "CColor.h"
#include <iostream>

using namespace bvme;

void exercise6() { //Histogrammlinearisierung in RGB
	//Farbbild -> 3 Grauwertbilder
	CImage image("Images/rose_rgb_flau.bmp");

	int redValue[255] = { 0 };
	int greenValue[255] = { 0 };
	int blueValue[255] = { 0 };

	float redValueSum[255] = { 0 };
	float greenValueSum[255] = { 0 };
	float blueValueSum[255] = { 0 };

	int red = 0;
	int green = 0;
	int blue = 0;

	int imageHeight = image.getHeight();
	int imageWidth = image.getWidth();
	
	CColor Color = image.getPointValue(1, 1);

	image.showImage();

	for (int i = 0; i < imageWidth; i++)
	{
		for (int n = 0; n < imageHeight; n++)
		{
			red = image.getPointValue(n,i).getRed();
			green = image.getPointValue(n,i).getGreen();
			blue = image.getPointValue(n,i).getBlue();
			
			redValue[red] += 1;
			greenValue[green] += 1;
			blueValue[green] += 1;
		}
	}

	for (int i = 0; i < 255; i++)
	{
		for (int n = 0; n <= i; n++)
		{
			redValueSum[i]   += redValue[n];
			greenValueSum[i] += greenValue[n];
			blueValueSum[i]  += blueValue[n];
		}
	}

	for (int i = 0; i < 255; i++)
	{
		redValueSum[i] = redValueSum[i] / imageWidth * imageHeight;
		redValueSum[i]   = redValueSum[i] *255;

		greenValueSum[i] = greenValueSum[i] / imageWidth * imageHeight;
		greenValueSum[i] = greenValueSum[i] * 255;

		blueValueSum[i] = blueValueSum[i] / imageWidth * imageHeight;
		blueValueSum[i]  = blueValueSum[i] * 255;
	}


for (int i = 0; i < imageWidth; i++)
	{
		for (int n = 0; n < imageHeight; n++)
		{
			red = image.getPointValue(n,i).getRed();
			green = image.getPointValue(n, i).getGreen();
			blue = image.getPointValue(n, i).getBlue();

			Color.setRed(redValueSum[red]);
			Color.setGreen(redValueSum[green]);
			Color.setBlue(redValueSum[blue]);

			image.setPointValue(n, i, Color);
		}
	}
	image.showImage();
}