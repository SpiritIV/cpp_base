
#include <iostream>

#include "../include/Bomb.h"
#include "../include/MyTools.h"

using namespace std;
using namespace MyTools;

void Bomb::Draw() const
{
    MyTools::SetColor(CC_LightMagenta);
    GotoXY(x, y);
    cout << "*";
}

/* ------------------ Task 1 ------------------ */

Bomb*	Bomb::clone()
{
    x -= 1;

    return (this);
};

/* ------------------ Task 1 ------------------ */