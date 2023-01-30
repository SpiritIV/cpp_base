
#include <conio.h>

#include "./include/SBomber.h"
#include "./include/MyTools.h"

using namespace std;

//========================================================================================================================

int main(void)
{
    ILogging    *new_file = ModifyLogging::GetInstance("../../log.txt");
    SBomber		game;

    new_file->OpenLogFile();
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

    new_file->CloseLogFile();

    return 0;
}
