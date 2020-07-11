#pragma once
#include <fstream>
#include <string>
#include <map>
#include <time.h>

class Logger
{
    public:
        /**Different log levels*/
        enum Level{DEBUG, INFO, WARNING, ERROR};
        /** generic constructor */
        Logger();
        /**Stop the logger*/
        static void stop();
        /**Write to log
         * takes a level and string as input*/
        void write(Level level, std::string message);
        /**Returns formatted string for given current time*/
        std::string formatCurrentTime(std::string currentTime);
        /**A string of spaces to continue a message on a new line for INFO messages.*/
        std::string spaceAfterINFOLine = std::string(31, ' ');
        /**Set the minimum level you want to log from given level*/
        void setMinLevel(Level level);
    private:
        Level minLevel;
        static std::map<Level, std::string> levelString;
        std::string lineBreak = std::string(40, '#');
        static std::string levelToString(Level level);
        static void start();
        static std::ofstream logFile;
};