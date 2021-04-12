#include "Stocks.h"
#include <cstring> 
#include <cstd>
#include <cstdio> 
#include <iomanip> 
#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>

using namespace std; 
Market::Market{
	Wcheck = false; 
	Lcheck = false; 
}; 
void Market::sync (){
	fstream winners, losers; 
	string tmp; 

	int i = 0; 

	winners.open("data.txt"); 
	losers.open("stocks_dataset.txt"); 

	if (winner.is_open() && losers.is_open()){

		while (getline(winners,tmp)){
			W.push_back(stock());
			winners >> W[i].ticker; 
			winners >> W[i].overnight_percent; 
			winners >> W[i].opening_price; 
			winners >> W[i].closing_price;
			winners >> W[i].high_price; 
			winners >> W[i].low_price; 
			if (W[i].closing_price > W[i].opening_price){				
				W[i].daytrade = (1 - (W[i].closing_price / W[i].opening_price)) * 100; 
			}
			if (W[i].opening_price != W[i].high_price){
					W[i].maxlong = (1 - (W[i].opening_price / W[i].high_price)) * 100; 
			}
			else {
				W[i].maxlong = 0; 
			}
			if (W[i].opening_price != W[i].low_price){
					W[i].maxshort = (1 - (W[i].opening_price / W[i].low_price)) * -100;
			}
			else {
				W[i].maxshort = 0; 
			}		
			i++; 
		}
		while (getline(losers, tmp)){
			L.push_back(stock());
				
			losers >> L[i].ticker; 	
			losers >> L[i].overnight_percent; 
			losers >> L[i].opening_price; 
			losers >> L[i].closing_price; 
			losers >> L[i].high_price; 
			losers >> L[i].low_price; 
			if (L[i].closing_price > L[i].opening_price){				
				L[i].daytrade = (1 - (L[i].closing_price / L[i].opening_price)) * 100; 
			}
			if (L[i].opening_price != L[i].high_price){
				L[i].maxlong = (1 - (L[i].opening_price / L[i].high_price)) * 100; 
			}
			else {
				L[i].maxlong = 0; 
			}		
			if (L[i].opening_price != L[i].low_price){
				L[i].maxshort = (1 - (L[i].opening_price / L[i].low_price)) * -100;
			}
			else {
				L[i].maxshort = 0; 
			}
					
			i++; 
		}
	}
	else{
		
		cerr << "There was a problem in sync() opeinging files\n"; 
		exit(-1); 
	}

	Wcheck = true; 
	Lcheck = true; 
}
void Market::adddata (char *addstatement,char *tick ,char *overnight, char *opening, char *closing, char *high, char *low){
	double input_check; 
	FILE *file; 

	input_check = atod(overnight); 

	if (input_check > 0){

		file = fopen("data.txt", "a"); 

		if (file == NULL){
			cout << "Error: in addata() opening the 'data.txt' file"; 
			exit(-1); 
		}
		else{
			fprintf(file, "%s %s %s %s %s %s\n", tick, overnight, opening, closing, high, low);
		}

	}
	else if (input_check < 0){
		
		file = fopen("stocks_dataset.txt", "a"); 
		
			if (file == NULL){
				cout << "Error: in addata() opening the 'stocks_dataset.txt' file"; 
				exit(-1);
			}
			else{
				fprintf(file, "%s %s %s %s %s %s\n", tick, overnight, opening, closing, high, low);

			}
	}
	else{
		cout << "Error in the import proccess"; 
		exit(-1); 
	}
}
void Market::printdata(){
	if (Wcheck == false || Lcheck == false){
		sync(W, L, Wcheck, Lcheck);
	}
	
	for (int i = 0; i < W.size(); i++){
		cout << "Ticker: " << W[i].ticker << endl; 
		cout << "Overnight Change: " << W[i].overnight_percent * 100 << '%' <<  endl; 
		cout << "Opening Price: $" << W[i].opening_price << endl; 
		cout << "Closing Price: $" << W[i].closing_price << endl; 
		cout << "Low: $" << W[i].low_price << endl; 
		cout << "High: $" << W[i].high_price << endl;
		cout << "Max Long Profits: " << W[i].maxlong << '%' << endl; 
		cout << "Max Whort Profit: " << W[i].maxshort << '%' << endl; 

		cout << "\n\n"; 
		cout << "------------------------------------" << endl;
	}
	for (int j = 0; j < L.size(); j++){
		cout << "Ticker: " << L[j].ticker << endl; 
		cout << "Overnight Change: " << L[j].overnight_percent * 100 << '%' <<  endl; 
		cout << "Opening Price: $" << L[j].opening_price << endl; 
		cout << "Closing Price: $" << L[j].closing_price << endl; 
		cout << "Low: $" << L[j].low_price << endl; 
		cout << "High: $" << L[j].high_price << endl;
		cout << "Max Long Profits: " << L[j].maxlong << '%' << endl; 
		cout << "Max Short Profit: " << L[j].maxshort << '%' << endl; 

		cout << "\n\n"; 
		cout << "------------------------------------" << endl;
	}
} 
void Market::simple (char *threshold){

Market::~Market(){};
}