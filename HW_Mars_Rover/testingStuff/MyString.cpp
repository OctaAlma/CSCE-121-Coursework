// TODO: Implement this source file
#include "MyString.h"
#include <iostream>

//using namespace std;

MyString::MyString():Capacity(1),size_string(0),string(new char[1]{'\0'}){
    /*this->string = new char[1];
    this->string[0] = '\0';
    this->Capacity = 1;*/
}

MyString::MyString(const MyString& str):Capacity(0),size_string(0),string(new char[str.Capacity]){
    for (int i = 0; i < str.Capacity; i++){
        this->string[i] = str.string[i];
    }

    this->Capacity = str.Capacity;
    this->size_string = str.size_string;
}

MyString::MyString(const char* s):Capacity(1),size_string(0),string(new char[1]){
    int length = 0;

    while (s[length] != '\0'){
        length++;
    }
    // We assigned starting values to Capacity and string so c++ could stop complaining
    // We can get rid of them now 
    if (this->Capacity != 0){
        delete [] this->string;
        Capacity = 0;
    }

    this->string = new char[length + 1];

    for (int i = 0; i < length + 1; i++){
        string[i] = s[i];
    }

    Capacity = length + 1;
    this->size_string = length;
}

MyString::~MyString(){
    delete [] this->string;
    this->string = nullptr;
    this->size_string = 0;
    this->Capacity = 0;
}

void MyString::resize (size_t n){
    if (n == this->size()){
        return;
    }else if (n > this->size()){
        char * newString = new char[n+1];
        for (size_t i = 0; i < n+1; i++){
            if (i < this->size()){
                newString[i] = this->string[i];
            }
            if (i >= this->size()){
                newString[i] = '\0';
            }
        }

        delete [] this->string;
        this->string = newString;
        this->Capacity = n + 1;
        this->size_string = n;
    }
}

size_t MyString::size() const noexcept{
    return this->size_string;
}

size_t MyString::length() const noexcept{
    return this->size_string;
}

const char * MyString::data() const noexcept{
    // this method returns a pointer to THE character array
    // that is composed of the values of the cstring it is called on
    return this->string;
}

bool MyString::empty() const noexcept{
    if (size_string == 0){
        return true;
    }
    return false;
}

const char& MyString::at (size_t pos) const{
    // I AM COMMENTING THIS OUT, IF IT BREAKS IT UNCOMMENT IT
    /*if (pos < 0){
        throw std::out_of_range("");
    }*/
    size_t SizeIn_SizeT = this->size_string;
    if (pos >= SizeIn_SizeT){ // This was an else if before the comment
        throw std::out_of_range("");
    }else{
        return this->string[pos];
    }
}

const char& MyString::front() const{
    return this->string[0];
}

void MyString::clear() noexcept{
    delete [] this->string;
    this->string = new char[1];
    this->string[0] = '\0';
    Capacity = 1;
    size_string = 0;
}

//std::ostream&
//std::ostream& operator<< (std::ostream& os, MyString& str){

MyString& MyString::operator= (const MyString& str){
    delete [] this->string;
    this->string = new char[str.Capacity];
    for (int i = 0; i < str.Capacity; i++){
        this->string[i] = str.string[i];
    }
    this->Capacity = str.Capacity;
    this->size_string = str.size_string;
    return *this;
}

MyString& MyString::operator+= (const MyString& str){
    // Recall that size stores the number of characters before null character
    if (str.empty()){
        return *this;
    }
    if (this->empty()){
        
    }

    int newCapacity = this->size() + str.size() + 1;
    char *combinedString = new char[newCapacity];

    // We copy this's characters to the combined string
    for (size_t i = 0; i < this->size(); i++){
        combinedString[i] = this->string[i];
    }
    
    // Now we copy str into the combined string
    for (size_t i = 0; i < str.size(); i++){
        // The index will start at this->size_string
        combinedString[this->size() + i] = str.string[i];
    }

    // Now we add the \0 at the end
    combinedString[newCapacity-1] = '\0';

    delete [] this->string;
    this->string = new char[newCapacity];

    for (int i = 0; i < newCapacity; i++){
        this->string[i] = combinedString[i];
    }

    this->Capacity = newCapacity;
    this->size_string = newCapacity - 1;
    delete [] combinedString;
    return *this;
}

size_t MyString::find (const MyString& str, size_t pos) const noexcept{
    if (this->size_string - str.size_string < 0){
        return -1;
    }
    size_t maxIndex = this->size_string - str.size_string + 1;
    for (size_t i = pos; i < maxIndex; i++){

        char *substr = new char[str.size_string];
        int JMax = str.size_string + i;
        for (int j = i; j < JMax; j++){
            substr[j-i] = this->string[j];
        }

        bool substrFound = true;
        for (int x = 0; x < str.size_string; x++){
            if (substr[x] != str.string[x]){
                substrFound = false;
                break;
            }
        }
        if (substrFound){
            delete [] substr;
            return i;
        }
        delete [] substr;
    }
    return -1;
}

void MyString::Print(){
    for (int i = 0; i < this->Capacity; i++){
        std::cout << this->string[i];
    }
    std::cout << std::endl;
}

