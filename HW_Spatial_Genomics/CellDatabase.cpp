#include <iostream>
#include <string>
#include <sstream>
#include "CellDatabase.h"
#include "CellData.h"
#include <fstream>

using std::cout;
using std::string;
using std::fstream;
using std::ofstream;
using std::endl;

// Default constructor/destructor. Modify them if you need to.

/*
To many points
to little points 

*/
CellDatabase::CellDatabase() {}
CellDatabase::~CellDatabase() {}

bool checkValidDouble(std::string doubleString){
    int decimalCount = 0;
    for (size_t i = 0; i < doubleString.size(); i++){
        if (doubleString[i] == '.'){
            decimalCount++;
        }
    }
    if (decimalCount <= 1){
        return true;
    }
    //cout << doubleString << endl;
    return false;
}

void assignStringToDouble(std::string doubleString, double &variable, std::string line, bool &cont){
    // Check if the string is valid at all:
    // Check if it is not numeric and not a '.'
    for (size_t i = 0; i < doubleString.size(); i++){
        if ((doubleString.at(i) < '0' || doubleString.at(i) > '9') && (doubleString.at(i)!='.')){
            cout << "Error, Invalid input: " << line << endl;
            cont = true;
            return;
        }
    }
    std::stringstream stream (doubleString);
    cont = false;
    stream >> variable;
    if (stream.fail()){
        cout << "Error, Invalid input: " << line << endl;
        cont = true;
    }
}

void CellDatabase::loadData(const string& filename) 
{
    // Implement this function
    std::ifstream inputFile;
    inputFile.open(filename);
    
    if (!inputFile.is_open()){
        cout << "Error: Unable to open" << endl;
        return;
    }
    string line;
    int lineNo = 0;

    std::string id;
    int fov;
    double volume;
    double center_x;
    double center_y;
    double min_x;
    double min_y;
    double max_x;
    double max_y;

    string integrityCheck;
    bool cont;

    //char comma;
    
    while(!inputFile.eof()){
        std::getline(inputFile,line); // puts a line from the file into string line
        lineNo++;
        //check if there is any whitespace:

        if (lineNo == 1){ // Line 1 only has headers.
            continue;
        }
        bool hasWhiteSpace = false;
        for (size_t i = 0; i < line.size(); i++){
            if (line.at(i) == ' '){
                hasWhiteSpace = true;
                break;
            }
        }
        if (hasWhiteSpace){
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        // Check if there is anything in the string
        if (line.size() < 1){
            // Maybe we reached the end of file
            if (inputFile.eof()){
                break;
            }
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        
        // Replace all commas with spaces for the sake of string stream:

        // Added this:
        std::string lineCopy = line;
        int commaCounter = 0;
        for (size_t i = 0; i < lineCopy.size(); i++){
            if (lineCopy.at(i) == ','){
                lineCopy.at(i) = ' ';
                commaCounter++;
            }
        }
        if (commaCounter != 8){ // There should be 8 commas on a valid cell.
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }
        //cout << line << endl;
        std::stringstream currLine(lineCopy); //Inserts the line into a string stream
        
        currLine >> id;
        //cout << line << " " << id << endl;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }
        // Check if the characters in id are valid
        for (size_t i = 0; i < id.size(); i++){
            if (id.at(i) < '0' || id.at(i) > '9'){
                cout << "Error, Invalid input: " << line << endl;
                continue;
            }
        }

        currLine >> fov;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }

        currLine >> integrityCheck;
        if (currLine.fail()){ //Instructions say volume has to be positive. Not sure about <0 or <=0
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        if (checkValidDouble(integrityCheck)){
            assignStringToDouble(integrityCheck,volume,line,cont);
            if (cont){continue;}

            if (volume < 0){
                cout << "Error, Invalid input: " << line << endl;
                continue;
            }
        }else{
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        currLine >> integrityCheck;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        if (checkValidDouble(integrityCheck)){
            assignStringToDouble(integrityCheck,center_x,line,cont);
            if (cont){continue;}
        }else{
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        currLine >> integrityCheck;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        if (checkValidDouble(integrityCheck)){
            assignStringToDouble(integrityCheck,center_y,line,cont);
            if (cont){continue;}
        }else{
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        currLine >> integrityCheck;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        if (checkValidDouble(integrityCheck)){
            assignStringToDouble(integrityCheck,min_x,line,cont);
            if (cont){continue;}
        }else{
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        currLine >> integrityCheck;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        if (checkValidDouble(integrityCheck)){
            assignStringToDouble(integrityCheck,max_x,line,cont);
            if (cont){continue;}
        }else{
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        currLine >> integrityCheck;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        if (checkValidDouble(integrityCheck)){
            assignStringToDouble(integrityCheck,min_y,line,cont);
            if (cont){continue;}
        }else{
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        currLine >> integrityCheck;
        if (currLine.fail()){
            cout << "Error, Invalid input: " << line << endl;
            //return;
            continue;
        }
        if (checkValidDouble(integrityCheck)){
            assignStringToDouble(integrityCheck,max_y,line,cont);
            if (cont){continue;}
        }else{
            cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        // Now we can check if there is any remaining error
        string remainder = "";
        getline(currLine,remainder);
        if (!remainder.empty()){
            cout << "Error, Invalid input: " << line << endl;
            continue;
        } 
        //cout << id<<" "<<fov<<" "<<volume<<" "<<center_x<<" "<<center_y<<" "<<min_x<<" "<<max_x<<" "<<min_y<<" "<<max_y << endl;
        records.insert(id,fov,volume,center_x,center_y,min_x,max_x,min_y,max_y);
    }
    inputFile.close();
}

// Do not modify
void CellDatabase::outputData(const string& filename) {
    ofstream dataout("sorted." + filename);

    if (!dataout.is_open()) 
    {
        cout << "Error: Unable to open" << endl;
        exit(1);
    }
    dataout << records.print();
}


// on the perform query, you are NOT supposed to print out anything
// You literally write the line in the output file.
void CellDatabase::performQuery(const string& filename) 
{
    // Implement this function
    std::ifstream inputFile;
    inputFile.open(filename);
    
    if (!inputFile.is_open()){
        cout << "Error: Unable to open" << endl;
        return;
    }

    std::ofstream outputFile;
    outputFile.open("result.data");

    if (!outputFile.is_open()){
        cout << "Error: Unable to open" << endl;
        return;
    }

    int lineCount = 0;
    while (!inputFile.eof()){
        string line;
        getline(inputFile,line);
        lineCount++;

        if (line.size() < 1){
            if (inputFile.eof()){
                break;
            }
            //cout << "Error, Invalid input: " << line << endl;
            continue;
        }

        std::stringstream currLine(line);
        string dataType;
        currLine >> dataType;
        //cout << "datatype: "<<dataType << endl;

        if (dataType == "AVG"){
            int k;
            currLine >> k;
            //cout << k << "|" << endl;
            if (k <= 0){
                outputFile << "Error, Invalid input: " << line << endl;
                continue;
            }
            outputFile << "AVG " << k << ": " << this->records.average(k) << endl;
        }

        else if (dataType == "VAR"){
            int k;
            currLine>> k;
            //cout << k << "|" << endl;
            if (k<=0){
                outputFile << "Error, Invalid input: " << line << endl;
                continue;
            }
            outputFile << "VAR " << k << ": " << this->records.variance(k) << endl;
        }
        
        else if (dataType == "COUNT"){
            int k;
            currLine>> k;
            //cout << k << "|" << endl;
            if (k<=0){
                outputFile << "Error, Invalid input: " << line << endl;
                continue;
            }
            outputFile << "COUNT " << k << ": " << this->records.countN(k) << endl;
        }

        else if (dataType == "OUTLIER"){
            int k, j, N;
            currLine>> k;
            if (currLine.fail()){
                outputFile << "Error, Invalid input: " << line << endl;
                continue;
            }
            currLine >> j;
            if (currLine.fail()){
                outputFile << "Error, Invalid input: " << line << endl;
                continue;
            }
            currLine >> N;
            if (currLine.fail()){
                outputFile << "Error, Invalid input: " << line << endl;
                continue;
            }
            //cout << k << "|" << N << "|" << j <<"|"<< endl;
            if (k<=0 || N<=0){
                outputFile << "Error, Invalid input: " << line << endl;
                continue;
            }
            outputFile << "OUTLIER " << k << " "  << j << " " << N << ": "<< this->records.outliers(k,j,N) << endl;
        }
        else{
            outputFile << "Error, Invalid input: " << line << endl;
        }
    }
    inputFile.close();
    outputFile.close();
}
