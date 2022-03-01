#include "stockdatatypes.h"


Market::Market(Initilizer &init)
{
	// must set the files == 0 to ensure they are not misread by the program. 
	winFilePath = ""; 
	loseFilePath = ""; 

	// this will check the initilization flags, and populate a command object and return it for use
	// will include the main command, the flags and the values they return.

	checkflags(init);

	Init();
}

bool Market::checkFlags(Initlizer &init){
  // will find the FIRST command thatis available, in the map and search to see what it holds, scan

  std::map::iterator<std::string, bool> it;

  for(it = init.commands.begin(); it != init.commands.end(); it++){

      if(it->second){

          mainCmd = it->first;
          break;

        }

    }

  // if there is no commands, it should not return anything, but a flag to show that it did not work.
  //other wise scan the flags associated with the various amounts for the whole

  if(mainCmd == "")
    return false;
  // this will list out all the commands, and will serve as "Internal documentation" for the Program
  if(mainCmd == "help"){

      //Add any additional commands here

      printf("\n\n Commands:\n\t-thresh: Returns data on a stated threshold. (eg. how many stocks have exceeded 3% long suring a trading day.\n Supports the commands for upper bound, lower bound, period, and ");

      printf("\n\t-add: Opens up the application for you to add stock data in the following format <Ticker, Overnight change, Open Price, Closing Price, High, Low>\n No need to differentiate what type of overnight direction is moved, the parser does it automatically");

      printf("\n\t-avg: Shows average long and short positions for a given period in a subset of the data.");



    }

}

void Market::extractFilePath(){

  //the next block checks the files, and sees if the locations file exsists, if not creates the file.
  struct stat buffer;
  if(stat(Locations.c_str(), &buffer) == -1){

// create the 

      FILE *fp;
      fp = fopen(Locations.c_str(), "w");  // if the file does not exsist it will create one in write mode then close. 
      fclose(fp);

    }

  /*

    2. Read the files into the string variable.
  */
//next block opens the Locations text file and opens it up for reading
  std::fstream locationFile;
  locationFile.open(Locations);
  locationFile >> winFilePath >> loseFilePath;

  /*
      3. If the variables are still blank, they will be told to go to the file, and set the file to the correct file path.
*/
  if(winFilePath == "" && loseFilePath == ""){

      printf("Error! there is no file path set, enter the file paths\nWinning File: ");
      std::cin >> winFilePath;
      printf("Loser Path: ");
      std::cin >> loseFilePath;
    }
}

void Market::Init(){

  // need to get a file path for the winfile and the losefile, so we get it out of our config file. then open the file in this case.
  extractFilePath();
	
  winFile.open(winFilePath);
  loseFile.open(loseFile);

  std::string tmp;
  int i = 0;

  //if the winfile and losefile are open, populate them both, if not return an error reporting sync problems.
  if (winFile.is_open() && loseFile.is_open()){

      //get the winners into the proper data structures. Does do data checks for length
      winners.reserve(200);
      while(getline(winFile, tmp)){
          winners.push_back(Stock());

          winFile >> winners[i].ticker;
          winFile >> winners[i].overnight_percent;
          winFile >> winners[i].opening_price;
          winFile >> winners[i].closing_price;
          winFile >> winners[i].high_price;
          winFile >> winners[i].low_price;
          if (winners[i].closing_price > winners[i].opening_price){
                  winners[i].daytrade = (1 - (winners[i].closing_price / winners[i].opening_price)) * 100;
          }
          if (winners[i].opening_price != winners[i].high_price){
                          winners[i].maxlong = ((winners[i].high_price - winners[i].opening_price) / winners[i].opening_price) * 100;
          }
          else {
                  winners[i].maxlong = 0;
          }
          if (winners[i].opening_price != winners[i].low_price){
                          winners[i].maxshort = ((winners[i].opening_price - winners[i].low_price) / winners[i].opening_price) * -100;
          }
          else {
                  winners[i].maxshort = 0;
          }
          i++;
        }
      i = 0;

      // now put the losers into the data structures, make sure they have validation
      while (getline(loseFile, tmp)){
          losers.push_back(Stock());

          loseFile >> tmp;
          if (tmp.length() <= 6)
             losers[i].ticker;

          loseFile >> losers[i].overnight_percent;
          loseFile >> losers[i].opening_price;
          loseFile >> losers[i].closing_price;
          loseFile >> losers[i].high_price;
          loseFile >> losers[i].low_price;
          if (losers[i].closing_price > losers[i].opening_price){
                  losers[i].daytrade = (1 - (losers[i].closing_price / losers[i].opening_price)) * 100;
          }
          if (losers[i].opening_price != losers[i].high_price){
                  losers[i].maxlong = ((losers[i].high_price - losers[i].opening_price) / losers[i].opening_price) * 100;
          }
          else {
                  losers[i].maxlong = 0;
          }
          if (losers[i].opening_price != losers[i].low_price){
                  losers[i].maxshort = ((losers[i].opening_price - losers[i].low_price) / losers[i].opening_price) * -100;
          }
          else {
                  losers[i].maxshort = 0;
          }

          i++;

        }



    }
  else {
      cout << "Error with importing, poroblem with Sync\n";
      return;
    }


}

void Market::addData(){

  //go on a loop where the promt asks for their line to properly parse the line
  std::cout << "Enter the dataline that you want to place in the file: (QUIT)";

  std::string Ticker = "", ov = "", high = "", low = "", open = "", close = "";

  while(Ticker != "QUIT"){
      FILE *inputFile;

      cin >> Ticker >> ov >> open >> close >> high >> low;

// Ensure a method to quit via the command line for the user.

      if (Ticker == "QUIT"){
          break;
        }

      //This will check to see if the data inputted has a good change of being valid data, not 100 but works really well

      if (Ticker.length() >= 12 || ov.length() >= 12 || open.length() >= 12 || low.length() == 0){

          printf("\n\nError, Data could not be validated");

          break;

        }

      // these checks will be validations of the data themselves, to ensure they fit the designed schema.

      if(atof(open.c_str()) > atof(high.c_str())){

          printf("Validation Error\n\n the high value: %s is not greater then the open price: %s", open.c_str(), high.c_str());
          break;
        }

      if(atof(open.c_str) < atof(low.c_str())){

          printf("Validation Error \n\n the low value of: %s is greater then the open: %s", low.c_str(), open.c_str());

        }

      // scrub the data so it is in an organized and standard format for the document to print to.



      if (ov[0] == "-"){

          if(ov[1] == "."){

              ov.insert(0, 1, '0');

            }

        inputFile = fopen(loseFilePath.c_str(), "a");
        }

      else{
          if (ov[0] == "."){
          // if they do not put the 0 at the start of the percentage values, ensure they are.
              ov.insert(0, 1, '0');

            }
        inputFile = fopen(winFilePath.c_str(), "a");
        }

      fprintf(inputFile, "%s %s %s %s %s %s", Ticker.c_str(), ov.c_str(), open.c_str(), close.c_str(), high.c_str(), low.c_str());

    }

  

}

Initilizer::Initilizer(int &argc, char **argv){ // get the correct commands in the map, and the flags together to pass to the market data type.

  getCommands(argc, argv);

}

void Initilizer::getCommands(int argc, char **argv){

  nums.reserve(5);

  std::vector<std::string> s;
  s.reserve(10);

  for(int i = 1; i < argc; i++){ // gives us alll the commands in a good format to do the find commands

      std::string args(argv[i]);
      s.push_back(args);

    }

  for(int i = 0; i < argc; i++){ // goes through the array of strings and changes the commands and the

  //This parses for the special commands for values in the program, to fill the floats in the initiliazer;


  // This will adjjust the map to include flags and the commands for later use
      std::map<std::string, bool>::iterator it = commands.find(s[i]);


      // goes throught the commands map to see if any of them match
      if (it != commands.end())
          it->second = true;

      //Goes through the flags to see if any are true.
      else {
          std::map<std::string, bool>::iterator fl = flags.find(s[i]);
          if (fl != flags.end())
            fl->second = true;

          // This will add values in thier associated maps for all of the numbered values
          //Values come right after their associated flags in the command line.
          else{
              std::map<std::string, float>::iterator vals = values.find(s[i]);

              if(vals != vlues.end())
                vals->second = s[i + 1];
            }
      }
    }

}

~Market(){}
