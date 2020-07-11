#include "TradeBot.h"
#include <iostream>
#include "OrderBook.h"
#include "MerkelMain.h"
#include <string>
#include "Logger.h"
#include <cfloat>
#include "CSVReader.h"

TradeBot::TradeBot(OrderBook& _orderBook)
: orderBook(_orderBook)
{
    username = "simbot";
}

void TradeBot::init()
{
    int input;

    while(true)
    {
        printLogMenu();
        input = MerkelMain::getUserOption();
        processUserLogOption(input);
        //break out of loop if user picks on of the options
        if(input == 0 || 1 || 2 || 3)
        {
            break;
        }
    }

    logger.write(Logger::DEBUG, "TradeBot::init called");
    logger.write(Logger::INFO, logger.formatCurrentTime(currentTime));

    //Enter Market
    enterMarket();
    //Traverse through time periods
    while(orderBook.getNextTime(currentTime) > currentTime)
    {
        gotoNextTimeframe();
        enterMarket();
        exitMarket();
    }
}

void TradeBot::loadWallet(Wallet newWallet)
{
    wallet = newWallet;
}

void TradeBot::loadCurrentTime(std::string newCurrentTime)
{
    currentTime = newCurrentTime;
}

void TradeBot::printLogMenu()
{
    //Info and instructions
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Bot mode logs to 'log.txt' in the working directory." << std::endl;
    std::cout << "All logs are set with a level. What level (and above) do you want to log to file?" << std::endl;
    //Recommended settings
    std::cout << "Option 1: INFO is recommended for normal use " << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    //0 DEBUG
    std::cout << "0: DEBUG" << std::endl;
    //1 INFO
    std::cout << "1: INFO" << std::endl;
    //2 WARNING
    std::cout << "2: WARNING" << std::endl;
    //3 EROR
    std::cout << "3: ERROR" << std::endl;
}

void TradeBot::processUserLogOption(int userOption)
{
    //might be able to do logger.setMinLevel(userOption)
    //instead of all the if statements.
    if (userOption == 0)
    {
        logger.setMinLevel(Logger::DEBUG);
    }
    if (userOption == 1) 
    {
        logger.setMinLevel(Logger::INFO);
    }
    if (userOption == 2) 
    {
        logger.setMinLevel(Logger::WARNING);
    }
    if (userOption == 3) 
    {
        logger.setMinLevel(Logger::ERROR);
    }
}

void TradeBot::enterMarket()
{
    logger.write(Logger::DEBUG, "TradeBot::enterMarket called");
    
    //get lowest asking price for each product
    orderBook.setProductMinAsks(currentTime);
    for (std::string const& p : orderBook.getKnownProducts())
    {
        std::cout << DBL_MIN << std::endl;
        std::vector<std::string> currency_pair = CSVReader::tokenise(p, '/');
        std::string currency = currency_pair[0];
        //if wallet does not contain any of a currency, buy currency
        if(!wallet.containsCurrency(currency, DBL_MIN))
        {
            std::cout << "Checking wallet for currencies" << std::endl;
            std::cout << "Wallet contains " << currency << " : " << wallet.containsCurrency(currency, DBL_MIN) << std::endl;
            double minAsk = orderBook.getProductMinAsks(p);
            placeBid(minAsk, 1, p);
        }
    }
}

void TradeBot::exitMarket()
{
    logger.write(Logger::DEBUG, "TradeBot::exitMarket called");
    // loop through all entry points
    for (std::pair<std::string,double> p : entryPoints)
    {
        if(p.second > 0)
        {   
            //find the max bid
            std::string product = p.first;
            double maxBid = orderBook.findProductMaxBid(product, currentTime);
            std::string maxBidStr = std::to_string(maxBid);
            double purchasePrice = p.second;
            //if the max bid is more than the purchase price
            if(purchasePrice < maxBid)
            {
                //sell the product
                logger.write(Logger::INFO, "Selling " + p.first + " for: " + maxBidStr);
                logger.write(Logger::INFO, "Original purchase price: " + p.first + " for: " + maxBidStr);
                placeAsk(maxBid, 1, product);
            }
        }
    }
}

void TradeBot::placeBid(double price, double amount, std::string product)
{
    logger.write(Logger::DEBUG, "TradeBot::placeBid called");
    OrderBookType orderType = OrderBookType::bid;
    try {
        OrderBookEntry obe{price, amount, currentTime, product, orderType, username};
        logger.write(Logger::INFO, 
                     "Placing bid for " + std::to_string(amount) + 
                     " " + product + " at a rate of " + std::to_string(price)
                     );

        if (wallet.canFulfillOrder(obe))
        {
            std::cout << "Wallet has sufficient funds to accomodate bid." << std::endl;
            logger.write(Logger::INFO, "Wallet has sufficient funds to accomodate bid.");
            orderBook.insertOrder(obe);
            entryPoints.insert(std::pair<std::string,double>(product,price));
        }
        else {
            std::cout << "Wallet has insufficient funds to accomodate bid." << std::endl;
            logger.write(Logger::INFO, "Wallet has insufficient funds to accomodate bid.");
        }
    }catch (const std::exception& e)
    {
        std::cout << "Received invalid bid order." << std::endl;
        logger.write(Logger::WARNING, "Received invalid bid order.");
    }   
}

void TradeBot::placeAsk(double price, double amount, std::string product)
{
    logger.write(Logger::DEBUG, "TradeBot::placeAsk called");
    try {
        OrderBookEntry obe{price, amount, currentTime, product, OrderBookType::ask, username};
        logger.write(Logger::INFO, 
            "Placing ask for " + std::to_string(amount) + 
            " " + product + " at a rate of " + std::to_string(price)
            );

        if (wallet.canFulfillOrder(obe))
        {
            std::cout << "Wallet has sufficient funds to accomodate bid." << std::endl;
            logger.write(Logger::INFO, "Wallet has sufficient funds to accomodate bid.");
            orderBook.insertOrder(obe);
        }
        else {
            std::cout << "Wallet has insufficient funds to accomodate bid." << std::endl;
            logger.write(Logger::INFO, "Wallet has insufficient funds to accomodate bid.");
        }
    }catch (const std::exception& e)
    {
        std::cout << "Received invalid bid order." << std::endl;
        logger.write(Logger::WARNING, "Received invalid bid order.");
    }
}

void TradeBot::gotoNextTimeframe()
{
    std::cout << "Looking for matches." << std::endl;
    logger.write(Logger::INFO, "Looking for matches.");
    for (std::string p : orderBook.getKnownProducts())
    {
        //print&logging
        std::cout << "Matching " << p << std::endl;
        logger.write(Logger::INFO, "Matching: " + p);

        //find sales
        std::vector<OrderBookEntry> sales =  orderBook.matchAsksToBids(p, currentTime, username);

        //print&logging
        std::cout << "Sales: " << sales.size() << std::endl;
        logger.write(Logger::INFO, "Sales:" + std::to_string(sales.size()));
        for (OrderBookEntry& sale : sales)
        {
            std::cout << "Sale price: " << sale.price << " amount " << sale.amount << std::endl; 
            logger.write(Logger::INFO, 
                         "Sale price: " + 
                         std::to_string(sale.price) + 
                         " amount " + 
                         std::to_string(sale.amount));
            if (sale.username == username)
            {
                // update the wallet
                wallet.processSale(sale);
            }
        }
    }

    std::cout << "Advancing to next time frame." << std::endl;
    logger.write(Logger::INFO, "Advancing to next time frame.");

    currentTime = orderBook.getNextTime(currentTime);
    
    logger.write(Logger::INFO, logger.formatCurrentTime(currentTime));
    logger.write(Logger::INFO, 
                 "Wallet at " + currentTime + ": " + "\n" + 
                 logger.spaceAfterINFOLine + wallet.toString("\t")
                 );
}