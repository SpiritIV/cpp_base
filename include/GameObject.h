#pragma once

class GameObject {
public:

    GameObject() : x(0.0), y(0.0), width(0) { }

    virtual void		Draw() const = 0;
	// virtual void		Move(uint16_t time) = 0;

    virtual void		SetPos(double nx, double ny) { x = nx; y = ny; }

    virtual double		GetY() const { return y; }
    virtual double		GetX() const { return x; }

    virtual void		SetWidth(uint16_t widthN) { width = widthN; }
    virtual uint16_t	GetWidth() const { return width; }

protected:

    double		x;
	double		y;
    uint16_t	width;
};