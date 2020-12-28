#include <cstring> 
#include <fstream> 
#include <iomanip> 
#include <iostream> 
#include <vector> 
#include <string>


using namespace std; 
struct stock{
	string ticker;  
	float overnight_percent; 
	float opening_price; 
	float closing_price; 
	float high_price; 
	float low_price; 
	
	// need the calculated values as well (how they did percentage wise etc. )
	float daytrade, maxlong, maxshort; }; 

void sync (vector<stock>&, fstream&, string); 
void add (fstream&, string); 

int main (){
	fstream f, w; 
	vector<stock> S;
	vector<stock> L;  
	string command = ""; 
	string dataline = "User/new$/mainscreen ";
	
	cout << "Welcome to Investats this terminal Is where you can acces all your investment data. "<< endl; 
	
	while (command != "q" || command != "Q"){
		cout << dataline; 
		getline(cin, command, '\n');

		switch (command)
		if (command == "sync -l"){
			sync (S, f, "stocks_dataset.txt");

			cout << endl << "Data of overnight losers added" << endl << endl;
			dataline = dataline + "/loserdata ";
		}
		else if (command == "sync -w"){
			sync (L, w, "data.txt"); 
			
			cout << endl << "Data of overnight winners added" << endl << endl;
			dataline = dataline + "/winnerdata ";  
				 
		}			
		else if (command == "add -l"){
			f.open("stocks_dataset.txt", ios::app); 
			
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
										
					f << tick << " -0."<< over << " " << open << " " << close << " " << max << " "<< min << "\n";  
					
				
				}
			} while (tick != "NULL"); 	
		}
		else if (command == "add -w"){
			{
			w.open("data.txt", ios::app); 
			
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
			} while (tick != "NULL"); 	
	
			
		}
		else if (command == "q" || command == "Q"){
			break; 
		}
	
	// create a menue for us to select our features. 
	
	
	
	}
	
	return 0; 
}

void sync (vector<stock>& S, fstream& f, string filename){
	f.open(filename);  
			 
		
			string tmp;
			int i = 0; 			 
			 
			while (getline(f, tmp)){
				
				S.push_back(stock());
				f >> S[i].ticker; 
				
				f >> S[i].overnight_percent; 
				
				f >> S[i].opening_price; 
				
				f >> S[i].closing_price; 
				
				f>> S[i].high_price; 
				
				f >> S[i].low_price; 
								
				S[i].daytrade = 1 - (S[i].opening_price / S[i].closing_price); 
				
				S[i].maxlong = 1 - (S[i].opening_price / S[i].high_price); 
				
				
				i++;  
				c
	
			}}
void add (fstream&, string); 


