#pragma once
#include "OrderBookEntry.h"
#include <vector>
#include <string>


class CSVReader
{
    public:
    /** generic constructor */
     CSVReader();
    /**reads a CSV from a given file and returns a vector of OrderBookEntry elements*/
     static std::vector<OrderBookEntry> readCSV(std::string csvFile);
     /**splits lines in given csv file along a given serparator into tokens
      * returns vector of token strings*/
     static std::vector<std::string> tokenise(std::string csvLine, char separator);
    /**From given strings and OrderBookType, returns OrderBookEntry*/
     static OrderBookEntry stringsToOBE(std::string price, 
                                        std::string amount, 
                                        std::string timestamp, 
                                        std::string product, 
                                        OrderBookType OrderBookType);
    private:
     static OrderBookEntry stringsToOBE(std::vector<std::string> strings);
     
};