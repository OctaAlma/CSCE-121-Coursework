#include "MyString.h"
#include <iostream>
using namespace std;

int main(){

    char * charArray = new char[11];
    charArray[0] = 'A';
    charArray[1] = 'B';
    charArray[2] = 'C';
    charArray[3] = 'D';
    charArray[4] = 'E';
    charArray[5] = 'A';
    charArray[6] = 'B';
    charArray[7] = 'C';
    charArray[8] = 'D';
    charArray[9] = 'E';
    charArray[10] = '\0';

    char * charArray1 = new char[5];
    charArray1[0] = 'A';
    charArray1[1] = 'B';
    charArray1[2] = 'C';
    charArray1[3] = 'C';
    charArray1[4] = '\0';

    MyString string1(charArray);
    MyString string2(string1);
    cout << string2 << endl;

    if (string1 == string2){
        cout << "Your == should work" << endl;
    }

    MyString newstr = string1 + string2;

    cout << newstr << endl;

    std::cout << "Printing string1:" << endl;
    std::cout << string1 << "   Size:" << string1.size() << endl << endl;

    cout << "Printing string2:" << endl;
    std::cout << string2 << "   Size:" << string2.size() << endl << endl;

    cout << "Can I find string 2 in string? bigNum = no " << endl;
    cout << string1.find(string2) << endl << endl;

    cout << "Printing string + string2: " << endl;
    //string1 += string2;
    std::cout << string1 << "   Size:" << string1.size() << endl << endl;

    cout << "Can I find string 2 in string? bigNum = no " << endl << string1.find(string2) << endl;

    /*
    cout << "Testing at" << endl;
    for (unsigned i = 0; i < string.size(); i++){
        cout << "string.at(" << i << ") is: " << string.at(i) << endl;
    }*/

    //const char * newCharArray = string.data();
    
    /*cout << "Printing string: " << endl;
    string.Print();

    for (int i = 0; i < 6; i++){
        if (i == 0){
            cout << "Printing newCharArray: " << endl;
        }
        cout << charArray[i];
    }cout << endl;*/

    delete [] charArray;
    delete [] charArray1;
    //delete [] newCharArray;
}