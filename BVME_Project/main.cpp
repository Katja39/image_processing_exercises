#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include "exercise4.h"
#include "exercise5.h"
#include "exercise6.h"
#include <iostream>

int main()
{
	int input;
	int exit = false;

	while(exit==false){
	std::cout << "Select exercise\n"<<
		"1: gray value image, binary image, max and min gray value\n"<<
		"2: \n"
		"7: Exit\n";


	std::cin >> input;

	switch (input)
	{
	case 1:
		exercise(); //gray value image, binary image, max and min gray value
		break;
	case 2:
		exercise2();
		break;
	case 3:
		exercise3();
		break;
	case 4:
		exercise4();
		break;
	case 5:
		exercise5();
		break;
	case 6:
		exercise6(); //Histogrammlinearisierung in RGB TODO
		break;
	case 7:
		exit = true;
		break;
	}
	}

	return 0;
}