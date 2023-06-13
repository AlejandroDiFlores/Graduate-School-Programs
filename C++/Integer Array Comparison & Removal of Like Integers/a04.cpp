//*****************************************************************************
// Author: Alejandro Flores
// Assignment: Assignment 4
// Date: 4/24/2023
/* Description: This program will receive input from the user to create two 
                separate arrays. The arrays will be sorted during the input 
                stage and then the two lists will be compared - any elements 
                that are shared will be removed from the first list only. */
// Input: userInput as int
// Output: set1 & set2 as array int
// Sources: zyBook, GD Iyer, Glen Sasek
//*****************************************************************************

#include <iostream>
#include <limits>
using namespace std;

//Declare global constant
const int CAP = 20;

//Declare prototypes
void readInput(int list[]);
void findIntersect(int set1[], int set2[]);
void deleteNum(int list[], int value);
void welcome();
void dataVal();
void sort(int list[], int count);

//Name:   main()
//Desc:   This function is the starting point for program execution
//input:  None
//output: set1 & set2 as int arrays
//return: 0;
int main() {
  
  //Declare variables
  int set1[CAP] = {0}, set2[CAP] = {0}, i = 0;
  
  //Call welcome for greeting
  welcome();
  
  //Build first array by calling readInput
  cout << "Enter the numbers for set 1 on separate lines (-1 to end):" 
       << endl;
  readInput(set1);
  cout << endl;
  cout << "Your set 1 with " << set1[0] << " numbers ordered:" << endl;
  for (i = 1; i <= set1[0]; i++) {
    cout << set1[i] << " ";
  }
  cout << endl;
  
  //Build second array by calling readInput 
  cout << endl;
  cout << "Enter the numbers for set 2 on separate lines (-1 to end):" 
       << endl;
  readInput(set2);
  cout << endl;
  cout << "Your set 2 with " << set2[0] << " numbers ordered:" << endl;
  for (i = 1; i <= set2[0]; i++) {
    cout << set2[i] << " ";
  }
  cout << endl;
  
  //Call findIntersect to find where array values match and cull it from set1
  cout << endl;
  findIntersect(set1, set2);
  
  //Display the new set arrays
  cout << "The new sets are: " << endl;
  cout << "Set1: ";
  for(i = 1; i <= set1[0]; i++) {
    cout << set1[i] << " ";
  }
  cout << endl;
  cout << "Set2: ";
  for(i = 1; i <= set2[0]; i++) {
    cout << set2[i] << " ";
  }
  cout << endl;

  //Display goodbye message
  cout << endl;
  cout << "Thank you for using my Set of Numbers program!" << endl;
  
	return 0;
}

//Name:   readInput()
//Desc:   Receives input from user to build array and stops when input is -1
//input:  userInput as int
//output: counts as int
//return: None
void readInput(int list[]){
  int i, counts = 0, userInput = 0, newPos = 0;
  bool looper = true;
  
  for(i = 1; i < CAP && looper != false; i++) {
    cin >> userInput;
    if(!cin || userInput < 0 && userInput != -1){
      cout << "Invalid input! Please enter a valid integer: " << endl;
      dataVal();
      i--;
    }
    else if (userInput == -1) {
      looper = false;
    }
    else {
      list [i] = userInput;
      counts++;
    }
  }
  list[0] = counts;
  dataVal();
  sort(list, list[0]);
}

//Name:   findIntersect()
//Desc:   Compares two arrays and finds which values are shared
//input:  set1 and set2 as int array
//output: None
//return: None
void findIntersect(int set1[], int set2[]){
  int i, j = 0, value;

  for(i = 1; i <= set1[0]; i++) {
    for (j = 1; j <= set2[0]; j++) {
      if (set2[j] == set1[i]) {
        deleteNum(set1, i);
      }
    }
  }
}

//Name:   deleteNum()
//Desc:   Deletes a value from an array
//input:  list as int array, value as int
//output: None
//return: None
void deleteNum(int list[], int value){
  int i;
  for( i = value; i <= list[0]; i++) {
    list[i] = list[i+1];
  }
  list[0] = list[0]-1;
}


//Name:   welcome()
//Desc:   Displays a greeting message
//input:  None
//output: Prompt
//return: None
void welcome() {
  cout << "Welcome to my Set of Numbers program!!" << endl;
}

//Name:   dataVal()
//Desc:   Clears the stream of any empty space that may cause issues
//input:  None
//output: None
//return: None
void dataVal() {
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

//Name:   sort()
//Desc:   Sorts array in ascending order
//input:  list as int array, count as int
//output: None
//return: None
void sort(int list[], int count){
  int i;
  int j;
  double minVal;
  int minIndex;
  for(i = 1; i <= count; i++) {
    minVal = list[i];
    minIndex = i;

    for (j = i+1; j <= count; j++) {
      if(minVal > list[j]) {
        minVal = list[j];
        minIndex = j;
      }
    }
    if (minIndex != i) {
      list[minIndex] = list[i];
      list[i] = minVal;
    }
  }
}


