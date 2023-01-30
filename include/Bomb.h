#pragma once

#include <iostream>
#include "MyTools.h"
#include "DynamicObject.h"


class Bomb : public DynamicObject
{
public:

	static const uint16_t BombCost = 10; // ��������� ����� � �����

	void Draw() const override;

private:

};

class BombDecorator : public DynamicObject
{
private:
	Bomb	bomb;
public:
	BombDecorator(Bomb	&_bomb) : bomb(_bomb) {};

	void		Move(uint16_t time) override;
	void		Draw() const override;
	
	void 		SetPos(double nx, double ny) { bomb.SetPos(nx, ny); }
	uint16_t 	GetWidth() const { return bomb.GetWidth(); }
};

void	BombDecorator::Move(uint16_t time)
{
	bomb.Move(static_cast<uint16_t>(time * 1.6));
}

void	BombDecorator::Draw() const
{
	bomb.Draw();

	// Некоторое изменение внешнего вида бомбы
	MyTools::GotoXY(bomb.GetX(), bomb.GetY() - 1);
	std::cout << "|";
}
