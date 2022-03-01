#ifndef STOCKDATATYPES_H
#define STOCKDATATYPES_H
#include <map>
#include <fstream>
#include <string>
#include <string.h>
#include <iostream>
#include <iterator>
#include <vector>
#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>

struct AveragePercentTotals{ // shows the average drawdown/gain of the last X number of stocks

  unsigned long int countofStocks;
  double avgGain;
  double avgDrawDown;
};

struct Stock{ //building block of the whole prgram is this data structure
  std::string ticker;

  double overnight_percent;

  double opening_price;

  double closing_price;

  double high_price;

  double low_price;

  double daytrade, maxlong, maxshort; }; // these are the calculated fields and are therefor put together.

struct ThresholdPercentSearches{ // how many stocks fit the threshhold you are looking at, percentage that fufilla given requirement


  long int numberofFufilled; // number of securites that fill the requirements of the arguments

  long long int countofStocks; // how many stocks are we analysing that fit the other criteria (to get a better idea of percent)

  double percentFufilled; // the percent that fufill the

  double avgDrawdown; // the average drawdown of the stocks that are fufilling the requirments

};

// classes

class Initilizer{

private:

  std::map<std::string, bool> commands {{"-avg", false}, {"-thresh", false}, {"help", false}}; // Will have them linking to the commands of the list, lists them as true.
  // help = will print out a list of commands and their associated
  //thresh =

  std::map<std::string, bool> flags {{"-win", false}, {"-los", false}, {"-shrt", false}, {"-long", false}};
  // win = desegnates the winners datgaset to be wueried, los = losers data set for queries
  // shrt = specifically the shoret side of the trade, long = specifically the long side of the trade

  std::map<std::string, float> values {{"-p", 50},{"-lb", 1}, {"-ub", 10}, {"-t", 2}}; // is the flags associatded with each command, and will ignore unsupported flags.
  // p = period, lb = lower bound of the range (opening price ususally), up = upper bound of the percentage (opening price usually), T = threshold of change on the day.

 public:

  Initilizer(int, char **); // needs to use the char array of args

  void getCommands(int, char **);


};

class Market // stores alll the variabeles we need for this program to run effectvely
{
private:

  std::vector<stock> winners;

  std::vector<stock> losers;

  std::string LocationsFilePath = "stockLocations.conf"; // set in stone until they can show me that it works properly

  std::string winFilePath;

  std::string loseFilePath;

  std::string mainCmd = "";

  std::string mainFlags[2];


public:
  Market(Initilizer &);

  void Init();

  void extractFilePath();

  void addData();

  ThresholdPercentSearches threaholdPercentSearch(Initilizer &); // will take 3 arguments, being (winners or losers flag, percent threshold wanting(eg 3 = 3%), and recentcy period (default all data) in the files)

  AveragePercentTotals averagePercentTotal(Initilizer&); // will take 4 arguments (winners or losers flag, period of application defualt all data, lower bound of premarket price(default 0), upper bound of pre market price (defualt 1000)), will return average drawdown as well

  ~Market();

};

#endif // STOCKDATATYPES_H

