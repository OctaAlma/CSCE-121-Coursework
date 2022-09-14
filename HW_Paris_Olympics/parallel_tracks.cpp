#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "parallel_tracks.h"

using std::string;

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the csv file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, double timeArray[], std::string countryArray[], 
		unsigned int numberArray[], std::string lastnameArray[]) 
{
	std::ifstream inputFile;
	inputFile.open(file);

	if (!inputFile.is_open()){
		throw std::invalid_argument("Cannot open file");
	}
	else{
		for (int i = 0; i < 9; ++i){
			string fullLine;
			std::getline(inputFile,fullLine);
			std::istringstream currLine (fullLine);

			double runTime;
			string country;
			unsigned int jerseyNum;
			string lastName;

			//string.empty() doesnt work because the string will have something, INSTEAD check if the size of the string is less than 1
			if (fullLine.size() < 1){
				throw std::domain_error("File missing data");
			}

			currLine >> runTime; 
			if (currLine.fail()){
				throw std::domain_error("File contains invalid data (time)");
			}
			if (runTime <= 0){
				throw std::domain_error("File contains invalid data (time)");
			}

			currLine >> country;
			if (currLine.fail()){
				throw std::domain_error("File contains invalid data (country)");
			}
			if (country.size() != 3){
				throw std::domain_error("File contains invalid data (country)");
			}
			for (int j = 0; j < 3; j++){
				if (country.at(j) > 90 || country.at(j) < 65){
					throw std::domain_error("File contains invalid data (country)");
				}
			}

			currLine >> jerseyNum;
			if (currLine.fail()){
				throw std::domain_error("File contains invalid data (number)");
			}
			if (jerseyNum > 99){
				throw std::domain_error("File contains invalid data (number)");
			}

			currLine >> lastName;
			if (currLine.fail()){
				throw std::domain_error("File contains invalid data (name)");
			}
			int sizeOfLastName = lastName.size();
			for (int j = 0; j < sizeOfLastName; j++){ //Cannot use lastName.size or it gets angry
				if ( !((lastName[j] == 32) ^ ((lastName[j] >= 65 && lastName[j] <= 90) ^ (lastName[j] >= 97 && lastName[j] <= 122))) ){
					throw std::domain_error("File contains invalid data (name)");
				}
			}
			if (sizeOfLastName <= 1){
				throw std::domain_error("File contains invalid data (name)");
			}

			timeArray[i] = runTime;
			countryArray[i] = country;
			numberArray[i] = jerseyNum;
			lastnameArray[i] = lastName;
		}
	}
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
  for (int i = 0; i<9; i++){
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
	for (int i = 0; i<9; i++){
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
    int sizeOfArray = 9;
    for (int i = 0; i<sizeOfArray; i++){
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
    for (int i = 0; i < 9; ++i){

        unsigned int rank = 1;

        for (int j = 0; j < 9; ++j){
            if (timeArray[i] > timeArray[j]){
                rank = rank+1;
            }
        }
        rankArray[i] = rank;
    }
}



//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very inefficient nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
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