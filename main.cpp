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

int main (int argc, char* argv[]){

	Market mainMarket; 

	if (argc < 2){
                cout << "Enter the proper Amount of arguments\n";
		return 1; 
	}
	
	if (strcmp(argv[1], "simple") == 0){
		mainMarket.simple(argv[2], argv[3]); 
	}
	else if (strcmp(argv[1], "add") == 0){
		switch(argc){
			case 2: 
				mainMarket.addBulkData();
				break; 
			default:
				mainMarket.adddata(argv[2], argv[3], argv[4], argv[5], argv[6], argv[7]); 
				break; }
		
	}
	
}
