/*
 * This file is the data structure for the average percent totals data type.
 * Which will be returned from a function containing information about the dataset, including average drawdown and gain.
 *
 * CountofStocks is used to see how many stocks were used in the calculation, and to use for the final averaging number. s
*/
#ifndef AVERAGEPERCENTTOTALS_H
#define AVERAGEPERCENTTOTALS_H

struct AveragePercentTotals{ // shows the average drawdown/gain of the last X number of stocks

  unsigned long int countofStocks;
  double avgGain;
  double avgDrawDown;
};
#endif // AVERAGEPERCENTTOTALS_H
