#include "stocks.cpp"
#include <cstring> 
#include <cstd>
#include <cstdio> 
#include <iomanip> 
#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>

struct stock{
	string ticker;  
	double overnight_percent; 
	double opening_price; 
	double closing_price; 
	double high_price; 
	double low_price; 

	double daytrade, maxlong, maxshort; 
};

class Market{

private:

	vector<stock> W; //list of winners
	vector<stock> L; // list of the losers
	bool Wcheck; // check to see if the winners are full
	bool Lcheck; // checks to see if the losers are full

protected:

Market(); 
void sync (vector<stock>&, string, int&, bool&); 
void addlosers (string); 
void addwinners (string);
void printdata(vector<stock>&); 
void simple (vector<stock>&, float&, float&, float&);
~Market(); 
}; 


