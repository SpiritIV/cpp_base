#include <iostream>

#include "../include/LevelGUI.h"
#include "../include/MyTools.h"
#include <random>

using namespace std;
using namespace MyTools;

void LevelGUI::Draw() const
{
    MyTools::SetColor(CC_White);

    /*--------------------Homework--------------------*/

    if (pMediator->GetSize())
    {
        std::cout << pMediator->GetMsg() << std::endl;
    }

    /*--------------------Homework--------------------*/

    GotoXY(x, y);
    char* buf = new (nothrow) char[width + 1];
    if (buf == nullptr)
    {
        return;
    }
    memset(buf, '+', width);
    buf[width] = '\0';
    cout << buf;
    GotoXY(x, y + height);
    cout << buf;
    delete [] buf;
    buf = nullptr;
    
    for (size_t i = size_t(y); i < height + y; i++)
    {
        GotoXY(x, (double)i);
        cout << "+";
        GotoXY(x + width - 1, (double)i);
        cout << "+";
    }

    GotoXY(3, 1);
    cout << "FramePerSecond: " << static_cast<int>(fps / (passedTime / 1000.0));
    GotoXY(25, 1);
    cout << "PassedTime: " << static_cast<int>(passedTime / 1000.0) << " sec";
    GotoXY(46, 1);
    cout << "BombsNum: " << bombsNumber;
    GotoXY(62, 1);
    cout << "Score: " << score;
}

void __fastcall LevelGUI::SetParam(uint64_t passedTimeNew, uint64_t fpsNew, uint16_t bombsNumberNew, int16_t scoreNew)
{
    passedTime = passedTimeNew;
    fps = fpsNew;
    bombsNumber = bombsNumberNew;
    score = scoreNew;
}

/*--------------------Homework--------------------*/

void    Mediator::AddMessage()
{
    queue_of_msgs.push_back(randomPhrase[std::rand()%queue_of_msgs.size()]);
}

/*--------------------Homework--------------------*/