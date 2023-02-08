
#include <conio.h>
#include <windows.h>
#include <stdint.h>
#include <time.h> 

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>

#include "../include/MyTools.h"

using namespace std;

namespace MyTools {


    void ClrScr()
    {
        system("cls");
    }

    void __fastcall GotoXY(double x, double y)
    {
        const COORD cc = { short(x), short(y) };
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cc);
    }

    uint16_t GetMaxX()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Right;
                int height = consoleInfo.srWindow.Bottom - consoleInfo.srWindow.Top + 1;
            }
        }

        return 0;
    }

    uint16_t GetMaxY()
    {
        HANDLE hWndConsole;
        if (hWndConsole = GetStdHandle(-12))
        {
            CONSOLE_SCREEN_BUFFER_INFO consoleInfo;
            if (GetConsoleScreenBufferInfo(hWndConsole, &consoleInfo))
            {
                return consoleInfo.srWindow.Bottom;
            }
        }

        return 0;
    }

    void SetColor(ConsoleColor color)
    {
        HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hConsole, color); // color =  (WORD)((BackgroundColor << 4) | TextColor))
    }

}; // namespace MyTools

//FileLoggerSingletone definition

FileLoggerSingletone	*FileLoggerSingletone::s_file = nullptr;

FileLoggerSingletone	*FileLoggerSingletone::GetInstance(const std::string &path)
{
	if (s_file == nullptr)
	{

		s_file = new FileLoggerSingletone(path);
	}
	return (s_file);
}

std::string		FileLoggerSingletone::GetCurDateTime(void)
{
	auto	cur = std::chrono::system_clock::now();
	time_t	time = std::chrono::system_clock::to_time_t(cur);
	char	buf[64] = { 0 };
        
	ctime_s(buf, 64, &time);
    buf[strlen(buf) - 1] = '\0';
	return (string(buf));
}

void __fastcall	FileLoggerSingletone::OpenLogFile(void)
{
	logOut.open(path_to_log, ios_base::out);
}

void FileLoggerSingletone::CloseLogFile(void)
{
	if (logOut.is_open())
 	{
		logOut.close();
	}
}

void __fastcall FileLoggerSingletone::WriteToLog(const string& str)
{
    if (logOut.is_open())
	{
		logOut << GetCurDateTime() << " - " << str << endl;
	}
}

void __fastcall FileLoggerSingletone::WriteToLog(const string& str, int n)
{
	if (logOut.is_open())
	{
		logOut << GetCurDateTime() << " - " << str << n << endl;
	}
}

void __fastcall FileLoggerSingletone::WriteToLog(const string& str, double d)
{
	if (logOut.is_open())
	{
		logOut << GetCurDateTime() << " - " << str << d << endl;
	}
}

//Modify logging

ModifyLogging	*ModifyLogging::ancor_pointer = nullptr;
int				ModifyLogging::index = 0;

ModifyLogging	*ModifyLogging::GetInstance(const std::string &path)
{
	if (ancor_pointer == nullptr)
	{

		ancor_pointer = new ModifyLogging(path);
	}
	return (ancor_pointer);
}

std::string		ModifyLogging::GetCurDateTime(void)
{
	auto	cur = std::chrono::system_clock::now();
	time_t	time = std::chrono::system_clock::to_time_t(cur);
	char	buf[64] = { 0 };
        
	ctime_s(buf, 64, &time);
    buf[strlen(buf) - 1] = '\0';
	return (string(buf));
}

void __fastcall	ModifyLogging::OpenLogFile(void)
{
	logOut.open(path_to_log, ios_base::out);
}

void ModifyLogging::CloseLogFile(void)
{
	if (logOut.is_open())
 	{
		logOut.close();
	}
}

void __fastcall ModifyLogging::WriteToLog(const string& str)
{
    if (logOut.is_open())
	{
		logOut << index << ". " <<GetCurDateTime() << " - " << str << endl;
		++index;
	}
}

void __fastcall ModifyLogging::WriteToLog(const string& str, int n)
{
	if (logOut.is_open())
	{
		logOut << index << ". " << GetCurDateTime() << " - " << str << n << endl;
		++index;
	}
}

void __fastcall ModifyLogging::WriteToLog(const string& str, double d)
{
	if (logOut.is_open())
	{
		logOut << index << ". " << GetCurDateTime() << " - " << str << d << endl;
		++index;
	}
}
