#ifndef MYSTRING_H
#define MYSTRING_H

// TODO: Implement this header file
#include <iostream>

class MyString{
    public:
        //Constructors:
        MyString();
        MyString (const MyString& str);
        MyString (const char* s);

        // Destructor:
        ~MyString();
        void resize (size_t n);
        
        size_t size() const noexcept; // getter for size value
        size_t length() const noexcept; // Synonym for size
        size_t capacity() const noexcept{
            size_t cap = this->Capacity;
            return cap;
        }

        /*A "const function", denoted with the keyword const after a function 
        declaration, makes it a compiler error for this class function to change 
        a member variable of the class. However, reading of a class variables is 
        okay inside of the function, but writing inside of this function will generate 
        a compiler error.*/
        
        const char* data()const noexcept;// data (const noexcept)
        bool empty()const noexcept; // empty (const noexcept)
        const char& front() const; // front
        void clear() noexcept;
        const char& at(size_t pos) const; // at (had const at the end)

        // The weird stuff now
        friend std::ostream& operator<< (std::ostream& os, MyString str){
            // You need "at" working for this one because you can't access str's string
            os << str.string;
            return os;
        }


        MyString& operator= (const MyString& str);
        MyString& operator+= (const MyString& str); // Used to pass by reference const MyString& str
        
        size_t find (const MyString& str, size_t pos = 0) const noexcept;
        void Print(); // Print for testing

        // Bonus stuff:
        friend bool operator==(const MyString& lhs, const MyString& rhs){
            if (lhs.size() != rhs.size()){
                return false;
            }
            if (lhs.capacity() != rhs.capacity()){
                return false;
            }
            for (size_t i = 0; i < lhs.capacity(); i++){
                if (lhs.data()[i] != rhs.data()[i]){
                    return false;
                }
            }
            return true;
        }

        friend MyString operator+(const MyString& lhs, const MyString& rhs){
            MyString str;
            str+= lhs;
            str+= rhs;
            return str;
        }

    protected:
        int Capacity = 0; //Includes the null character \0 
        int size_string = 0; // Does not include the null character \0
        char *string;
};



#endif