
#include <iostream>

#include "../include/Plane.h"
#include "../include/MyTools.h"

using namespace std;
using namespace MyTools;

/*--------------------Homework--------------------*/

void    Plane::DrawBody() const
{
    MyTools::SetColor(CC_LightBlue);

    GotoXY(x, y);
    cout << "=========>";
}

void	Plane::DrawWings() const
{
	MyTools::SetColor(CC_LightBlue);

    GotoXY(x - 2, y - 1);
    cout << "===";
}

void	Plane::DrawTail() const
{
	MyTools::SetColor(CC_LightBlue);

    GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 1);
    cout << "////";
}

void	Plane::Draw() const
{
    DrawBody();
	DrawWings();
	DrawTail();   
}

void    ColorPlane::DrawBody() const
{
    MyTools::SetColor(CC_Cyan);

    GotoXY(x, y);
    cout << "=========>";
}

void	ColorPlane::DrawWings() const
{
	MyTools::SetColor(CC_Green);

    GotoXY(x - 2, y - 1);
    cout << "===";
}

void	ColorPlane::DrawTail() const
{
	MyTools::SetColor(CC_LightRed);

    GotoXY(x + 3, y - 1);
    cout << "\\\\\\\\";
    GotoXY(x + 3, y + 1);
    cout << "////";
}

/*--------------------Homework--------------------*/