#pragma once

#include "DynamicObject.h"

class Plane : public DynamicObject {
public:
    /*--------------------Homework--------------------*/

    virtual void    DrawBody() const;
	virtual void	DrawWings() const;
	virtual void	DrawTail() const;

	void Draw() const override;

    /*--------------------Homework--------------------*/

    inline void ChangePlaneY(double dy) { yDirection += dy; }

private:

};

class ColorPlane : public Plane
{
public:
	virtual void    DrawBody() const override;
	virtual void	DrawWings() const override;
	virtual void	DrawTail() const override;
};



