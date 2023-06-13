/******************************************************************************
# Author:           Alejandro Flores, Kyle Carlson, Sam Wilson
# Lab:              Discussion #6
# Date:             05/20/2023
# Description:      This program asks the user what species of pet they used 
                    to own, how many years they owned them, and the pets name. 
                    The program then outputs the users inputs. The user is 
                    then asked if they would like to input another pet. The 
                    program closes when the user decides not to input anymore 
                    pets.
# Input:            char myPets[count].petType, char myPets[count].petName,                        
                    int myPets[count].years, char userInput
# Output:           char myPets[i].petType, char myPets[i].petName, 
                    int myPets[i].years
# Who did what:
# Alex              code
# Kyle              design.doc
# Sam               code and header
# Sources:          ZyBooks
#******************************************************************************/
#include <iomanip> //to use setw() to space out columns
#include <iostream>
#include <limits>

using namespace std;

// create constant for max limit of char arrays
const int MAXCHAR = 30;
// create structures
// structure needs 1-2 char arrays and 3 data members
struct petsOwned {
  char petType[MAXCHAR] = {0}; // species of the animal
  char petName[MAXCHAR] = {0}; // name of the animal
  int years = 0;               // how many years did you own the animal
};

// create function prototypes
void buildStruct(petsOwned myPets[], int &count);
void printStruct(const petsOwned myPets[], int count);
void welcome();
void goodbye();

// Name:   main()
// Desc:   This function is the starting point for program execution
// input:  None
// output: None
// return: 0;
int main() {
  int count = 0;        // will be used for loops during printStruct function
  petsOwned myPets[50]; // create a variable of the defined struct

  welcome();

  // pass the variable by reference to buildStruct
  buildStruct(myPets, count);
  cout << endl;
  // pass variable by constant reference to printStruct()
  printStruct(myPets, count);

  goodbye();
  return 0;
}

// Name:   buildStruct()
// Desc:
// input:  None
// output: None
// return: 0;
void buildStruct(petsOwned myPets[], int &count) {
  bool petLoop = true;
  bool dataVal = true;
  char userInput;
  // prompt user to build Struct data
  // increase count with each full set of Struct completed
  // data validate all user input
  while (petLoop) {
    
    cout << "What kind of pet did you own? (species) : " << endl;
    while(dataVal != false) {
      cin.getline(myPets[count].petType, MAXCHAR, '\n');
      if(cin.fail()) {
        cout << "Invalid input, please enter an animal (dog, cat, gecko etc.)" 
             << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      else{
        dataVal = false;
        cout << endl;
      }
    }
    dataVal = true;
    
    cout << "How many years did you own this " << myPets[count].petType 
         << "? :" << endl; 
    while(dataVal != false) {
      cin >> myPets[count].years;
      if(cin.fail()) {
        cout << "Invalid input, please enter an integer." 
             << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      else{
        dataVal = false;
        cout << endl;
        cin.ignore(100, '\n');
      }
    }
    dataVal = true;

    cout << "What was this " << myPets[count].petType << "'s name? :" << endl;
    while(dataVal != false) {
      cin.getline(myPets[count].petName, MAXCHAR, '\n');
      if(cin.fail()) {
        cout << "Invalid input, please enter non-integer characters." 
             << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      else{
        dataVal = false;
        cout << endl;
      }
    }
    dataVal = true;
    
    cout << "Did you own any more pets? (y/n): " << endl;
    while(dataVal != false) {
      cin >> userInput;
      if(userInput != 'y' && userInput != 'n') {
        cout << "Please enter either 'y' or 'n': " << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
      }
      else {
        dataVal = false;
        cout << endl;
      }
    }
    dataVal = true;
    
    petLoop = userInput != 'n';
  
    cin.clear();
    cin.ignore(100, '\n');
    
    count++;
    cout << endl;
  }
}

// Name:   printStruct()
// Desc:
// input:  None
// output: None
// return: 0;
void printStruct(const petsOwned myPets[], int count) {
  // print the members of the struct variable
  int i = 0;
  // implement setw() for better table
  cout << "Now exporting a table of the pets you've owned..." << endl << endl;
  
  cout << left << setw(20) << "Pet Species";
  cout << left << setw(15) << "Pet Name";
  cout << left << setw(10) << "Years Owned" << endl;
  for (i = 0; i <= 45; i++) {
    cout << "_";
  }
  cout << endl << endl;;
  
  for (i = 0; i < count; i++) {
    cout << setw(20) << left << myPets[i].petType;
    cout << left << setw(15) << myPets[i].petName;
    cout << setw(10) << left << myPets[i].years << endl;
  }
}

// Name:   welcome();
// Desc:   This message greets the user and explains the program
// input:  None
// output: prompt;
// return: 0;
void welcome() {
  cout << "Greetings! This program will ask you questions about pets you've "
       << "owned, build it into a structure and then output said structure. " 
       << endl << endl;
}

// Name:   goodbye();
// Desc:   This message alerts the user the program has ended
// input:  None
// output: prompt;
// return: 0;
void goodbye() {
  cout << endl;
  cout << "Terminating program..." << endl << endl;
  cout << "Thank you for using our program!" << endl;
  cout << "Goodbye!" << endl;
}