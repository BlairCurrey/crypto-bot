Compile command used for development:
g++ main.cpp OrderBookEntry.cpp OrderBook.cpp MerkelMain.cpp CSVReader.cpp Wallet.cpp TradeBot.cpp Logger.cpp -o exchange -std=c++11

Configurations:
- Logs to log.txt
- Uses the shorter CSV file for testing purposes. This can be switched by changing the argument in the OrderBook initialization to the larger filename ("20200601.csv") in MerkelMain.h. The larger file takes much longer to run the simulation.

How to use the program:
- Compile and run the program.
- Choose whether to run in manual or bot mode
    - if manual, follow provided prompts
    - if bot, specify the log level you want to write to. Currently there are only DEBUG and INFO messages set to log to file. The level you set will omit every log below that level. For instance, setting the level to INFO will omit all DEBUG messages from the log file
        - the bot will run and you can view the results in the log.txt file located in the program's working directory
