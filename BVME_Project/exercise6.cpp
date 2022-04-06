#include "CImage.h"
#include "CColor.h"
#include <iostream>

using namespace bvme;

void exercise6() {
	CImage image("Images/rose_rgb_flau.bmp");

	std::cout << "Histogram linearization is not recommended in RGB because the color changes.\n";

	int redValue[256] = { 0 };
	int greenValue[256] = { 0 };
	int blueValue[256] = { 0 };

	float redValueSum[256] = { 0 };
	float greenValueSum[256] = { 0 };
	float blueValueSum[256] = { 0 };

	int red = 0;
	int green = 0;
	int blue = 0;

	int imageHeight = image.getHeight();
	int imageWidth = image.getWidth();
	
	CColor Color = image.getPointValue(1, 1);

	image.showImage("original image");

	for (int i = 0; i < imageWidth; i++)
	{
		for (int n = 0; n < imageHeight; n++)
		{
			red = image.getPointValue(n,i).getRed();
			green = image.getPointValue(n,i).getGreen();
			blue = image.getPointValue(n,i).getBlue();
			
			redValue[red] += 1;
			greenValue[green] += 1;
			blueValue[blue] += 1;
		}
	}

	for (int i = 0; i < 256; i++)
	{
		for (int n = 0; n <= i; n++)
		{
			redValueSum[i]   += redValue[n];
			greenValueSum[i] += greenValue[n];
			blueValueSum[i]  += blueValue[n];
		}
	}

	double widthHeight = (double)image.getWidth() * (double)image.getHeight();

	for (int x = 0; x < image.getHeight(); x++)
	{
		for (int y = 0; y < image.getWidth(); y++)
		{
			CColor color = image.getPointValue(x, y);

			int redValue = 255 * ((double)redValueSum[color.getRed()] / widthHeight);
			int greenValue = 255 * ((double)greenValueSum[color.getGreen()] / widthHeight);
			int blueValue = 255 * ((double)blueValueSum[color.getBlue()] / widthHeight);

			color.setRed(redValue);
			color.setGreen(greenValue);
			color.setBlue(blueValue);

			image.setPointValue(x, y, color);
		}
	}

	image.showImage("changed image, wrong color");
	std::cout << "\n";
}