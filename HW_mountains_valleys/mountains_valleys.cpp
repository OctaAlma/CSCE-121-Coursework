#include <iostream>
#include "functions.h"

using std::cout, std::cin, std::endl;

int main() {
	int a = 0;
	int b = 0;
	bool x = false;
	while (x == false){
		// TODO(student): print prompt for input
		cout << "Enter numbers 10 <= a <= b < 10000: ";
	
		// TODO(student): read the numbers from standard input
		cin >> a;
		cin >> b;

		// TODO(student): validate input (and reprompt on invalid input)
		x = is_valid_range (a,b);
		if (x == false){
			cout << "Invalid Input" << endl;
		}
	}

	// TODO(student): compute and display solution
	count_valid_mv_numbers(a, b);

	return 0;
}

