#include <iostream>
#include <limits>
#include <cstring>
#include <cctype>
#include "DataValidation.h"

using namespace std;

//Name:   validateInput()
//Desc:   This function validates userInput isn't negative or a valid data type
//input:  None
//output: None
//return: valid as a bool
bool validateInput(int userInput){
  bool valid = true;
  
  if (!userInput || userInput < 0) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    valid = false;
    cout << "Invalid response. " 
         << "Please enter a whole, non-negative number." << endl;
  }
  return valid;
}

//Name:   validateInput()
//Desc:   This function validates userInput isn't negative or a valid data type
//input:  None
//output: None
//return: valid as a bool
bool validateInput(double userInput){
  bool valid = true;
  
  if (!userInput || userInput < 0) {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    valid = false;
    cout << "Invalid response."
         << " Please enter a non-negative number." << endl;
  }
  return valid;
}

//Name:   validateInputMain()
//Desc:   This function validates userInput isn't negative or a valid data type of main menu selections
//input:  None
//output: None
//return: valid as a bool
bool validateInputMain(char userInput){
  bool valid = true;
  char userInputUpper = toupper(userInput);
  
  if (userInputUpper != 'A' && userInputUpper != 'B' && userInputUpper != 'C'
      && userInputUpper != 'D' && userInputUpper != 'Q') {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    valid = false;
    cout << "Invalid response. " 
         << "Please enter a valid selection (A, B, C, D, or Q):" << endl 
         << endl;
  }
  return valid;
}

//Name:   validateInput()
//Desc:   This function validates userInput isn't negative or a valid data type of A or B
//input:  None
//output: None
//return: valid as a bool
bool validateInput(char userInput){
  bool valid = true;
  char userInputUpper = toupper(userInput);
  
  if (userInputUpper != 'A' && userInputUpper != 'B') {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    valid = false;
    cout << "Invalid response. " 
         << "Please enter a valid selection (A or B):" << endl << endl;
  }
  return valid;
}
