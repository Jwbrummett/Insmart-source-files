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
	float daytrade, maxlong, maxshort; 
}; 


int main (){
	fstream f, w; 
	vector<stock> S;
	vector<stock> L;  
	string command = ""; 
	
	
	cout << "Welcome to Investats this terminal Is where you can acces all your investment data. "<< endl; 
	
	while (command != "q" || command != "Q"){
		cout << "User/new$/mainscreen "; 
		getline(cin, command, '\n');

		
		if (command == "sync -l"){
			f.open("stocks_dataset.txt"); 
			 
		
			string tmp;
			int linenum = 0; 
			 
			 
			while (getline(f, tmp)){
				
				S.push_back(stock());
				f >> S[linenum].ticker; 
				cout << S[linenum].ticker << " "; 

				f >> tmp; 
				cout << tmp << " ";
				
				f >> tmp; 
				cout << tmp << " ";
				
				f >> tmp; 
				cout << tmp << " ";
				
				f >> tmp; 
				cout << tmp << " "; 
				
				f >> tmp; 
				cout << tmp << " \n"; 
				
				S[linenum].daytrade = 1 - (S[linenum].opening_price / S[linenum].closing_price); 
				
				S[linenum].maxlong = 1 - (S[linenum].opening_price / S[linenum].high_price); 
				
				
				linenum++;  
	
			}
		}
		else if (command == "sync -w"){
			string tmp; 
			int linenum = 0;
			w.open ("data.txt");
			
			while (getline(w, tmp)){
				L.push_back(stock());
				w >> L[linenum].ticker; 
				 
				
				w >> tmp; 
				L[linenum].overnight_percent = stof(tmp); 
				
				w >> tmp; 
				L[linenum].opening_price = stof(tmp);
				
				w >> tmp; 
				L[linenum].closing_price = stof(tmp);
				
				w >> tmp; 
				L[linenum].high_price = stof(tmp); 
				
				w >> tmp; 
				L[linenum].low_price = stof(tmp); 
				
				L[linenum].daytrade = 1 - (L[linenum].opening_price / L[linenum].closing_price); 
				
				L[linenum].maxlong = 1 - (L[linenum].opening_price / L[linenum].high_price);
				
				
				linenum++;  
				
			} 
		}
		// add the statistics to the dataset
			
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
		else if (command == "q" || command == "Q"){
			break; 
		}
	
	// create a menue for us to select our features. 
	
	
	
	}
	
	return 0; 
}

