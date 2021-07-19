#include "Stocks.h"
#include <cstring> 
#include <fstream>
#include <cstdlib>
#include <cstdio> 
#include <iomanip> 
#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <cmath>
using namespace std;
Market::Market()
{
	Wcheck = false; 
	Lcheck = false; 
}; 

void Market::sync()
{
	fstream winners, losers; 
	string tmp; 

	int i = 0; 

	winners.open("data.txt"); 
	losers.open("stocks_dataset.txt"); 

	if (winners.is_open() && losers.is_open()){
		
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
					W[i].maxlong = ((W[i].high_price - W[i].opening_price) / W[i].opening_price) * 100; 
			}
			else {
				W[i].maxlong = 0; 
			}
			if (W[i].opening_price != W[i].low_price){
					W[i].maxshort = ((W[i].opening_price - W[i].low_price) / W[i].opening_price) * -100;
			}
			else {
				W[i].maxshort = 0; 
			}		
			i++; 
		}
		
		i = 0; 
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
				L[i].maxlong = ((L[i].high_price - L[i].opening_price) / L[i].opening_price) * 100; 
			}
			else {
				L[i].maxlong = 0; 
			}		
			if (L[i].opening_price != L[i].low_price){
				L[i].maxshort = ((L[i].opening_price - L[i].low_price) / L[i].opening_price) * -100;
			}
			else {
				L[i].maxshort = 0; 
			}
					
			i++; 
		}}
	else{
		
		cerr << "There was a problem in sync() opening files\n"; 
		exit(-1); }

	Wcheck = true; 
	Lcheck = true; 
	cout << "sync Completed"; 
}
void Market::adddata(char *tick ,char *overnight, char *opening, char *closing, char *high, char *low){
	double input_check = atof(overnight); 
	FILE *file; 
	

	if (input_check > 0){

		file = fopen("data.txt", "a"); 

		if (file == NULL){
			cout << "Error: in addata() opening the 'data.txt' file"; 
			exit(-1); 
		}
		else{
			fprintf(file, "\n%s %s %s %s %s %s", tick, overnight, opening, closing, high, low);
			cout << "Data Written Successfully to data.txt\n"; 
		}

	}
	else if (input_check < 0){
		
		file = fopen("stocks_dataset.txt", "a"); 
		
			if (file == NULL){
				cout << "Error: in addata() opening the 'stocks_dataset.txt' file"; 
				exit(-1);
			}
			else{
				fprintf(file, "'\n%s %s %s %s %s %s", tick, overnight, opening, closing, high, low);
				cout << "Data written successfully to stocks_dataset.txt"; 
			}
	}
	else{
		cout << "Error in the import proccess"; 
		exit(-1); 
	}}
void Market::printdata(char *selection)
{

	char sel = selection[0]; 

	if (Wcheck == false || Lcheck == false){
		sync();
	}

	switch(sel){
		case 'w':{
			
			cout << "Ticker\t\tOvernight Change\t\tOpening Price\t\tM.Long\t\tM.short\n"; 
			
			for (int i = 0; i < W.size(); i++){
				cout << W[i].ticker << "\t\t";
				cout << W[i].overnight_percent << "\t\t\t\t"; 
				cout << W[i].opening_price << "\t\t\t"; 
				cout << W[i].maxlong << "\t\t"; 
				cout << W[i].maxshort << "\n"; 
			}

			break; 
		}
		case 'l':{
			cout << "Ticker\t\tOvernight Change\t\tOpening Price\t\tM.Long\t\tM.short\n"; 

			for (int i = 0; i < L.size(); i++){
				cout << L[i].ticker << "\t\t";
				cout << L[i].overnight_percent << "\t\t\t\t"; 
				cout << L[i].opening_price << "\t\t\t"; 
				cout << L[i].maxlong << "\t\t"; 
				cout << L[i].maxshort << "\n"; 
			}

			break;
		}
		case 'a':{
			cout << "Ticker\t\tOvernight Change\t\tOpening Price\t\tM.Long\t\tM.short\n"; 

			for (int i = 0; i < L.size(); i++){
				cout << L[i].ticker << "\t\t";
				cout << L[i].overnight_percent << "\t\t\t\t"; 
				cout << L[i].opening_price << "\t\t\t"; 
				cout << L[i].maxlong << "\t\t"; 
				cout << L[i].maxshort << "\n"; 
			}

			for (int i = 0; i < W.size(); i++){
				cout << W[i].ticker << "\t\t";
				cout << W[i].overnight_percent << "\t\t\t\t"; 
				cout << W[i].opening_price << "\t\t\t"; 
				cout << W[i].maxlong << "\t\t"; 
				cout << W[i].maxshort << "\n"; 
			}


		}
			
	}
}
	
void Market::simple(char* selection ,char *threshold)
{ 

	if (strlen(selection) != 1){
		cout << "Incorrect argument modifier, too many characters, try 'a', 'l' or 'w'.\n"; 
		return; 
	}
	float th = atof(threshold);

	char sel = selection[0]; 

	if (Wcheck == false || Lcheck == false){
		sync(); 
	}


	switch (sel){
		case 'w':{

			long int count;  
			float threshLong = 0, threshShort = 0, both = 0; 

			for (count = 0; count < W.size(); count++){

                            if (W[count].maxlong >= th && W[count].maxshort <= -1 * th){

                                cpyToBoth(W[count]);

                             }

                            if (W[count].maxlong >= th){

                                cpyToLong(W[count]);
		
                            }
                            if (W[count].maxshort <= -1 * th){

                                cpyToShort(W[count]);
		
					}}
			threshLong = (float)Meets_long.size();
			threshShort = (float)Meets_short.size(); 
			both = (float)Meets_both.size();

			cout << "\n Winners data sorted"; 

			cout << "Basic Analysis: \n\n\t threshold =  " << th << "%\n\n";  
			cout << "Long: %" << threshLong / W.size() *100<< "\tncount = " << Meets_long.size() <<"\n"; 
                        cout << "Short: %" << threshShort / W.size()*100<< "\tncount = " << Meets_short.size() <<"\n";
			cout << "Volatile: %" << threshLong / W.size() *100<< "\tncount = " << Meets_both.size() <<"\n";

			char sel2;

			while (sel2 != 'q' || sel2 != 'Q'){
				cout << "Drill Deeper into Data? (l/L, s/S, b/B, q/Q)\n"; 
				cin >> sel2; 

				switch (sel2){

					case 'l':
					case 'L':{
						printsubvector(Meets_long); 
						break;
					}
					case 's':
					case 'S':{
						printsubvector(Meets_short); 
						break; 
					}
					case 'b':
					case 'B':{
						printsubvector(Meets_both); 
						break; 
					}
					case 'q':
					case 'Q':
						break; 
						break; 
					
					default:{
						cout << "Not an appropriate value (enter h/H to seek help\n"; 
						break; 
					}} 
			}
			break; 
		}
		case 'l': {
			vector<stock> Meets_both; 
			vector<stock> Meets_long; 
			vector<stock> Meets_short; 

			long int count;  
			float threshLong = 0, threshShort = 0, both = 0; 

			for (count = 0; count < L.size(); count++){

					if (L[count].maxlong >= th && L[count].maxshort <= -1 * th){

                                                cpyToBoth(L[count]);
					}
					if (L[count].maxlong >= th){

                                                cpyToLong(L[count]);
		
					}
					if (L[count].maxshort <= -1 * th){

                                                cpyToShort(L[count]);
					}}
			threshLong = (float)Meets_long.size();
			threshShort = (float)Meets_short.size(); 
			both = (float)Meets_both.size();

			cout << "\n Winners data sorted"; 

			cout << "Basic Analysis: \n\n\t threshold = " << th << "%\n\n";  
			cout << "Long: %" << threshLong / L.size() << "\n"; 
			cout << "Short: %" << threshShort / L.size() << "\n"; 
			cout << "Volatile: %" << threshLong / L.size() << "\n"; 

			char sel2;

			while (sel2 != 'q' || sel2 != 'Q'){
				cout << "\nDrill Deeper into Data? (l/L, s/S, b/B, q/Q)\n"; 
				cin >> sel2; 				switch (sel2){

					case 'l':
					case 'L':{
						printsubvector(Meets_long); 
						break;
					}
					case 's':
					case 'S':{
						printsubvector(Meets_short); 
						break; 
					}
					case 'b':
					case 'B':{
						printsubvector(Meets_both); 
						break; 
					}
					case 'q':
					case 'Q':
						break; 
					
					default:{
						cout << "Not an appropriate value (enter h/H to seek help\n"; 
						break; 
					}} 
				}
			break;
		} 
		default:
			cout << "Error, incorrect selection criteria, try 'w', 'l' tags with the simple command\n"; 
			break; 

	}
}

void Market::cpyToBoth(struct stock& from)
{
    Meets_both.push_back(stock());
    int i = Meets_both.size() - 1;
    Meets_both[i].ticker = from.ticker;
    Meets_both[i].overnight_percent = from.overnight_percent;
    Meets_both[i].opening_price = from.opening_price;
    Meets_both[i].maxlong = from.maxlong;
    Meets_both[i].maxshort = from.maxshort;
	
}

void Market::cpyToLong(struct stock& from)
{
    Meets_long.push_back(stock());
    int i = Meets_long.size();
    Meets_long[i].ticker = from.ticker;
    Meets_long[i].overnight_percent = from.overnight_percent;
    Meets_long[i].opening_price = from.opening_price;
    Meets_long[i].maxlong = from.maxlong;
    Meets_long[i].maxshort = from.maxshort;

}

void Market::cpyToShort(struct stock& from)
{
    Meets_short.push_back(stock());
    int i = Meets_short.size();
    Meets_short[i].ticker = from.ticker;
    Meets_short[i].overnight_percent = from.overnight_percent;
    Meets_short[i].opening_price = from.opening_price;
    Meets_short[i].maxlong = from.maxlong;
    Meets_short[i].maxshort = from.maxshort;
}

void Market::printsubvector(vector<stock>& printed)
{
	cout << "Ticker\t\tOvernight Change\t\tOpening Price\t\tM.Long\t\tM.short\n";

	for (int i = 0; i < printed.size(); i++){
		cout << printed[i].ticker << "\t\t";
		cout << printed[i].overnight_percent << "\t\t\t\t"; 
		cout << printed[i].opening_price << "\t\t\t"; 
		cout << printed[i].maxlong << "\t\t"; 
		cout << printed[i].maxshort << "\n";
	}
}
void Market::addBulkData()
{
	FILE  *file; 
        string Ticker = "", Ov, Open, Close, High, Low = "";
        short int amount;
        cout << "What amount of stocks would you like to import? ";
        cin >> amount;

        printf("Enter %d Stocks to add to the dataset", amount);

        for (int i = 0; i < amount; i++){
            cin >> Ticker >> Ov >> Open >> Close >> High >> Low;
            if (Low == "" && Ticker != "NULL"){
                cout << "Insifficient Arguments " << Ticker << "Was not added";
            }
				
            else {
                if (Ov[0] == '-'){
                    file = fopen("stocks_dataset.txt", "a");
                }
                else if (Ov[0] == '0'){
                    file = fopen("data.txt", "a");
                }
                else {
                    cout << "Error, failure in argument parse (error in identifying file)\n";
                }

                fprintf(file, "\n%s %s %s %s %s %s", Ticker.c_str(), Ov.c_str(), Open.c_str(), Close.c_str(), High.c_str(), Low.c_str());
                cout << "Successfully added stock, Ticker:" << Ticker << endl;
            }
        }
}
Market::~Market(){};

