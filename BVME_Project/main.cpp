#include "exercise1.h"
#include "exercise2.h"
#include "exercise3.h"
#include <iostream>

int main()
{
	int input;
	std::cout << "Waehle Uebung\n";
	std::cin >> input;
	switch (input)
	{
	case 1:
		exercise();
		break;
	case 2:
		exercise2();
		break;
	case 3:
		exercise3();
		break;
	}
	std::cin >> input;
	return 0;
}