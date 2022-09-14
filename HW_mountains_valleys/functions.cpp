#include <iostream>
#include "functions.h"

using std::cout, std::endl;

bool is_valid_range(int a, int b) {
	// TODO(student): validate input range
	if (10 <= a && a <= b && b < 10000){
		return true;
	}
	else {
		return false;
	}
}

char classify_mv_range_type(int number) {
	// TODO(student): return 'M' if number has /\/\... pattern,
	// return 'V' if number has \/\/ pattern, and return 'N' otherwise

    int lengthOfNum = 0;
    int currentNum = 0;
	int nextNum = 0;
	int NumCopy = number;

    for (int i = number; i>0; i = i/10){
        if (i > 0){
            lengthOfNum += 1;
        }
	}

	int lengthPlace = 1;
	for (int i = 0; i<(lengthOfNum-1); ++i){
		lengthPlace = lengthPlace*10;
	}

	//Now we are gonna compare the numbers inside

	bool alternating = false;

	bool decreasing = false; //If it increases it will turn to false. If it decreases it will be true. 
	//This should alternate for it to be a mountain or a valley

	for (int i = lengthOfNum; i > 0; --i){
		currentNum = number%10;
		number = number/10;

		if (i == (lengthOfNum - 1)){
			
			if (currentNum == nextNum){
				alternating = false;
				break;
			}

			else if (currentNum > nextNum){
				alternating = true;
				decreasing = true;
			}
			
			else if (currentNum < nextNum){
				alternating = true;
				decreasing = false;
			}
		}

		if (i <= (lengthOfNum-2)){

			if (currentNum == nextNum){
				alternating = false;
				break;
			}

			else if ((currentNum < nextNum && decreasing == false) || (currentNum > nextNum && decreasing == true)){
				alternating = false;
				break;
			}

			else if (currentNum > nextNum && decreasing == false){
				decreasing = true;
				alternating = true;
			}
			else if (currentNum > nextNum && decreasing == true){
				alternating = false;
				break;
			}

			else if (currentNum < nextNum && decreasing == true){
				decreasing = false;
				alternating = true;
			}

		}
		nextNum = currentNum;
	}
	
	if (alternating == true){
		number = NumCopy; //Bring back the original value for number
		int firstNum = number/lengthPlace;
		int secondNum = (number/(lengthPlace/10))-firstNum*10;
		
		if (firstNum > secondNum){
			return 'V';
		}
		if (secondNum > firstNum){
			return 'M';
		}
	}
	return 'N';}

void count_valid_mv_numbers(int a, int b) {
	// TODO(student): count the number of valid mountain ranges and valley
	// ranges in the range [a, b] and print out to console using the format
	// in Requirement 4 of the homework prompt

	int mountainCount = 0;
	int valleyCount = 0;
	int i = 0;

	for (i = a; i <= b ; ++i){
		if (classify_mv_range_type(i) == 'M'){
			mountainCount += 1;
		}
		else if (classify_mv_range_type(i) == 'V'){
			valleyCount += 1;
		}
	}
	cout << "There are "<< mountainCount << " mountain ranges and " << valleyCount <<" valley ranges between " << a << " and "<< b << "." << endl;

}

/*Compile stuff
cd hw_mountains_valleys

ls

mountains_valleys.cpp  functions.cpp  functions.h  

g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ mountains_valleys.cpp  functions.cpp

*/
