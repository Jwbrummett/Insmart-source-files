#include <cstring> 
#include <fstream> 
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
void sync (vector<stock>&, string, int&); 
void addlosers (string); 
void addwinners (string);
void printdata(vector<stock>&); 
void simple (vector<stock>&, float&, float&, float&); 
void standard_dev(vector<stock>&, float&, float&, int&, float&, float&, float&); 

int main (){ 
	vector<stock> S;
	vector<stock> L;  
	string command = ""; 
	string dataline = "User/new$/mainscreen ";
	bool importwin = false, importloss = false;

	float wlong_avg = 0, wshort_avg = 0, llong_avg = 0, lshort_avg = 0; // the average of max longs and max shorts for each scenario. 


	float lp_avg = 0, wp_avg = 0; //the averages for the overnight changes, l loser changes, and w for winner changes


	int lcount = 0, wcount = 0; // Counts for the various datasets, the l is long count and w is loser count. 
	


	cout << "Welcome to Investats this terminal Is where you can acces all your investment data. "<< endl; 
	
	while (command != "q" || command != "Q"){
		cout << dataline; 
		getline(cin, command, '\n');
			
			if (command == "sync -l"){
				switch (importloss){
					case 0: {
						sync(S, "stocks_dataset.txt", lcount);

						cout << endl << "Data of overnight losers added" << endl << endl;
						dataline = dataline + "/loserdata ";
						importloss = true; 
						break; 
					}
					case 1: {
						cout << "\nThe data has already been imported\n"; 
						break; 
					}
				}	 
			}
			
			else if( command == "sync -w"){
				switch (importwin){
					case 0: {
						sync(L, "data.txt", wcount); 
						
						cout << endl << "Data of overnight winners added" << endl << endl;
						dataline = dataline + "/winnerdata "; 
						importwin = true; 
						break; 
					}
					case 1: {
						cout << "\nThe data has already been imported\n"; 
						break; 
					}
				}	
			}

			else if (command == "add -l") {
				addlosers("stocks_dataset.txt"); 
			}

			else if (command == "add -w") {
				addwinners("data.txt"); 
			}

			else if (command == "print -w") {
				switch (importwin){
					case 0: {
						cout << "\n error no winner data found, try the 'sync -w' command\n"; 
						break; 
					}
					case 1: {
						printdata(L);
						break; 
					}
				}	 
			}

			else if (command == "print -l"){
				switch (importloss){
					case 0: {
						cout << "\n error no loser data found, try the 'sync -l' command\n"; 
						break; 
					}
					case 1: {
						printdata(S);
						break; 
					}
				} 
			}

			else if (command == "simple -l") {
				switch (importloss){
					case 0: {
						cout << "\n error no winner data found, try the 'sync -w' command\n"; 
						break; 
					}
					case 1: {
						simple(S, llong_avg, lshort_avg, lp_avg);
						break; 
					}
				}	 
			}

			else if (command == "simple -w") {
				switch (importwin){
					case 0: {
						cout << "\n error no winner data found, try the 'sync -w' command\n"; 
						break; 
					}
					case 1: {
						simple(L, wlong_avg, wshort_avg, wp_avg);
						break; 
					}
				}	 
			}
			else if (command == "corr -w"){
				standard_dev(L, wlong_avg, wshort_avg, wcount, wlong_std, wshort_std, wp_avg); 
			}
			else if (command == "corr -l"){

			}

			else if (command == "q"|| command == "Q") {
				break; 
			}
	

	}
	return 0; 
}
		

void sync (vector<stock>& S, string filename, int& i){
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
}
void addlosers (string filename){
	fstream f; 
	f.open(filename, ios::app); 
			
	string tick, over, open, close, max, min;
	cout << endl<< endl; 
	cout << "\t \t Add new stock to dataset" << endl; 
	cout << endl; 
	do {
		cout << "Ticker: "; 
		cin >> tick; 
				
		if (tick != "NULL"){
					 
			cout << "Overnight Change: "; 
			cin >> over; 
			cout << endl; 

					
			cout << "Opening Price: "; 
			cin >> open; 
			cout << endl; 
					
			cout << "Closing Price: ";
			cin >> close; 
			cout << endl; 
										
			cout << "Daily High: "; 
			cin >> max; 
			cout << endl; 
					
			cout << "Daily Low: "; 
			cin >> min; 
			cout << endl; 
										
			f  << "\n" << tick << " -0."<< over << " " << open << " " << close << " " << max << " "<< min;  
		}
	} while (tick != "NULL"); 	}
void addwinners (string filename){
	fstream w; 
	w.open(filename, ios::app); 
	
	string tick, over, open, close, max, min;
	cout << endl<< endl; 
	cout << "\t \t Add new stock to dataset" << endl; 
	cout << endl; 
	do {
		cout << "Ticker: "; 
		cin >> tick; 
		
		if (tick != "NULL"){
			 
			cout << "Overnight Change: "; 
			cin >> over; 
			cout << endl; 

			
			cout << "Opening Price: "; 
			cin >> open; 
			cout << endl; 
			
			cout << "Closing Price: ";
			cin >> close; 
			cout << endl; 
								
			cout << "Daily High: "; 
			cin >> max; 
			cout << endl; 
			
			cout << "Daily Low: "; 
			cin >> min; 
			cout << endl; 
								
			w << tick << " "<< over << " " << open << " " << close << " " << max << " "<< min << "\n";  
			
		
		}
	} while (tick != "NULL");}
void printdata(vector<stock>& S){
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
void simple(vector<stock>& S, float& long_avg, float& short_avg, float& p_average) // simple overarching statistics of the entire dataset
{
	long double lpercent = 0, spercent = 0, ppercent = 0; 
	float lost_long = 0, lost_short = 0, both_lost = 0, both_hit = 0 , profit_long_count = 0, profit_short_count = 0, three_long = 0, three_short = 0; 
	int i = 0; 
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
	cout << i; 
	lpercent = lpercent / i; 
	long_avg = lpercent; 
	spercent = spercent / i; 
	short_avg = spercent; 
	p_average = ppercent / i; 
	profit_short_count = (profit_short_count / i) * 100; 
	profit_long_count = (profit_long_count / i) * 100; 

	cout << "\nShort profitable(5% threshhold): %" << profit_short_count << "\nShort profitable (3% threshhold): %"<< ((three_short / i) * 100) + profit_short_count;

	cout << "\n\nPercent profitable from long(5% threshhold): %" << profit_long_count <<"\nLong Profitable (3% threshhold): %" << ((three_long / i) * 100) + profit_long_count; 
	
	cout << "\n\nPercent Short Unprofitable: %" << (lost_short / i) * 100 << "\nUnprofitable Long: %" << (lost_long / i) * 100 << "\n\n"; 

	cout <<" \n\nAvg. max long: %" << lpercent << " \nAvg. max short: %" << spercent << "\n\n"; 
}
void search(vector<stock>& S, string &d){
	string CommandString; 
	float SearchOvernight, SearchPrice;
	vector<Stock> matches; 
	short int nextquintet = 5; 


	cout << d << "/search "; 
	cin.get(CommandString,8,';'); 

	if (CommandString == "gsearch" || CommandString == "Gsearch"){
		cout << d << "/search/GeneralSearch "; 
		cin >> SearchOvernight >> SearchPrice; 

		for (int i = 0; i < S.size();){
			if (S[i].overnight_percent <= SearchOvernight + 0.4 && S[i].overnight_percent >= SearchOvernight - 0.4 ){
				// add to a new vector or dynamic array in this case. Copy the whole data point from the struct
				i++; 
				nextquintet--;
			}
			else if (S[i].overnight_percent > SearchOvernight + 0.4){
				i++; 
				nextquintet--; 
			}
		}

	}

	else if (CommandString == "ssearch" || CommandString == "Ssearch"){
		cout << d << "/search/StockSearch "; 
	}
}
void stockcopy(struct Stock &from, struct Stock &to){
	// copies all the information from one stock to another
	strcpy(to.ticker, from.ticker);
	to.overnight_percent = from.overnight_percent;
	to.opening_price = from.opening_price; 
	to.maxlong = from.maxlong; 
	to.maxshort = from.maxshort; 
}