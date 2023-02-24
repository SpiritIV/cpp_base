#pragma once

#include <stdint.h>

#include <vector>
#include <string>

#include "GameObject.h"

class Mediator;

class LevelGUI : public GameObject {
public:

	LevelGUI() : bombsNumber(0), score(0), passedTime(0), fps(0), height(0) {}
    LevelGUI(Mediator* pMed) : bombsNumber(0), score(0), passedTime(0), fps(0), height(0), pMediator(pMed) { }

    void __fastcall SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew);
    
    void __fastcall SetHeight(uint16_t heightN) { height = heightN; };
    
    inline uint16_t GetFinishX() const { return finishX; }
    inline void SetFinishX(uint16_t finishXN) { finishX = finishXN; }

    void Draw() const override;

private:

    uint16_t height;
    uint16_t finishX = 109;

    uint64_t passedTime, fps;
    uint16_t bombsNumber;
    int16_t score;

	/*--------------------Homework--------------------*/

	Mediator					*pMediator;

	/*--------------------Homework--------------------*/
};

/*--------------------Homework--------------------*/

class Mediator
{
private:
	std::vector<std::string>	queue_of_msgs;
	std::vector<std::string>	randomPhrase = {"Hey!", "Whats up?", "Oh no!", "Stop it!!!"};
public:
	void		AddMessage();

	std::string	GetMsg() { std::string	temp = queue_of_msgs.back(); queue_of_msgs.pop_back(); return (temp); };
	int			GetSize() { return (static_cast<int>(queue_of_msgs.size())); };
};

/*--------------------Homework--------------------*/


