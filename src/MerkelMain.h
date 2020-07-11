#pragma once

#include <vector>
#include "OrderBookEntry.h"
#include "OrderBook.h"
#include "Wallet.h"
#include "TradeBot.h"

class MerkelMain
{
    public:
        /** generic constructor */
        MerkelMain();
        /** Call this to start the sim */
        void init();
        /** Receives an integer from the user*/
        static int getUserOption();
    private:
        void initUserMode();
        void initBotMode();
        void printMenu();
        void printStartMenu();
        void printHelp();
        void printMarketStats();
        void enterAsk();
        void enterBid();
        void printWallet();
        void gotoNextTimeframe();
        void processUserOption(int userOption);
        void processUserStartOption(int userOption);
        std::string username;
        std::string currentTime;
        OrderBook orderBook{"20200601.csv"};
        // OrderBook orderBook{"20200317.csv"};
        Wallet wallet;
        TradeBot bot{orderBook};
};
