#include <string>
#include <conio.h>
#include <iostream>

#include "../include/SBomber.h"
#include "../include/MyTools.h"


static const size_t ScrollHeight = 30;
static const size_t ScrollWidth = 30;
static const char* ppScroll[ScrollHeight] =
{
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
" Project manager: ",
" Ivan Vasilevich ",
" ",
" Developers: ",
" Nikolay Gavrilov ",
" Dmitriy Sidelnikov ",
" Eva Brown ",
" ",
" Designers: ",
" Anna Pachenkova ",
" Elena Shvaiber ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        ",
"                        "};


void SBomber::AnimateScrolling()
{
	MyTools::WriteToLog(std::string(__FUNCTION__) + " was invoked");
	
	const size_t windowHeight = 10; // Размер окна для скроллинга
	const size_t startX = MyTools::GetMaxX() / 2 - ScrollWidth / 2;
	const size_t startY = MyTools::GetMaxY() / 2 - windowHeight / 2;

	double curPos = 0;
	do
	{
		TimeStart();
		MyTools::ClrScr();
		
		for (int i = curPos, j = 0; j < windowHeight; ++i, ++j)
		{
			std::cout << ppScroll[i] << std::endl;
		}

		
		MyTools::GotoXY(0, 0);
		TimeFinish();
		curPos += deltaTime * 0.0015;
	} while (!_kbhit() && int(curPos) <= (ScrollHeight - windowHeight));
	MyTools::ClrScr();
}
