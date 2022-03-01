#ifndef MARKET_H
#define MARKET_H
#include "Stock.h"
#include "averagepercenttotals.h"
#include "stock.h"
#include "thresholdpercentsearches.h"
#include <vector>
#include <string>
#include <list>
#include <iterator>


class Market // stores alll the variabeles we need for this program to run effectvely
{
private:

  std::vector<stock> winners;

  std::vector<stock> losers;

  std::string LocationsFilePath = "stockLocations.conf"; // set in stone until they can show me that it works properly

  std::string winFilePath;

  std::string loseFilePath;

public:
  Market(); 
  
  void Init(); 

  void extractFilePath(); 

  void addData();

  ThresholdPercentSearches threaholdPercentSearch(char*, char*, char*, char*, char*); // will take 3 arguments, being (winners or losers flag, percent threshold wanting(eg 3 = 3%), and recentcy period (default all data) in the files)

  AveragePercentTotals averagePercentTotal(char*, char*, char*, char*); // will take 4 arguments (winners or losers flag, period of application defualt all data, lower bound of premarket price(default 0), upper bound of pre market price (defualt 1000)), will return average drawdown as well


};

#endif // MARKET_H
