### Acknowledgements
This bot is an extension of the Merkel Exchange, which was developed by the University of London and is included here. The Merkel Exchange is a simulated crypto currency marketplace that utilizes order data from a real exchange (see the included csv file). The Merkel Exchange consists of the MerkelMain, OrderBook, OrderBookEntry, Wallet, and CSVReader cpp and header files. Of these, I have extended MerkelMain, OrderBook, OrderBookEntry, and Wallet for compatability and functionality with my the TradeBot and Wallet classes, which I have developed myself.

### How to use the program:
- Compile and run the program.
- In the console, choose whether to run in manual or bot mode
    - if manual, follow provided prompts
    - if bot, specify the log level you want to write to. Currently there are only DEBUG and INFO messages set to log to file. The level you set will omit every log below that level. For instance, setting the level to INFO will omit all DEBUG messages from the log file
        - the bot will run and you can view the results in the log.txt file located in the program's working directory