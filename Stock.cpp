/************************************************************************
*	Filename:	Stock.cpp												*
*	Author:		Jake Brummett											*
*	Date:		December 25th, 2020										*
*	Purpose:	To define the Stock	class Stock							*
************************************************************************/

//	HEADER FILES
# include <string>
# include "Stock.h"

void Stock::printStock(Stock s) {
	std::cout << "Stock: " << s.ticker << endl
		<< "Overnight Percent: " << s.overnightPercent << endl
		<< "Openibg Price: " << s.openingPrice << endl
		<< "Closing Price: " << s.closingPrice << endl
		<< "High Price: " << s.highPrice << endl
		<< "Low Price: " << s.lowPrice << endl
		<< "Day Trade: " << s.dayTrade << endl
		<< "Max Long: " << s.maxLong << endl
		<< "Max Short: " << maxShort << endl
		<< endl;
}
