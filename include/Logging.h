#ifndef LOGGING_H
# define LOGGING_H

#include "MyTools.h"

class FileLogger
{
public:
    FileLogger() { MyTools::OpenLogFile("log.txt"); };
    ~FileLogger() { MyTools::CloseLogFile(); };
};

#endif