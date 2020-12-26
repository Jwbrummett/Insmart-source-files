/************************************************************************
*	Filename:	Stock.h													*
*	Author:		Jake Brummett											*
*	Date:		December 25th, 2020										*
*	Purpose:	To declare the Stock class 								*
************************************************************************/
# ifndef STOCK_H
# define STOCK_H

//	HEADER FILES
# include <string>
# include <iostream>

class Stock{
public:
	//	CONSTRUCTORS AND DESTRUCTOR	
	Stock() {}
	Stock(string tick) {ticker = tick;}


	void printStock(Stock s);
private:
	string ticker = "ZZZZ";  
	float overnightPercent= 0;
	float openingPrice = 0;
	float closingPrice = 0; 
	float highPrice = 0;
	float lowPrice = 0;
	float dayTrade = 0;
	float maxLong = 0;
	float maxShort = 0;
};

# endif