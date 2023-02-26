
#include <conio.h>

#include "./include/SBomber.h"
#include "./include/MyTools.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    // MyTools::OpenLogFile("log.txt");

    SBomber game;

    do {
        game.TimeStart();

        if (_kbhit())
        {
            game.ProcessKBHit();
        }

        MyTools::ClrScr();

        game.DrawFrame();
        game.MoveObjects();
        game.CheckObjects();

        game.TimeFinish();

    } while (!game.GetExitFlag());

    // MyTools::CloseLogFile();

    return 0;
}
