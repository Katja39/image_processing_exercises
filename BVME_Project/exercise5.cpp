#include "CImage.h"
#include "CColor.h"
#include <iostream>
#include <cmath>

using namespace bvme;

int min;
int max;
int med;

int cmpfunc(const void* a, const void* b)
{
	return (*(int*)a - *(int*)b);
}

void measure(int list[], int length)
{
	qsort(list, 49, sizeof(int), cmpfunc);
	min = list[0];
	max = list[length * length - 1];
	med = list[(length * length - 1) / 2];
}

void exercise5() {
	CImage image("Images/schmetterling_saltpepper.bmp");
	image = image.getGreyscaleImage();

	int sMax = 7;
	int array[49];
	int windowSize = 3;
	int a1, a2, b1, b2;

	int m = image.getHeight();
	int n = image.getWidth();
	bool abort = true;
	int index = 0;

	CImage medianImage(m, n, true); //empty gray value image

	CColor tmpPoint(0);
	for (int i = 0; i < 49; i++)
	{
		array[i] = 1000;
	}

	for (int x = sMax / 2; x < m - sMax / 2; x++)
	{
		for (int y = sMax / 2; y < n - sMax / 2; y++)
		{
			windowSize = 3;
			while (abort)
			{
				index = 0;
				for (int i = -windowSize / 2; i <= windowSize / 2; i++)
				{
					for (int j = -windowSize / 2; j <= windowSize / 2; j++)
					{
						array[index] = image.getPointValue(x + i, y + j).getGrey();
						index++;
					}

				}
				for (int k = index; k < 49; k++) //Padding the remaining array with values that are too large 
				{
					array[k] = 1000;
				}

				measure(array, windowSize); //calculate min, med, max 

				a1 = med - min;
				a2 = med - max;

				if (a1 > 0 && a2 < 0)
				{
					b1 = image.getPointValue(x, y).getGrey() - min;
					b2 = image.getPointValue(x, y).getGrey() - max;
					if (b1 > 0 && b2 < 0) 
					{
						tmpPoint.setGrey(image.getPointValue(x, y).getGrey());
						medianImage.setPointValue(x, y, tmpPoint);
						abort = false;
						break;
					}
					else 
					{
						tmpPoint.setGrey(med);
						medianImage.setPointValue(x, y, tmpPoint);
						abort = false;
						break;
					}
				}
				else if (windowSize < sMax) 
				{
					windowSize += 2;
				}
				else 
				{
					tmpPoint.setGrey(image.getPointValue(x, y).getGrey());
					medianImage.setPointValue(x, y, tmpPoint);
					abort = false;
					break;
				}
			}
			abort = true;
		}
	}
	medianImage.showImage("adaptive median filter");
}
