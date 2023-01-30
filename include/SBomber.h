#pragma once

#include <vector>

#include "LevelGUI.h"
#include "Plane.h"
#include "Bomb.h"
#include "Ground.h"
#include "Tank.h"

/*---------------------Command pattern---------------------------*/

class	Command
{
public:
	virtual ~Command() {}

	virtual	void	Execute() = 0;
};

class DeleteCommand : public Command
{
private:
	GameObject					*game_object;
	std::vector<GameObject*>	*vec_objects;
public:
	DeleteCommand(GameObject *_game_object, std::vector<GameObject*> *_vec_objects) : 
					game_object(_game_object), vec_objects(_vec_objects) {};

	void	Execute() override;

	~DeleteCommand() { if (game_object != nullptr) delete game_object; };
};

class DeleteDynamicCommand : public Command
{
private:
	DynamicObject				*game_object;
	std::vector<DynamicObject*>	*vec_objects;
public:
	DeleteDynamicCommand(DynamicObject *_game_object, std::vector<DynamicObject*> *_vec_objects) : 
					game_object(_game_object), vec_objects(_vec_objects) {};

	void	Execute() override;

	~DeleteDynamicCommand() { if (game_object != nullptr) delete game_object; };
};

class DropBomb : public Command
{
private:
	Plane						*plane;
	int16_t						*score;
	uint16_t					*bombsNumber;
	DynamicObject				*game_object;
	std::vector<DynamicObject*>	*vec_objects;
public:
	DropBomb(Plane *_plane, DynamicObject *_game_object, uint16_t *bombsNumber, std::vector<DynamicObject*> *_vec_objects, int16_t *_score) : 
	plane(_plane), game_object(_game_object), bombsNumber(bombsNumber), vec_objects(_vec_objects), score(_score)  {};

	~DropBomb() { };

	void	Execute() override;
};

/*--------------------------------------------------------------------*/

class SBomber
{
public:

    SBomber();
    ~SBomber();
    
	inline bool								GetExitFlag() const { return exitFlag; }

	void									ProcessKBHit();
	void									TimeStart();
	void									TimeFinish();

	void									DrawFrame();
	void									MoveObjects();
	void									CheckObjects();

	// void __fastcall						DeleteDynamicObj(DynamicObject * pBomb);
	// void __fastcall						DeleteStaticObj(GameObject* pObj);
	// void __fastcall						DeleteObj(GameObject* pObj);

	// void									DropBomb();

	void									CommandExecuter(Command *pCommand);

private:

	void									CheckPlaneAndLevelGUI();
	void									CheckBombsAndGround();
	void __fastcall							CheckDestoyableObjects(Bomb* pBomb);

	Ground									*FindGround() const;
	Plane									*FindPlane() const;
	LevelGUI								*FindLevelGUI() const;
	std::vector<DestroyableGroundObject*>	FindDestoyableGroundObjects() const;
	std::vector<Bomb*>						FindAllBombs() const;

	/*---------------------Put to the command---------------------*/

	std::vector<DynamicObject*>				vecDynamicObj;
	std::vector<GameObject*>				vecStaticObj;
	std::vector<Command *>					all_commands;

	/*------------------------------------------------*/

	bool									exitFlag;

	uint64_t								startTime, finishTime, passedTime;
	uint16_t								bombsNumber, deltaTime, fps;
	int16_t									score;
};