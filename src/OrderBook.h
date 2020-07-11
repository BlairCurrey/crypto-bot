#pragma once
#include "OrderBookEntry.h"
#include "CSVReader.h"
#include <string>
#include <vector>
#include <unordered_map> 

class OrderBook
{
    public:
    /** construct, reading a csv data file */
        OrderBook(std::string filename);
    /** return vector of all know products in the dataset*/
        std::vector<std::string> getKnownProducts();
    /** return vector of Orders according to the sent filters*/
        std::vector<OrderBookEntry> getOrders(OrderBookType type, 
                                              std::string product, 
                                              std::string timestamp);
        /** returns the earliest time in the orderbook*/
        std::string getEarliestTime();
        /** returns the next time after the current time
         * sent time in the orderbook  
         * If there is no next timestamp, wraps around to the start*/
        std::string getNextTime(std::string timestamp);
        /** adds given order to orderbook*/
        void insertOrder(OrderBookEntry& order);
        /** finds matching asks and bids for a given product, timestamp, and username
         * returns a vector of sales*/
        std::vector<OrderBookEntry> matchAsksToBids(std::string product, std::string timestamp, std::string username);
        /** returns high price for a given vector of OrderBookEntries*/
        static double getHighPrice(std::vector<OrderBookEntry>& orders);
        /** returns low price for a given vector of OrderBookEntries*/
        static double getLowPrice(std::vector<OrderBookEntry>& orders);
        /**sets the productMinAsks for a given time*/
        void setProductMinAsks(std::string time);
        /**retrieves mimumum ask price saved to the map for given product*/
        double getProductMinAsks(std::string product);
        /**returns max bid for given product and time*/
        double findProductMaxBid(std::string product, std::string time);
    private:
        std::vector<OrderBookEntry> orders;
        std::unordered_map<std::string, double> productMinAsks;
};
