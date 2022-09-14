// These headers define some of the classes and functions we need
#include <iostream>
#include <string>
#include <sstream>
#include <limits>

// ONLY MAKE CHANGES WHERE THERE IS A TODO

// These using declarations let us refer to things more simply
// e.g. instead of "std::cin" we can just write "cin"
using std::cin, std::cout, std::endl;
using std::string, std::getline;

// These methods are defined below the main function

// print instructions for inputting grades
void print_instructions();

// pretty print a summary of the grades
void print_results(double exam_average,
                   double hw_average,
                   double lw_average,
                   double engagement,
                   double weighted_total,
                   char final_letter_grade);

// YOU ARE NOT EXPECTED TO UNDERSTAND THIS ONE... YET
// extract the category and score from the line
// and store the values in the provided variables
// if line := "exam 95", then category := "exam" and score := 95
// if the line is invalid, then category := "ignore"
void get_category_and_score(const string& line,
                            string* category,
                            double* score);

int main() {
    print_instructions();

    // ONLY MAKE CHANGES WHERE THERE IS A TODO

    // TODO(student): declare and initialize variables that you want
    double examPointSum = 0;
    double examAmount = 0;
    double hwPointSum = 0;
    double hwAmount = 0;
    double lwPointSum = 0;
    double lwAmount = 0;
    double engagementPointSum = 0;
    double finalExamGrade = 0;
    

    string line;
    // read one line from standard input (discards the ending newline character)
    getline(cin, line);
    // read lines until an empty line is read
    while (!line.empty()) {
        string category;
        double score;
        get_category_and_score(line, &category, &score);

        // process the grade entry

        //For code: Exams (including final) are 40%, engagement is 10%, Homework is 40%, labwork is 10%
        //13.333 for each exam technically

        if (category == "exam") {
            // TODO(student): process exam score
            examPointSum += score;
            examAmount += 1;
        
        } else if (category == "final-exam") {
            // TODO(student): process final score
            //examPointSum += score;
            //examAmount += 1;
            finalExamGrade = score;
            
        } else if (category == "hw") {
            // TODO(student): process hw score
            hwPointSum += score;
            hwAmount += 1;
        } else if (category == "lw") {
            // TODO(student): process lw score
            if (score>0){
                lwPointSum +=100;
                lwAmount +=1;    
            }
            else if (score <= 0){
                lwAmount += 1;
            }
        } else if (category == "engagement") {
            // TODO(student): process engagement score
            engagementPointSum += score;
                
        } else {
            cout << "ignored invalid input" << endl;
        }

        // get the next line from standard input
        getline(cin, line);
    }

    // TODO(student): compute component averages
    double exam_average = 0;
    double hw_average = 0;
    double lw_average = 0;
    double engagement = 0;

    
    double a = examPointSum;
    exam_average = examPointSum/2; 
    
    if (exam_average < finalExamGrade){
        exam_average = finalExamGrade;
    }
    if (exam_average > finalExamGrade){
        exam_average = (a + finalExamGrade)/3;

        //The reason why you get -nan when you output is because you are dividing by 0 at some points
        //Make an if statement to ensure that if xAmount == 0, it just sets the x_average as 0 
    }

    if (hwAmount > 0){
        hw_average = hwPointSum/hwAmount; 
        //The reason why you get -nan when you output is because you are dividing by 0 at some points
        //Make an if statement to ensure that if xAmount == 0, it just sets the x_average as 0 
    }
    if (hwAmount <= 0){
        hw_average = 0;
    }
    
    if (lwAmount > 0){
        lw_average = lwPointSum/lwAmount; 
        //The reason why you get -nan when you output is because you are dividing by 0 at some points
        //Make an if statement to ensure that if xAmount == 0, it just sets the x_average as 0 
    }
    if (lwAmount <= 0){
        lw_average = 0;
    }

    //Engagement is weird. 
    if (engagementPointSum > 100){ //look into the grading of the course engagement. This is the main issue with your code atm
        engagement = 100; 
        //The reason why you get -nan when you output is because you are dividing by 0 at some points
        //Make an if statement to ensure that if xAmount == 0, it just sets the x_average as 0 
    }
    if (engagementPointSum > 0 && engagementPointSum <=100){
        engagement = engagementPointSum;
    }

    // TODO(student): compute weighted total of components
    double weighted_total = 0.0;
    weighted_total = exam_average * 0.4 + hw_average * 0.4 + lw_average * 0.1 + engagement * 0.1;

    // TODO(student): compute final letter grade
    char final_letter_grade = 'X';

    if (weighted_total >= 89.5 && weighted_total <= 100){
        final_letter_grade = 'A';
    }
    else if (weighted_total >= 79.5){
        final_letter_grade = 'B';
    }
    else if (weighted_total >= 69.5){
        final_letter_grade = 'C';
    }
    else if (weighted_total >= 59.5){
        final_letter_grade = 'D';
    }
    else if (weighted_total >= 0 && weighted_total < 60){
        final_letter_grade = 'F';
    }

    print_results(
        exam_average, hw_average, lw_average, engagement,
        weighted_total, final_letter_grade);
}

// These methods are already implemented for you
// You should not need to modify them

void print_instructions() {
    cout << "enter grades as <category> <score>" << endl;
    cout << "  <category> := exam | final-exam | hw | lw | engagement" << endl;
    cout << "     <score> := numeric value" << endl;
    cout << "enter an empty line to end input" << endl;
}

void get_category_and_score(
    const string& line,
    string* category,
    double* score) {
    // turn the string into an input stream
    std::istringstream sin(line);

    // read the category (as string) and score (as double) from the stream
    sin >> *category;
    sin >> *score;

    if (sin.fail()) {
        // the stream is in a fail state (something went wrong)
        // clear the flags
        sin.clear();
        // clear the stream buffer (throw away whatever garbage is in there)
        sin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        // signal that the line was invalid
        *category = "ignore";
    }
}

void print_results(
    double exam_average,
    double hw_average,
    double lw_average,
    double engagement,
    double weighted_total,
    char final_letter_grade) {
    cout << "summary:" << endl;
    cout << "      exam average: " << exam_average << endl;
    cout << "        hw average: " << hw_average << endl;
    cout << "        lw average: " << lw_average << endl;
    cout << "        engagement: " << engagement << endl;
    cout << "    ---------------" << endl;

    cout << "    weighted total: " << weighted_total << endl;

    cout << "final letter grade: " << final_letter_grade << endl;
}


//In lab work, a 0 means you get a 0, and anything else means you have a perfect score (of 1)
//points will add up to more than 100 for engagement, so the score of 121 has to be brought down to 100


//This is for me, so please ignore
//Compile: g++ -std=c++17 -Wall -Wextra -pedantic -Weffc++ grade_calculator.cpp
//File as input: ./a.out < test_complete_1.txt