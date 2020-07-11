#include "Logger.h"
#include <algorithm>

std::ofstream Logger::logFile;
std::map<Logger::Level, std::string> Logger::levelString
{
    {Logger::Level::DEBUG, "DEBUG"},
    {Logger::Level::INFO, "INFO"},
    {Logger::Level::WARNING, "WARNING"},
    {Logger::Level::ERROR, "ERROR"}
};

Logger::Logger()
{
    start();
}

void Logger::start()
{
    logFile.open("log.txt");
}

void Logger::stop()
{
    logFile.close();
}

void Logger::write(Level level, std::string message)
{
    if(level >= minLevel)
    {
        std::string cTimeNoNewLine;
        time_t timeNow = time(NULL); //get raw time
        cTimeNoNewLine = ctime(&timeNow); //convert to string
        cTimeNoNewLine.erase(cTimeNoNewLine.length()-6); //erase new line and year

        logFile << cTimeNoNewLine << " - [" << levelToString(level) << "] - " << message << std::endl;
    }
}

std::string Logger::formatCurrentTime(std::string currentTime)
{
    return lineBreak + "\n" + spaceAfterINFOLine + "Current time: " + currentTime + "\n" + spaceAfterINFOLine + lineBreak;
}


void Logger::setMinLevel(Level level)
{
    minLevel = level;
}

std::string Logger::levelToString(Level level)
{
    return levelString[level];
}