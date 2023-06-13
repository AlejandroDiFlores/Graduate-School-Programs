/*****************************************************************************
# Author:           Sam Wilson and Alejandro Flores
# Assignment:       Discussion 3
# Date:             04/19/2023
# Description:      This program asks the user to input a positive number over
20. The user is then asked to input that many integers into a int array. The
program then asks the user to input 2 more integers representing the beginning
and end of items in the list array. If all the items from the beginning of the
list to the end of the list are congruent, the program displays yes, if not
the program displays no.
# Input:            numVals, beginPos, and endPos as integers.
                    list[] as a integer array
# Output:           none
# Who did what:
# Sam:              header and design doc
# Alex:             code and comments
# Sources:          Zybooks
*****************************************************************************/
#include <cmath>
#include <iostream>
#include <limits>

using namespace std;

// Declare global constants
const int maxCap = 20;

// Name:   main()
// Desc:   The starting point for program execution.
// input:  numVals as int array, beginPos and endPos as integers.
// output: None
// return: None
int main() {
  int i;
  double notInt;
  int numVals;
  int list[maxCap];
  int beginPos;
  int endPos;
  bool yN;
  bool inRange = false;
  bool valid = true;
  bool begRange;
  bool endRange;

  //Welcome message
  cout << "Welcome to our array analyzer! This program will determine if "
       << "the array is congruent between two chosen values." << endl;

  //Prompt to get range of array with data validation
  cout << "Enter the size of the list(max 20): " << endl;
  while (inRange != true) {
    cin >> numVals;
    if (cin.fail() || numVals == notInt) {
      cout << "Error! Please enter valid input: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else if (numVals > 20 || numVals < 2) {
      cout << "Error! Please select an integer within range: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    } else {
      inRange = true;
    }
  }
  //Validation to prevent doubles
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  //Prompt using For loop to build user array with data validation
  cout << "Enter the numbers in the list: " << endl;
  for (i = 0; i < numVals; i++) {
    cin >> list[i];
    if (cin.fail()) {
      cout << "Error! Please enter valid input: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      i--;
    }
  }

  /*Prompt while loop to ask for beginning and ending range to check 
  against array, with data validation*/
  while (valid != false) {
    //Calling user input with data validation for beginning range
    cout << "Enter the beginning parameter: " << endl;
    begRange = false;
    //Validation to prevent doubles
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (begRange != true) {
      cin >> beginPos;
      if (cin.fail()) {
        cout << "Error! Please enter beginning parameter: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else {
        begRange = true;
      }
    }
    
    //Calling user input with data validation for end range
    cout << "Enter the end parameter: " << endl;
    endRange = false;
    //Validation to prevent doubles
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    while (endRange != true) {
      cin >> endPos;
      if (cin.fail()) {
        cout << "Error! Please enter valid end parameter: " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      } else {
        endRange = true;
      }
    }

    /* Validates range is logical or within parameters, if not, the loop
    starts from beginning to ask for beginning & end positions */
    if (endPos <= beginPos || endPos > 20) {
      cout << "Error, range invalid!" << endl;
    } else {
      valid = false;
    }
  }

  //For loop to check array for congruency against beginning and end range
  for (i = beginPos-1; i < endPos-1; i++) {
    yN = true;
    if (list[i] > list[i + 1]) {
      yN = false;
    }
  }
  //References above For loop to output whether or not array is congruent
  if (yN == false) {
    cout << "no" << endl;
  } else {
    cout << "yes" << endl;
  }
  
  //Goodbye message
  cout << "Thank you for using our program, goodbye!" << endl;

  return 0;
}
