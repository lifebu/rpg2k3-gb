#include "Logger.h"

#include <cassert>
#include <iostream>

const static std::string ERR_LOGFILE_IO = "Logfile could not be opened.";

Logger::~Logger() 
{
    Shutdown();
}

void Logger::Init(std::string logFilePrefix, int logMask) 
{
    m_LogMask = logMask;

    if(m_LogMask & LOGMASK::LOG_MODE_FILE)
    {
        m_LogFile.open(logFilePrefix + LOG_FILE);
        if(!m_LogFile.is_open())
        {
            Log(ERR_LOGFILE_IO, LogLevel::ERROR);
        }
    }
}

void Logger::Shutdown() 
{
    if(m_LogFile.is_open())
    {
        m_LogFile.close();
    }
}

void Logger::Log(std::string message, LogLevel logLevel)
{
    const std::string newEntry = GenerateLogLevelPrefix(logLevel) + message;
    m_Log.push_back(newEntry);

    if(logLevel == LogLevel::GB_PANIC) 
    {
        m_IsInPanic = true;
    }

    if(m_LogMask & LOGMASK::LOG_MODE_FILE && m_LogFile.is_open())
    {
        m_LogFile << newEntry << std::endl;
    }

    if(m_LogMask & LOGMASK::LOG_MODE_STDOUT) 
    {
        if(logLevel >= LogLevel::ERROR)
        {
            std::cerr << newEntry << std::endl;
        }
        else
        {
            std::cout << newEntry << std::endl;
        }
    }
}

bool Logger::IsInPanic()
{
    return m_IsInPanic;
}

const std::vector<std::string>& Logger::GetLog()
{
    return m_Log;
}

std::string Logger::GenerateLogLevelPrefix(LogLevel logLevel)
{
    switch(logLevel)
    {
        case LogLevel::INFO:
            return "[INFO]     ";
        case LogLevel::WARNING:
            return "[WARNING]  ";
        case LogLevel::ERROR:
            return "[ERROR]    ";
        case LogLevel::GB_PANIC:
            return "[GB_PANIC] ";
    }

    return "";
}