#pragma once

#include "Singleton.h"

#include <fstream>
#include <string>
#include <vector>

enum class LogLevel
{
    INFO = 0,
    WARNING = 1,
    ERROR = 2,
    GB_PANIC = 3
};

namespace LOGMASK
{
    constexpr int LOG_MODE_FILE = 1;
    constexpr int LOG_MODE_STDOUT = 2;
}

const static std::string LOG_FILE = "log.txt";

class Logger : public Singleton<Logger>
{
public:
    ~Logger();

    void Init(std::string logFilePrefix, int logMask);
    void Shutdown();

    void Log(std::string message, LogLevel logLevel);

    bool IsInPanic();
 
    const std::vector<std::string>& GetLog();

private:
    std::string GenerateLogLevelPrefix(LogLevel logLevel);

private:
    bool m_IsInPanic = false;
    std::vector<std::string> m_Log;
    int m_LogMask;
    std::ofstream m_LogFile;
};