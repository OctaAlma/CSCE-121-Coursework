/******************************************************************************

File: main.cpp
Author: Prof. Lupoli & Andrew Nemec
Date: 2/16/2021
Section: 
E-mail: slupoli@tamu.edu
Description:
This file contains C++  code that will simulate data collected from a track 
event with 9 lanes. The code will sort the order, then display the results

Updates
Author: J. Michael Moore & Paul Taele

Data File Information
name: data.csv
content: The csv file will contain data in the constant form of:
<Time (double)> <Abbreviated Country (String)> <Uniform number (int)> <Lastname (String)>
32.7 USA 12 Moore
36.5 RUS 35 Polsley
45.8 ENG 73 Teale
52.34 CHN 14 Nemec
76.45 ITY 23 Lupoli     

*******************************************************************************/

/*
g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ *.cpp
*/

#include <iostream>
#include "parallel_tracks.h"
#include <fstream>

using std::cin; using std::cout; using std::endl;
using std::string; using std::getline; using std::ifstream;
using std::invalid_argument; using std::domain_error;

int main()
{
    // TODO: create arrays needed
    double runnerTime[9] = {};
    string countryName[9] = {};
    unsigned int jerseyNumber[9] = {};
    string lastNames[9] = {};
    unsigned int rankArray[9] = {};
	
    // TODO: prep all arrays
    prep_double_array(runnerTime);
    prep_string_array(countryName);
    prep_unsigned_int_array(jerseyNumber);
    prep_string_array(lastNames);
    prep_unsigned_int_array(rankArray);
	
    // TODO: prompt until both the file and the contained data are valid
    
    bool x = false;
    while (!x){
        try{
            string nameOfFile;
            cout << "Enter file name: ";
            cin >> nameOfFile;
            const string fileName = nameOfFile;
            get_runner_data(fileName, runnerTime, countryName, jerseyNumber, lastNames);
            x = true;
        }
        catch(std::domain_error& ex){
            cout << ("Invalid File: ") << ex.what() << endl;
            x = false;
        }
        catch(std::invalid_argument& ex){
            cout << ("Invalid File: ") << ex.what() << endl;
            x = false;
        }
    }

    // TODO: determine ranking, notice the rank array receives the results
    get_ranking(runnerTime, rankArray);

    print_results(runnerTime, countryName, lastNames, rankArray);

    // TODO: Output results

    return 0;
}