#include <iostream>
#include <string>
#include <limits>
#include "./string_calculator.h"

using std::cout, std::endl, std::cin;
using std::string;

//g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ main.cpp  string_calculator.cpp

int main() {
    string input;
    cout << "String Calculator" << endl;
    cout << "\"q\" or \"quit\" or ctrl+d to exit" << endl;

    while ((input != "q") || (input != "quit")){
        cout << ">> ";

        getline(cin, input);

        if (input == "q" || input == "quit"){
            cout << "farvel!\n" << endl;
            break;
        }

        int num1Index = input.find(" ",1);

        string num1 = input.substr(0,num1Index);

        string num2 = input.substr(num1Index + 3, input.size());

        if (input[num1Index+1] == '+'){
            cout<< endl;
            cout << "ans =\n" << endl;
            cout << "    " << add(num1,num2) << endl;
            cout << endl;
        }
        else if (input[num1Index+1] == '*'){
            cout<< endl;
            cout << "ans =\n" << endl;
            cout << "    " << multiply(num1,num2) << endl;
            cout << endl;
        }
    }
}


