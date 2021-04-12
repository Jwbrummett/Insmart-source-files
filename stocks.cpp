#include "Stocks.h"
#include <cstring> 
#include <fstream> 
#include <iomanip> 
#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>

using namespace std; 

void sync (vector<stock>& S, string filename, int& i, bool& check){
	if (check == false) {
		cout << "Data Added Successfully\n\n"; 

	fstream f; 
	f.open(filename);  	 
		
	string tmp;
	i = 0; 			 
			 
	while (getline(f, tmp)){
				
		S.push_back(stock());
				
		f >> S[i].ticker; 
				
		f >> S[i].overnight_percent; 
				
		f >> S[i].opening_price; 
				
		f >> S[i].closing_price; 
				
		f>> S[i].high_price; 
				
		f >> S[i].low_price; 
				
		if (S[i].closing_price > S[i].opening_price){				
			S[i].daytrade = (1 - (S[i].closing_price / S[i].opening_price)) * 100; 
		}


		if (S[i].opening_price != S[i].high_price){
					S[i].maxlong = (1 - (S[i].opening_price / S[i].high_price)) * 100; 
		}

		else {
			S[i].maxlong = 0; 
		}
				
		if (S[i].opening_price != S[i].low_price){
					S[i].maxshort = (1 - (S[i].opening_price / S[i].low_price)) * -100;
		}

		else {
			S[i].maxshort = 0; 
		}
				
		i++; 
	
			}
	check = true; 
	}}
void addlosers (string); 
void addwinners (string);
void printdata(vector<stock>& S, bool& check, string filename, int &i){
	if (check == false){
		sync(S, filename, i, check); 

		for (size_t i = 0; i < S.size(); i++){
		cout << "Ticker: " << S[i].ticker << endl; 
		cout << "Overnight Change: " << S[i].overnight_percent * 100 << '%' <<  endl; 
		cout << "Opening Price: $" << S[i].opening_price << endl; 
		cout << "Closing Price: $" << S[i].closing_price << endl; 
		cout << "Low: $" << S[i].low_price << endl; 
		cout << "High: $" << S[i].high_price << endl;
		cout << "Max Long Profits: " << S[i].maxlong << '%' << endl; 
		cout << "Max Short Profit: " << S[i].maxshort << '%' << endl; 

		cout << "\n\n"; 
		cout << "------------------------------------" << endl;

		}
	}
	else if (check == true) {
		for (size_t i = 0; i < S.size(); i++){
		cout << "Ticker: " << S[i].ticker << endl; 
		cout << "Overnight Change: " << S[i].overnight_percent * 100 << '%' <<  endl; 
		cout << "Opening Price: $" << S[i].opening_price << endl; 
		cout << "Closing Price: $" << S[i].closing_price << endl; 
		cout << "Low: $" << S[i].low_price << endl; 
		cout << "High: $" << S[i].high_price << endl;
		cout << "Max Long Profits: " << S[i].maxlong << '%' << endl; 
		cout << "Max Short Profit: " << S[i].maxshort << '%' << endl; 

		cout << "\n\n"; 
		cout << "------------------------------------" << endl;

		}
	}
	
 }
void simple (vector<stock>& S, bool& checkpos, bool& checkneg, string filename){
	long double lpercent = 0, spercent = 0, ppercent = 0; 
	float lost_long = 0, lost_short = 0, both_lost = 0, both_hit = 0 , profit_long_count = 0, profit_short_count = 0, three_long = 0, three_short = 0; 
	int i = 0; 

	while (checkpos == false && checkneg == false){
		sync(S, checkpos, )
	}
	i = 0; 
	for(i = 0; i < S.size(); i++){
		lpercent = lpercent + S[i].maxlong; 
		spercent = spercent + S[i].maxshort; 
		ppercent = ppercent + S[i].overnight_percent; 

		if (S[i].maxlong >= 5){
			profit_long_count += 1; 
		} 
		else if (S[i].maxlong >= 3){
			three_long++; 
		}
		else if (S[i].maxlong <= 2){
			lost_long++; 
		}


		if (S[i].maxshort >= 5){
			profit_short_count += 1; 
		}
		else if (S[i].maxshort >= 3){
			three_short++; 
		}
		else if (S[i].maxshort <= 2){
			lost_short++;
		}
	}

	lpercent = lpercent / i; 
	spercent = spercent / i; 
	p_average = ppercent / i; 
	profit_short_count = (profit_short_count / i) * 100; 
	profit_long_count = (profit_long_count / i) * 100; 

	cout << "\nShort profitable(5% threshhold): %" << profit_short_count << "\nShort profitable (3% threshhold): %"<< ((three_short / i) * 100) + profit_short_count;

	cout << "\n\nPercent profitable from long(5% threshhold): %" << profit_long_count <<"\nLong Profitable (3% threshhold): %" << ((three_long / i) * 100) + profit_long_count; 
	
	cout << "\n\nPercent Short Unprofitable: %" << (lost_short / i) * 100 << "\nUnprofitable Long: %" << (lost_long / i) * 100 << "\n\n"; 

	cout <<" \n\nAvg. max long: %" << lpercent << " \nAvg. max short: %" << spercent << "\n\n"; 
}
