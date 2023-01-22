#pragma once

#include <stdint.h>
#include <string>
#include <fstream>
#include <iostream>

namespace MyTools {

    // ������� ������ �� 0 �� 15
    enum ConsoleColor
    {
        CC_Black = 0,
        CC_Blue,
        CC_Green,
        CC_Cyan,
        CC_Red,
        CC_Magenta,
        CC_Brown,
        CC_LightGray,
        CC_DarkGray,
        CC_LightBlue,
        CC_LightGreen,
        CC_LightCyan,
        CC_LightRed,
        CC_LightMagenta,
        CC_Yellow,
        CC_White
    };

	//=============================================================================================

	void ClrScr();

	void __fastcall GotoXY(double x, double y);

	uint16_t GetMaxX();

	uint16_t GetMaxY();

    void SetColor(ConsoleColor color);

};

//Proxy for logging

class ILogging
{
public:
	virtual void __fastcall	OpenLogFile(void) = 0;
    virtual void			CloseLogFile(void) = 0;
    virtual void __fastcall	WriteToLog(const std::string& str) = 0;
    virtual void __fastcall	WriteToLog(const std::string& str, int n) = 0;
    virtual void __fastcall WriteToLog(const std::string& str, double d) = 0;
	virtual std::string		GetCurDateTime(void) = 0;
};

//Logging singletone

class FileLoggerSingletone : public ILogging
{
private:
	std::ofstream               logOut;
    std::string     			path_to_log;
    static FileLoggerSingletone	*s_file;

    FileLoggerSingletone(const std::string _path) : path_to_log(_path) {}
    FileLoggerSingletone(FileLoggerSingletone &) = delete;
	~FileLoggerSingletone() {if (s_file != nullptr) { delete s_file; }; };
    
    void    operator=(const FileLoggerSingletone &) = delete;

public:
	static FileLoggerSingletone	*GetInstance(const std::string &path);

	std::string		GetCurDateTime(void);

	void __fastcall			OpenLogFile(void);
    void					CloseLogFile(void);
    void __fastcall	WriteToLog(const std::string& str);
    void __fastcall	WriteToLog(const std::string& str, int n);
    void __fastcall WriteToLog(const std::string& str, double d);
};

class ModifyLogging : public ILogging
{
private:
    static int		index;		
	std::ofstream	logOut;
    std::string		path_to_log;

	ModifyLogging(const std::string _path) : path_to_log(_path) {}
    ModifyLogging(ModifyLogging &) = delete;
	void	operator=(ModifyLogging &) = delete;
    static      ModifyLogging   *ancor_pointer;
public:
    static ModifyLogging   *GetInstance(const std::string &path);

	std::string		GetCurDateTime(void);

	void __fastcall	OpenLogFile(void);
    void			CloseLogFile(void);
    void __fastcall	WriteToLog(const std::string& str);
    void __fastcall	WriteToLog(const std::string& str, int n);
    void __fastcall WriteToLog(const std::string& str, double d);
};
