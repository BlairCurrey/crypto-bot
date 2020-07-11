#pragma once
#include "OrderBook.h"
#include "Wallet.h"
#include <string>
#include "OrderBookEntry.h"
#include "Logger.h"
#include <fstream>
#include <unordered_map> 

class TradeBot
{
    public:
        /** construct via a given orderbook */
        TradeBot(OrderBook& _orderBook);
        /** Call this to start the bot */
        void init();
        /** Import a wallet to the bot's wallet */
        void loadWallet(Wallet newWallet);
        /** Import a time to current time */
        void loadCurrentTime(std::string newCurrentTime);
    private:
        void printLogMenu();
        void processUserLogOption(int userOption);
        void enterMarket();
        void exitMarket();
        void placeBid(double price, double amount, std::string product);
        void placeAsk(double price, double amount, std::string product);
        void gotoNextTimeframe();
        std::unordered_map<std::string, double> entryPoints;
        std::string username;
        OrderBook& orderBook;
        Wallet wallet;
        std::string currentTime;
        Logger logger;
};