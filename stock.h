#ifndef STOCK_H
#define STOCK_H

struct Stock{ //building block of the whole prgram is this data structure
  std::string ticker;
  double overnight_percent;
  double opening_price;
  doubsle closing_price;
  double high_price;
  double low_price;

  double daytrade, maxlong, maxshort; };

#endif // STOCK_H
