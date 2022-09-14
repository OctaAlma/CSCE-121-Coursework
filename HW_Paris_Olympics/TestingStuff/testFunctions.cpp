#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

/*
g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ testFunctions.cpp
*/

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the csv file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
  	//TODO
    ifstream inputFile;
    inputFile.open(file);

    int iterations = 0;

    while (!inputFile.eof()){
        string fullLine;
        getline(inputFile, fullLine);
        
        if (fullLine.find(' ') != string::npos){
            int timeIndex = fullLine.find(' ');
            //stod converts string to double
            double runTime = stod(fullLine.substr(0,timeIndex));
            //We can now remove the time from the string
            fullLine = fullLine.substr(timeIndex+1, fullLine.size()-1);

            timeArray[iterations] = runTime;
        }

        if (fullLine.find(' ') != string::npos){
            int countryIndex = fullLine.find(' ');
            string countryName = fullLine.substr(0,countryIndex);
            fullLine = fullLine.substr(countryIndex+1, fullLine.size()-1);
            countryArray[iterations] = countryName;
            //cout << "For line " << iterations+1 << " we get country = " << countryArray[iterations] << endl;
        }

        if (fullLine.find(' ') != string::npos){
            int numberIndex = fullLine.find(' ');
            unsigned int jerseyNum = stoul(fullLine.substr(0,numberIndex));
            fullLine = fullLine.substr(numberIndex+1, fullLine.size()-1);
            numberArray[iterations] = jerseyNum;
            //cout << "For line " << iterations+1 << " we get jerseyNum = " << numberArray[iterations] << endl;
        }

        lastnameArray[iterations] = fullLine;
        //cout << "For line " << iterations+1 << " we get Last name " << lastnameArray[iterations] << endl;
        
        iterations ++;

        //If the iterations have reached a number that is greater 
        //than that of an arbitrary chosen argument array, we can break it 
        int sizeOfAllArrays = sizeof(numberArray) + 1;
        if (iterations == sizeOfAllArrays){
            break;
        }
    }

    inputFile.close();
	
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_double_array(double ary[])
// making sure all values within the array are set to 0.0;
{
  //TODO
  int sizeOfArray = sizeof(ary);
  for (int i = 0; i<=sizeOfArray; i++){
      ary[i] = 0.0;
  }
}

//-------------------------------------------------------
// Name: prep_double_array
// PreCondition:  a double arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int ary[])
// making sure all values within the array are set to 0;
{
	//TODO
    int sizeOfArray = sizeof(ary);
    for (int i = 0; i<=sizeOfArray; i++){
      ary[i] = 0;
  }
}

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string ary[])
// making sure all values within the array are set to "N/A";
{
    //TODO
    int sizeOfArray = sizeof(ary);
    for (int i = 0; i<=sizeOfArray; i++){
        ary[i] = "N/A";
    }
}

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very inefficient nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const double timeArray[], unsigned int rankArray[])
{
    prep_unsigned_int_array(rankArray);

    unsigned int placements[sizeof(timeArray)+1];
    prep_unsigned_int_array(rankArray);

    for (int i = 0; i < sizeof(timeArray) + 1; ++i){

        unsigned int rank = 1;

        for (int j = 0; j < sizeof(timeArray) + 1; ++j){
            if (timeArray[i] > timeArray[j]){
                rank = rank+1;
            }
        }
        rankArray[i] = rank;
    }
}

void print_results(const double timeArray[], const std::string countryArray[],
		const std::string lastnameArray[], const unsigned int rankArray[])
{

	std::cout << "Final results!!";
	std::cout << std::setprecision(2) << std::showpoint << std::fixed << std::endl;
	double best_time = 0.0;
		
	// print the results, based on rank, but measure the time difference_type
	for(unsigned int j = 1; j <= SIZE; j++)
	{
		
		// go thru each array, find who places in "i" spot
		for(unsigned int i = 0; i < SIZE; i++)
		{
			if(rankArray[i] == 1) // has to be a better way, but need the starting time
			{
				best_time = timeArray[i];
			}
			
			
			if(rankArray[i] == j) // then display this person's data
			{
				// this needs precision display
				std::cout << "[" << j << "]  " << timeArray[i] << " " << std::setw(15) << std::left << lastnameArray[i] << "\t" << "(" << countryArray[i] << ")  +" << (timeArray[i] - best_time) << std::endl; 
			}
			
		}
	}	
}

std::string trim(const std::string word) {
	string ret = word;

	// remove whitespace from the beginning
	while (!ret.empty() && isspace(ret.at(0))) {
			ret.erase(0, 1);
		}

	// remove whitespace from the end
	//  Note: last index is (.size() - 1) due to 0 based indexing
	while (!ret.empty() && isspace(ret.at(ret.size()-1))) {
		ret.erase(ret.size()-1, 1);
	}
	
	return ret;
}

int main()
{
    // TODO: create arrays needed
    double runnerTime[9] = {};
    string countryName[9] = {};
    unsigned int jerseyNumber[9] = {};
    string lastNames[9] = {};

    //File opening stuff
    const string fileName = "good_data01.txt";

    ifstream inputFile;
    inputFile.open(fileName);
    if (!inputFile.is_open()){ //Checks if file open, if it isn't returns 1
        cout << "Could not open file good_data01.txt";
        return 1;
    }
    inputFile.close();
	
    // TODO: prep all arrays
    prep_double_array(runnerTime);
    prep_string_array(countryName);
    prep_unsigned_int_array(jerseyNumber);
    prep_string_array(lastNames);

    // TODO: prompt until both the file and the contained data are valid
    get_runner_data(fileName, runnerTime, countryName, jerseyNumber, lastNames);

    unsigned int rank[9] = {};
    get_ranking(runnerTime, rank);
	
    // TODO: determine ranking, notice the rank array receives the results

    // TODO: Output results

    return 0;
}