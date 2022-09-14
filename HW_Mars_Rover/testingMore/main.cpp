#include "MyString.h"
#include <iostream>

using std::cout, std::endl;

#define EXPECT_EQ(X,Y) if (!(X == Y)) { cout << "[FAIL] ("<<__FUNCTION__<<":"<<__LINE__<<") expected equality of " << #X << " and " << #Y << endl; }
//#define EXPECT_TRUE(X <= Y) if (!(X == Y)) { cout << "[FAIL] ("<<__FUNCTION__<<":"<<__LINE__<<") expected equality of " << #X << " and " << #Y << endl; }


int main(){
  MyString input = "";

  size_t actual_size      = 0;
  size_t actual_length    = 0;
  // size_t actual_capacity  = 1;
  size_t actual_capacity  = 0;
  bool actual_empty       = true;
  char actual_data0       = '\0';

  size_t predicted_size      = input.size();
  size_t predicted_length    = input.length();
  size_t predicted_capacity  = input.capacity();
  bool predicted_empty       = input.empty();
  char predicted_data0       = input.data()[0];
  bool predicted_front       = false;

  EXPECT_EQ(actual_length, predicted_length);
  EXPECT_EQ(actual_size, predicted_size);
  //EXPECT_EQ(actual_capacity, predicted_capacity);
  //EXPECT_TRUE(actual_capacity <= predicted_capacity);
  EXPECT_EQ(actual_empty, predicted_empty);
  EXPECT_EQ(actual_data0, predicted_data0);
}
/*
{
  const char* sequence = new char[6] {'h', 'o', 'w', 'd', 'y', '\0'};
  MyString input = sequence;
  const char* input_data = input.data();
  
  size_t actual_size     = 5;
  size_t actual_length   = 5;
  size_t actual_capacity = 6;
  bool actual_empty      = false;
  char actual_null       = '\0';
  char actual_front      = 'h';
  
  size_t predicted_size      = input.size();
  size_t predicted_length    = input.length();
  size_t predicted_capacity  = input.cap();
  bool predicted_empty       = input.empty();
  char predicted_null        = input.data()[5];
  char predicted_front       = input.front();
  
  EXPECT_EQ(actual_length, predicted_length);
  EXPECT_EQ(actual_size, predicted_size);
  EXPECT_EQ(actual_capacity, predicted_capacity);
  EXPECT_EQ(actual_empty, predicted_empty);
  EXPECT_EQ(actual_null, predicted_null);
  EXPECT_EQ(actual_front, predicted_front);
  
  for (size_t i = 0; i < input.length(); ++i) {
  	char predicted_element = sequence[i];
  	char actual_element_at = input.at(i);
  	char actual_element_data = input_data[i];
  
    EXPECT_EQ(predicted_element, actual_element_at);
    EXPECT_EQ(predicted_element, actual_element_data);
  }
  delete [] sequence;
}
*/