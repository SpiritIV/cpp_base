#pragma once

#include <iostream>
#include <stdint.h>
#include <vector>
#include <string>

#include "GameObject.h"
#include "SBomber.h"
#include "MyTools.h"

class Plane;
class Bomb;

/*-------------------Task 1-------------------*/

class Visitor
{
public:
	virtual	void log(Plane* _plane) = 0;
	virtual	void log(Bomb* _bomb) = 0;
};

class LogVisitor : public Visitor
{
public:
	void	log(Plane* _plane) override;
	void	log(Bomb* _bomb) override;
};

class DynamicObject : public GameObject
{
public:

    DynamicObject() : speed(0.0), xDirction(0.0), yDirection(0) { }

    inline void SetSpeed(double sp) 
    {
        speed = sp;
    }

    inline void SetDirection(double dx, double dy)
    {
        xDirction = dx; yDirection = dy;
    }
    
    virtual void		Move(uint16_t time)
    {
        x += xDirction * speed * time * 0.001;
        y += yDirection * speed * time * 0.001;
    };

	/*-------------------Task 1-------------------*/

    double              GetSpeed(void)
    {
        return (speed);
    };

    std::vector<double>	GetDirection(void)
	{
		return { xDirction, yDirection };
	}

	virtual void		Accept(Visitor& v) = 0;

	/*--------------------------------------------*/

protected:

    double speed;
    double xDirction, yDirection;

};

class Plane : public DynamicObject {
public:

    void			Draw() const override;

    inline void		ChangePlaneY(double dy)
	{
		yDirection += dy;
	}

	/*-------------------Task 1-------------------*/

	void 	Accept(Visitor& v)
	{
		v.log(this);
	}

	/*--------------------------------------------*/
};


class Bomb : public DynamicObject
{
private:
	std::vector<DestroyableGroundObject*> vecDestoyableObjects;
public:

	static const uint16_t		BombCost = 10;

	void						Draw() const override;

	DestroyableGroundObject*    AddObserver(std::vector<DestroyableGroundObject*> _vecDestoyableObjects);

	bool						HandleInsideCheck(DestroyableGroundObject* _dest_obj);

	void						Accept(Visitor& v)
	{
		v.log(this);
	};
};
