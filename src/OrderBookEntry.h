#pragma once

#include <string>

enum class OrderBookType{bid, ask, unknown, asksale, bidsale};

class OrderBookEntry
{
    public:
        /** construct via given parameters */
        OrderBookEntry( double _price, 
                        double _amount, 
                        std::string _timestamp, 
                        std::string _product, 
                        OrderBookType _orderType, 
                        std::string username = "dataset");

        /**Convert given string to OrderBookType*/
        static OrderBookType stringToOrderBookType(std::string s);
        /**Convert given OrderBookType to string*/
        static std::string typeToString(OrderBookType orderType);
        /**Returns true if first given OrderBookEntry time is less than second*/
        static bool compareByTimestamp(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.timestamp < e2.timestamp;
        }
        /**Returns true if first given OrderBookEntry price is less than second*/
        static bool compareByPriceAsc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price < e2.price;
        }
        /**Returns true if first given OrderBookEntry price is more than second*/
         static bool compareByPriceDesc(OrderBookEntry& e1, OrderBookEntry& e2)
        {
            return e1.price > e2.price;
        }
        double price;
        double amount;
        std::string timestamp;
        std::string product;
        OrderBookType orderType;
        std::string username;
};
