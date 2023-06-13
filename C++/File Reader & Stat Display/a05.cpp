//*****************************************************************************
// Author:      Alejandro Flores
// Assignment:  Assignment 5
// Date:        5/13/2023
// Description: This program will read from a text file and run some data
//              analysis on that file. Data will be stored into parallel arrays
//              and the sum, average, high and low values of data columns will
//              be displayed.
// Input:       txt file
// Output:      txt file as table; sum, highPower, lowCost, totalCost as ints,
//              averagePower as a double
// Sources:     zyBook, GD Iyer, Glen Sasek, Rachael Tatman via Kaggle
//*****************************************************************************

#include <iostream>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <limits>
using namespace std;

//include global constants
const int CAP = 400;
const int charCAP = 100;

//include function prototypes
void welcome();
bool openFile(ifstream &inFile);
int loadData(ifstream &inFile, char moveList[][charCAP], 
             int moveDetails[][2]);
void summationCalc(int moveDetails[][2]);
void goodbye();

//Name:   main()
//Desc:   This function is the starting point for program execution
//input:  None
//output: None
//return: 0;
int main() {
  //declare variables
  ifstream inFile;
  int count = 0;
  char moveList[CAP][charCAP];
  int moveDetails[CAP][2] = {0};

  //call welcome function
  welcome();
  cout << endl;
  
  /*call openFile function to open file and exit if there is an error with
  opening said file */
  if(!openFile(inFile)) {
    cout << "File did not open! Program terminating!" << endl;
    exit(0);
  }
  
  //call loadData to read from arrays and do some data analysis (hi/low vals)
  count = loadData(inFile, moveList, moveDetails);
  cout << "There are exactly " << count << " moves in the game." <<endl 
       << endl;

  //call summationCalc to read from the arrays and conduct data analysis
  summationCalc(moveDetails);
  
  //Close the file and end the program
  inFile.close();
  cout << endl;
  goodbye();
  
  return 0;
}

//Name:   welcome()
//Desc:   This function greets the user
//input:  None
//output: prompt
//return: None
void welcome(){
  cout << "Hello, welcome to my File Input/Output program!" << endl << endl;
  cout << "This program contains information about the Digimon game"
       << " 'Cyber Sleuth'. It will generate information about the moves "
       << " available in the game based on a file entered." << endl;
}

//Name:   openFile()
//Desc:   This function opens file and returns true or false
//input:  inFile
//output: None
//return: true or fales;
bool openFile(ifstream &inFile) {
  inFile.open("yourfile.txt");
  if(!inFile) {
    return false;
  }
  return true;
}

//Name:   loadData()
//Desc:   This function opens takes info from file and loads them into arrays
//input:  inFile as txt 
//output: moveList as char array, moveDetails as int array
//return: count as int;
int loadData(ifstream &inFile, char moveList[][charCAP], 
             int moveDetails[][2]){
  //declare variables
  int count = 0;
  int highPower = moveDetails[0][1];
  int lowCost = moveDetails[0][0];
  int length;
  int i;

  cout << "Opening file...." << endl << endl << endl;
  
  //display category of columns to user of data file 
  inFile.getline(moveList[0], charCAP, '\n');
  cout << moveList[0] << endl;
  cout << "_______________________     _______     _____" << endl;
  inFile.getline(moveList[count], charCAP, ';');

  //read from file, display info as a table, and calc high/low values
  while(!inFile.eof()){
    if(strlen(moveList[count]) < 30){
      length = strlen(moveList[count]);
      length = 30-length;
      cout << moveList[count];
      for(i = 0; i <= length; i++) {
        cout << " ";
      }
    }
    inFile >> moveDetails[count][0];
    if(moveDetails[count][0] < 10){
      length = 8;
      cout << moveDetails[count][0];
      for(i = 0; i <= length; i++) {
        cout << " ";
      }
    }
    else if(moveDetails[count][0] < 100){
      length = 7;
      cout << moveDetails[count][0];
      for(i = 0; i <= length; i++) {
        cout << " ";
      }
    }
    
    if(lowCost > moveDetails[count][0]){
      lowCost = moveDetails[count][0];
    }
    inFile.ignore(5, ';');
    
    inFile >> moveDetails[count][1];
    cout << moveDetails[count][1] << endl;
    
    if(highPower < moveDetails[count][1]){
      highPower = moveDetails[count][1];
    }
    inFile.ignore(5, '\n');
    
    count++;
    inFile.getline(moveList[count], CAP, ';');
  }
  cout << endl;
  cout << "Detailing results for file: " << endl << endl;
  cout << "The highest power for a move available is " << highPower << "." 
       << endl << endl;
  cout << "The lowest cost for a move available is " << lowCost << " SP."
       << endl << endl;
  
  return count;
}

//Name:   summationCalc()
//Desc:   This function calculates the average power of moves in the game
//        as well as the sum costs of all those moves
//input:  moveDetails as int array
//output: averagePower as double, totalCost as int
//return: none
void summationCalc(int moveDetails[][2]){
  double averagePower;
  int totalCost = 0;
  int tempPower = 0;
  int i;

  for (i = 0; i < 388; i++){
    totalCost = totalCost + moveDetails[i][0];
    tempPower = tempPower + moveDetails[i][1];
  }
  averagePower = tempPower/(387*1.0);
  averagePower = round(averagePower*100)/100;
  
  cout << "The average power of all moves in the game is: " 
       << averagePower << " power." << endl;
  cout << "The total cost of using all moves in game is: " 
       << totalCost << " SP." << endl;
}

//Name:   goodbye()
//Desc:   This function lets the user know the program has ended
//input:  None
//output: prompt
//return: None
void goodbye(){
  cout << "Thank you for using my program!" << endl;
  cout << "See you space cowboy..." << endl;
}