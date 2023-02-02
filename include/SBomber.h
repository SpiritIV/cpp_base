#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"
#include "DestroyableGroundObject.h"

/*----------------Home task----------------*/

class	BombIterator
{
private:
	std::vector<Bomb*>			vecBombs;
	std::vector<DynamicObject*>	vec_dynamic;
public:
	BombIterator(std::vector<DynamicObject*>& _vecDynamic) : vec_dynamic(_vecDynamic) {};
	
	std::vector<Bomb*>	FindAllBombs() const
	{
		std::vector<Bomb*> vecBombs;

    	for (size_t i = 0; i < vec_dynamic.size(); i++)
    	{
        	Bomb* pBomb = dynamic_cast<Bomb*>(vec_dynamic[i]);
        	if (pBomb != nullptr)
        	{
            	vecBombs.push_back(pBomb);
        	}
    	}

    	return (vecBombs);
	}
};

class TankAdaptee : public DestroyableGroundObject
{
protected:
	Tank			tank;
	double			x, y;
	uint16_t		width;
	const uint16_t	score = 30;
public:
	TankAdaptee(Tank &_tank) : x(0.0), y(0.0), width(0), tank(_tank) { }
	
	void 			Paint() const;
	bool __fastcall	isInRange(double x1, double x2) const;
	inline uint16_t	GetScore() const { return score; }
	inline void		SetPos(double nx, double ny);
	inline double	GetY() const { return y; }
	inline double	GetX() const { return x; }
	inline void		SetWidth(uint16_t widthN) { width = widthN; }
	inline uint16_t	GetWidth() const;
};

/*-----------------------------------------*/

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
    inline bool GetExitFlag() const { return exitFlag; }

    void ProcessKBHit();
    void TimeStart();
    void TimeFinish();

    void DrawFrame();
    void MoveObjects();
    void CheckObjects();

	/*----------------Home task----------------*/

	int		begin();
	int		end();

	/*-----------------------------------------*/

private:

    void			CheckPlaneAndLevelGUI();
    void			CheckBombsAndGround();
    void __fastcall	CheckDestoyableObjects(Bomb* pBomb);

    void __fastcall DeleteDynamicObj(DynamicObject * pBomb);
    void __fastcall DeleteStaticObj(GameObject* pObj);

    Ground * FindGround() const;
    Plane * FindPlane() const;
    LevelGUI * FindLevelGUI() const;
    std::vector<DestroyableGroundObject*> FindDestoyableGroundObjects() const;

    std::vector<Bomb*>	FindAllBombs() const;

    void DropBomb();

    std::vector<DynamicObject*>	vecDynamicObj;
    std::vector<GameObject*>	vecStaticObj;
    
    bool exitFlag;

    uint64_t startTime, finishTime, passedTime;
    uint16_t bombsNumber, deltaTime, fps;
    int16_t score;
};