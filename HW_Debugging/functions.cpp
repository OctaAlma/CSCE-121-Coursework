#include <iostream>
/*
g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ functions.cpp debugging.cpp 
*/
int Largest(int a, int b, int c) { //DO NOT TOUCH
  int d = a;
  if (d < b) {
    d = b;
  } if (c > d) {
    d = c;
  }
  return d;
}//Fixed

bool SumIsEven(int a, int b) { //DO NOT TOUCH!
  if((a+b)%2 !=0){
    return false;
  }
  else{
    return true;
  }
}//Fixed

int BoxesNeeded(int apples){ //DO NOT TOUCH
  if (apples <= 0){
    return 0;
  }
  double filledBoxes = apples;
  filledBoxes = filledBoxes/20;

  if (filledBoxes <= apples/20){
      return apples/20;
  }
  int x = 1 + (apples/20);
  return x;
}//Fixed

bool SmarterSection(int A_correct, int A_total, int B_corect, int B_total) { //DO NOT TOUCH
  //The main problem with this is that the inputs are integers instead of floats or doubles.
  //I will make a double that is equal to each variable then calculate the % using the double variables
  double aCorrect = A_correct;
  double aTotal = A_total;
  double bCorrect = B_corect;
  double bTotal = B_total;
  //The try-catch should throw invalid_argument if it detects one of the following:
  //The # of students correct is greater than total students for either class
  //The total students are less than or equal to 0
  //Any of the arguments are negative
  if (aCorrect < 0 || aTotal <= 0 || bCorrect < 0 || bTotal <= 0 || aCorrect > aTotal || bCorrect > bTotal){
    throw std::invalid_argument("Invalid Argument");
  }
  return aCorrect/aTotal > bCorrect/bTotal;
}//Fixed (hopefully)

bool GoodDinner(int pizzas, bool is_weekend) { //DO NOT TOUCH
  if (is_weekend == true){
    if (pizzas >= 10) {
      return true;
    }
  }
  else if (is_weekend == false){
    if (pizzas >= 10 && pizzas <= 20) {
      return true;
    }
  }
  return false;
}//Fixed

int SumBetween(int low, int high) { //DO NOT TOUCH IT'S FINISHED!!!!
  #include <cstdint>
  int value = 0;

  if (high < low){
    throw std::invalid_argument("Invalid Argument");
  }

  if (high == low){
    return high;
  }

  if (low != INT32_MIN){ //If low were the minimum integer value, its absolute value would have no positive form
    if(abs(low) == high || -1*high == low){
      return 0;
    }
  }
  
  if (low < 0 && high > 0 && low){
    if (low == INT32_MIN && high == INT32_MAX){
      high = INT32_MIN;
    }
    else if (abs(low) < high){
      low = abs(low)+1;
    }
    else if (abs(low) > high){
      high = -1*high-1;
    }
  }

  if (high == low){
    return high;
  }

  // low = INT32_MIN (-2147483648) and high = INT32_MAX (2147483647)
  for (int i = low; i<=high; i++){
    
    if (low > 0){ //Both bounds are positive
      if (INT32_MAX - i < value){
        throw std::overflow_error ("Sum is too big!");
      }
    }

    if (high < 0){ //Both bounds are negative
      if (INT32_MIN + abs(i) > value){
        throw std::overflow_error ("Sum is too small!");
      }
    }
    if (high == 0){
      if (INT32_MIN + abs(i) > value){
        throw std::overflow_error ("Sum is too small!");
      }
    }

    if (low == 0){
      if (INT32_MAX - i < value){
        throw std::overflow_error ("Sum is too small!");
      }
    }

    value = value+i;
  }
  return value;
}

int Product(int a, int b){
  #include <cstdint>
  #include <iostream>
  //Product should throw std::overflow_error if the product exceeds the maximum/minimum value of int.
  if (a==0 || b==0){
    return 0;
  }

  //try{
  if ((a < 0 && b < 0) || (a > 0 && b > 0)){ //Either of these cases means a*b will be positive
    if (INT32_MAX/abs(a) < abs(b) || INT32_MAX/abs(b) < abs(a)){
      throw std::overflow_error ("Integer Overflow!");
    }
  }

  else if (a < 0 && b > 0){ // a is negative and b is positive
    if (INT32_MIN/b > a){
      throw std::overflow_error ("Integer Overflow!");
    }
  }

  else if (a > 0 && b < 0){ // a is positive and b is negative
    if (INT32_MIN/a > b){
      throw std::overflow_error ("Integer Overflow!");
    }
  }
  //}catch (std::overflow_error){
  //  std::cout << "Integers are too big or small!" << std::endl;
  //}
  return a * b;
}