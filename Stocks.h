#include <fstream>
#include <cstring> 
#include <cstdlib>
#include <cstdio> 
#include <iomanip> 
#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>
using namespace std; 

struct stock{
	string ticker;  
	double overnight_percent; 
	double opening_price; 
	double closing_price; 
	double high_price; 
	double low_price; 

	double daytrade, maxlong, maxshort; };

class Market{

private:

	vector<stock> W; //list of winners
	vector<stock> L; // list of the losers
	bool Wcheck; // check to see if the winners are full
	bool Lcheck; // checks to see if the losers are full
	vector<stock> Meets_both; 
	vector<stock> Meets_long; 
	vector<stock> Meets_short; 

public:

	Market(); 
	void sync (); 
	void adddata (char* ,char *, char*, char*, char*, char*);
	void simple(char*,char*); 
	void cpyToBoth(struct stock&);
	void cpyToLong(struct stock&); 
	void cpyToShort(struct stock&); 
	void printdata(char *);
	void printsubvector(vector<stock>&); 
	void addBulkData();
	~Market(); 
}; 

 

