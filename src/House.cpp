
#include <iostream>

#include "../include/House.h"
#include "../include/MyTools.h"

using namespace std;
using namespace MyTools;

bool House::isInside(double x1, double x2) const
{
	const double XBeg = x + 2;
	const double XEnd = x + width - 1;

	if (x1 < XBeg && x2 > XEnd)
	{
		return true;
	}

	if (x1 > XBeg && x1 < XEnd)
	{
		return true;
	}

	if (x2 > XBeg && x2 < XEnd)
	{
		return true;
	}

	return false;
}

void House::Draw() const
{
	MyTools::SetColor(CC_Yellow);
/* 	GotoXY(x, y - 5);
	cout << "  ########  ";
	GotoXY(x, y - 4);
	cout << "##        ##";
	GotoXY(x, y - 3);
	cout << "############";
	GotoXY(x, y - 2);
	cout << "#          #";
	GotoXY(x, y - 1);
	cout << "#          #";
	GotoXY(x, y);
	cout << "############"; */

	for (size_t floor = 6; floor >= 0; --floor)
	{
		GotoXY(x, y - floor);
		std::cout << look[floor];
	}
}

House::House()
{
	look = new char * [house_height];

	for (uint16_t i = 0; i < house_height; ++i)
	{
		look[i] = new char[house_width];

		for (uint16_t j = 0; j < house_width; ++j)
		{
			look[i][j] = ' ';
		}
	}
}

House::~House()
{
	// if (*look)
	// {
	// 	for (uint16_t i = 0; i < house_height; ++i)
	// 	{
	// 		delete[] look[i];
	// 	}
	// 	delete[] look;
	// }
}

void	HouseBuilder::createRoof()
{
	house->setObj(4, "**************");
};

void	HouseBuilder::createBasement()
{
	house->setObj(0, "**************");
};