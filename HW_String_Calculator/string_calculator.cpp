#include <iostream>
#include <string>
#include "./string_calculator.h"

using std::cout, std::endl;
using std::string;

unsigned int digit_to_decimal(char digit) {
    // TODO(student): implement
    if (int (digit) < 48 || int (digit) > 57){
        throw std::invalid_argument("This isn't a valid character!");
    }
    return (int(digit)-48);
}

char decimal_to_digit(unsigned int decimal) {
    // TODO(student): implement
    if (decimal > 9){
        throw std::invalid_argument("This is an invalid decimal value!");
    }
    else{
        int digit = decimal + 48;
        digit = char(digit);
        return digit;
    }
    return '0';
}

string trim_leading_zeros(string num) {
    // TODO(student): implement

    bool negative = false;
    if (num[0] == '-'){
        negative = true;
        num.erase(0,1);
    }
    int stringSize = num.size();

    //If they enter a string of 000000. We should return 0
    //The for loop below determines if the string contains only zeroes. If it does, we will return 0
    bool onlyZero = false;
    for (int i = 0; i < stringSize; i++){
        if (num[i]=='0'){
            onlyZero = true;
        }
        else{
            onlyZero = false;
            break;
        }
    }
    if (onlyZero == true){
        return "0";
    }

    int numOfX = 0;
    for (int i = 0; i < stringSize; i++){
        if (num[i] == '0'){
            num.at(i) = 'x';
            numOfX += 1;
        }
        else if (num[i] != '0'){
            break;
        }
    }
    //We have replaced the leading zeroes with x, and we know how many x(s) there are
    //We can run a third for loop and remove all the x(s)
    
    num.erase(0, numOfX);

    if (negative == true){
        num.insert(0,"-");
    }

    return num;
}

string add(string lhs, string rhs) { //DONT TOUCH
    // TODO(student): implement

    bool negative = false;
    //Since the arithmetic will only be between numbers of the same sign, we can just check the sign of 1
    if (lhs[0] == '-'){
        negative = true;
        rhs.erase(0,1);
        lhs.erase(0,1);
    }

    lhs = trim_leading_zeros(lhs);
    rhs = trim_leading_zeros(rhs);

    int sizelhs = lhs.size();
    int sizerhs = rhs.size();
    bool carryOne = false;
    string sum = "";

    //We want to make both strings the same size, 
    //One way to do it is to add leading zeroes to the smaller one
    if (sizelhs > sizerhs){
        int zeroesToAdd = sizelhs-sizerhs;
        for (int i = zeroesToAdd; i > 0; i--){
            rhs.insert(0,"0");
        }
    }

    //We can do the same if rhs has more numbers than lhs:
    else if (sizerhs > sizelhs){
        int zeroesToAdd = sizerhs-sizelhs;
        for (int i = zeroesToAdd; i > 0; i--){
            lhs.insert(0,"0");
        }
    }

    //cout << "rhs is "<< rhs.size() << " numbers long and lhs is " << lhs.size() << "numbers long" << endl;

    int z;
    for (int i = lhs.size()-1; i >= 0; i--){
        unsigned int x = digit_to_decimal(lhs[i]);
        unsigned int y = digit_to_decimal(rhs[i]);

        if (carryOne == true){
            z = x + y + 1;
        }
        else if (carryOne == false){
            z = x + y;
        }

        if (z > 9){
            carryOne = true;
            z = z-10;
        }
        else if (z<=9){
            carryOne = false;
        }

        char zchar = decimal_to_digit(z);
        sum = zchar + sum;

        //When it gets to the last digit, if the addition becomes double digits, we have to make sure the 1 is there
        if (i == 0 && carryOne == true){
            sum = "1" + sum;
        }
    }

    sum = trim_leading_zeros(sum);

    if (negative == true){
        sum = "-" + sum;
    }
    return sum;
}

string multiply(string lhs, string rhs) { //DONT TOUCH
    // TODO(student): implement
    bool lhsNegative = false;
    bool rhsNegative = false;

    if (lhs[0] == '-'){
        lhsNegative = true;
        lhs.erase(0,1);
    }

    if (rhs[0] == '-'){
        rhsNegative = true;
        rhs.erase(0,1);
    }

    //Now that we have removed the negative signs and know whether each variable is positive or negative, 
    //it's computation time.

    int lhsSize = lhs.size();
    int rhsSize = rhs.size();
    
    int remainder = 0;
    int tempProduct = 0; //Will hold one integer, which is the product of two integers in the numbers being multiplied
    char tempProductChar; //Will hold the tempProduct as a character variable
    string tempProductString; //This will hold all the values of tempProductChar that are generated
    string productString = ""; //tempProductString will be added with this after the second for loop finishes

    int iterations = 0;
    string zeroesToAdd = "";

    for (int i = lhsSize-1; i >= 0; i--){
        //This restarts tempProductString because it will be a new multiple
        tempProductString = "";
        zeroesToAdd = string(iterations, '0');
        tempProductString = tempProductString + zeroesToAdd;

        for (int j = rhsSize-1; j>=0; j--){
            unsigned int x = digit_to_decimal(lhs[i]);
            unsigned int y = digit_to_decimal(rhs[j]);

            if (remainder == 0){
                tempProduct = x * y;
            }
            else if (remainder != 0){
                tempProduct = x * y + remainder; 
                remainder = 0;
            }
            if (tempProduct > 9){
                remainder = tempProduct/10;
                tempProduct = tempProduct%10;
            }

            tempProductChar = decimal_to_digit(tempProduct); //Converts the integer into a character type
            tempProductString = tempProductChar + tempProductString; //Appends the character into the beginning of the string

            if ((j==0) && remainder != 0){
                char remainderChar = decimal_to_digit(remainder);
                tempProductString = remainderChar + tempProductString;
            }

            //cout << x << " * " << y << " = " << tempProduct << " with remainder "<< remainder << endl;
            //cout << "the current string is " << tempProductString << endl;
            //cout << "The current remainder is " << remainder << endl << endl;
        }
        remainder = 0;
        string X = productString;
        productString = add(tempProductString, X);
        iterations += 1;
    }
    productString = trim_leading_zeros(productString);
    if (lhsNegative ^ rhsNegative){
        productString.insert(0,"-");
    }

    return productString;
}
