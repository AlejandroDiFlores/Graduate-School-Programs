//*****************************************************************************
// Author: Alejandro Flores
// Assignment: Assignment 2
// Date: 04/14/2023
// Description: This program will encode a file presented by the user based on
//               a series of answered queries. 
// Input:
// Output:
// Sources: zyBook, GDIyer, Glen Sasek
//*****************************************************************************

//TO DO: Fix it so inputs can't go past limits
#include <iostream> 
#include <cstring>
#include <cctype>
#include <limits>
// Only #include libraries being used.
// Do not #include <bits/stdc++>

using namespace std;

//DECLARE constants
const int maxLength = 101;
const char underScore[2] = "_";
const int maxName = 30;
const int maxparsedID = 5;
const int maxfileName = 30;
const int maxstrTime = 5;
const int maxstudentID = 12;
//DECLARE protype functions
void welcome();
void menuOption();
char displayMenu();
void encode(char array[]);
void readInput(char fName[], char lName[], bool &lateFlag);
void readInput(char parsedID[], char fileName[]);
void readTime(char strTime[]);
void makeLowerArray(char makeLower[]);

//Name:   main()
//Desc:   This function is the starting point for program execution
//input:  None
//output: int, prompts
//return: 0;
int main() {
  //DECLARE variables
  bool aLooper = true;
  //response will reference the option selected in displayMenu function
  char response;
  char encodedFileName[maxLength];
  //CALL welcome function
  welcome();
  //while loop to encode or stop program depending on response
  while(aLooper!= false){
    response = displayMenu();
    if(response == 'y'){
      //call encode function
      encode(encodedFileName);
      cout << "Your encoded file name is: " << encodedFileName << endl;
      cout << "" << endl;
    }
    else if(response == 'n') {
      cout << "Thank you for using my fileName generator!" << endl;
      aLooper = false;
    }
    else {
      cout << "Invalid response! Please try again!!" << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
	return 0;
}

//Name:   welcome()
//Desc:   This function displays a welcome message
//input:  None
//output: prompt
//return: None
void welcome(){
  cout << "Welcome to my fileName encoding program!!" << endl;
}

//Name:   menuOption()
//Desc:   This function displays a menu of options to select from
//input:  None
//output: prompts
//return: None
void menuOption(){
  cout << "Please pick an option below: " << endl;
  cout << "(e) Encode a file name" << endl;
  cout << "(q) quit" << endl;
}
//Name:   displayMenu()
//Desc:   This program references the option to encode or not
//input:  None
//output: char, prompts
//return: char
char displayMenu(){
  char menuChoice;
  char picker;
  bool valid = false;
  //loop to accept only valid response and return answer to continue or not
  do {
    menuOption();
    cin >> menuChoice;
    if(menuChoice == 'e') {
      picker = 'y'; 
      cout << "This program will ask you a few questions and generate an " <<
      "encoded fileName based on your answers." << endl;
      valid = true;
    }
    else if(menuChoice == 'q'){
      picker = 'n';
      valid = true;
    }
    else {
      cout << "Invalid option! Please try again!!" << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  } while(!valid);
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  return picker;
}

//Name:   encode()
//Desc:   This program calls for user input and compiles them into an
//        an encoded file name.
//input:  char
//output: None
//return: None
void encode(char array[]){
  char fName[maxName];
  char lName[maxName];
  bool lateFlag;
  char parsedID[maxparsedID];
  char fileName[maxfileName];
  char strTime[maxstrTime];
  char isLate[5] = "LATE";
  //call readInput to get first, last name and see if assignment is late
  readInput(fName, lName, lateFlag);
  //call readInput to get shortened ID and name of file
  readInput(parsedID, fileName);
  //call readTime to get time assignment was turned in
  readTime(strTime);
  //cstring functions to build new file name
  strcpy(array, lName);
  strcat(array, underScore);
  strcat(array, fName);
  strcat(array, underScore);
  //only includes late flag if assignment was late
  if (lateFlag == true) {
    strcat(array, isLate);
    strcat(array, underScore);
  }
  strcat(array, parsedID);
  strcat(array, underScore);
  strcat(array, strTime);
  strcat(array, underScore);
  strcat(array, fileName);
}


//Name:   readInput()
//Desc:   This program reads the first and last name from the user and
//        also determines if the assignment was turned in on time
//input:  char arrays
//output: prompts
//return: None

void readInput(char fName[], char lName[], bool &lateFlag) {
  char c;
  bool aLooper = true;
  //retrieve names from user
  cout << "Enter your last name: " << endl;
  //cin.getline(lName, maxName);
  cin.get(lName, maxName, '\n');
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  makeLowerArray(lName);
  cout << "Enter your first name: " << endl;
  cin.get(fName, maxName, '\n');;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  makeLowerArray(fName);
  //assess if assignment was late and creates a flag for such
  cout << "Was your assignment late (y/n)?" << endl;
  while(aLooper != false) {
    cin >> c;
    c = tolower(c);
    if(c == 'n') {
      lateFlag = false;
      aLooper = false;
    }
    else if(c == 'y') {
      lateFlag = true;
      aLooper = false;
    }
    else {
      cout << c << "Invalid option! Please try again!!" << endl;
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Name:   readInput()
//Desc:   This program reads student id and shortens it and reads file name
//input:  char arrays
//output: prompts
//return: None
void readInput(char parsedID[], char fileName[]){
  bool aLooper = true;
  char array[maxstudentID];
  cout << "Enter your Student-ID (format: 977-15-5587): " << endl;
  cin.get(array, maxstudentID, '\n');
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  //using cstring to copy only the last 4 numbers from the student ID
  strncpy(parsedID, array+7, 4);
  cout << "Enter the file name: " << endl;
  cin.get(fileName, maxfileName, '\n');
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Name:   readTime()
//Desc:   This programs read the time entered by user and validates the range
//input:  None
//output: None
//return: None
void readTime(char strTime[]) {
  int hours;
  int mins;
  char discard;
  cout << "Enter the time submitted (military time - ex: 18:24 for 6:24pm): "
       << endl;
  cin >> hours >> discard >> mins;
  while (!cin || discard != ':') {
    cout << "Invalid input! Please try again!!" << endl;
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin >> hours >> discard >> mins;
  }
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  strncpy(strTime, to_string(hours).c_str(), 3);
  strcat(strTime, to_string(mins).c_str());
}
//Name:   makeLowerArray()
//Desc:   This program makes the user names entered lowercase
//input:  char array
//output: none
//return: None
void makeLowerArray(char makeLower[]){
  int i;
  for(i = 0; i < maxName; i++) {
    makeLower[i] = tolower(makeLower[i]);
  }
}
