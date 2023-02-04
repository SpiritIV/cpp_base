#pragma once

#include <stdint.h>

#include "DestroyableGroundObject.h"

/* -----------------------Builder pattern----------------------- */

class House : public DestroyableGroundObject
{
public:
	House();
	~House();

	bool __fastcall isInside(double x1, double x2) const override;

	inline uint16_t GetScore() const override { return score; }

	uint16_t	getHouseHeight() const { return (house_height); };
	uint16_t	getHouseWidth() const { return (house_width); };

	void		setObj(uint16_t row, char *obj) { look[row] = obj; };

	void Draw() const override;

private:
	const uint16_t	house_height = 7;
	const uint16_t	house_width = 14;

	char			**look;
	const uint16_t	score = 40;
};

class HouseBuilder
{
protected:
	House	*house;
public:
	HouseBuilder() : house(new House) {};
	virtual ~HouseBuilder() { delete house; };

	void	createRoof();
	void	createBasement();
	
	virtual	void	createWall() {};
	virtual void	createPipe() {};
	virtual void	createWindow() {};
	
	virtual House*	getHouse() const { return (house); }
};

class HouseBuilderA : public HouseBuilder
{
public:
	void	createWindow() override
	{
		house->setObj(3, "*    ****    *");
		house->setObj(2, "*    *  *    *");
		house->setObj(1, "*    ****    *");
	};
};

class HouseBuilderB : public HouseBuilder
{
public:
	void	createPipe() override
	{
		house->setObj(6, "          **  ");
		house->setObj(5, "          **  ");
	};
	void	createWall() override
	{
		house->setObj(3, "*            *");
		house->setObj(2, "*            *");
		house->setObj(1, "*            *");
	};
};

class Director
{
public:
	House*	createHouse(HouseBuilder& builder)
	{
		builder.createPipe();
		builder.createRoof();
		builder.createWindow();
		builder.createWall();
		builder.createBasement();

		return (builder.getHouse());
	}
};



