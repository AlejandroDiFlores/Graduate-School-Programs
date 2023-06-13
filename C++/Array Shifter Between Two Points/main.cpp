/******************************************************************************
# Author:           Kyle Carson & Alejandro Flores
# Lab:              Discussion #4
# Date:             April 28, 2021
# Description:      This progam prompts the user for the size of an array, the
                    elements of the array, as well as from where the array 
                    should be shifted from - moving all elements after that to
                    the front of the array
# Input:            int array size, int array elements, int index 
# Output:           int array (re-ordered)
# Sources:          Zybooks
#******************************************************************************/

#include <iostream>
#include <limits>
using namespace std;

//Declare global constants
const int CAP = 20;
//Declare protoype functions
void welcome();
void inputNums(int array[]);
void adjustArray(int array[], int index);


int main() {
  int count = 0, numArray[CAP] = {0}, index = 0, i = 0;
  bool val = true;
  //Begin program and ask for length of array
  welcome();
  cout << "Please enter the number of integers you will enter: " << endl;
  cout << ">> ";
  //While loop for data validation
  while(val != false){
    cin >> count;
    if(cin.fail()) {
      cout << "Invalid input, please enter an integer: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
      val = false;
    }
  }
  val = true;
  numArray[0] = count;

  //Prompt user for array elements by calling inputNums function
  cout << "\nPlease enter your list of numbers with a space between each: " << endl;
  inputNums(numArray);

  //Prompt user to decide which index to swap the array calling adjustArray
  cout << "\nPlease enter the index of the numbers you want moved: " << endl;
  cout << ">> ";
  //While loop for data validation
  while(val != false) {
    cin >> index;
    if(cin.fail() || index > numArray[0] || index <= 0) {
      cout << "Invalid input. Enter a value within the array size: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
      val = false;
    }
  }
  adjustArray(numArray, index);

  //Displays the new array after re-ordering from selected index
  cout << "\nYour new array is: ";
  for(i = 1; i <= numArray[0]; i++) {
    cout << numArray[i] << " ";
  }

  //Display goodbye message
  cout << "\n\nThank you for using our shift the numbers to the right program!"
       << endl;
  
  return 0;
}

//Function greets the user
void welcome(){
  cout << "Welcome to our shift the numbers to the right program!" << endl;
}

//Function receives input from user to build array with, utilizing for loop
void inputNums(int array[]){
  int i = 0, userInput = 0;
  
  cout << ">> ";
  for(i = 1; i <= array[0]; i++) {
    cin >> userInput;
    array[i] = userInput;
  }
}

//Function swaps to the right numbers in array from desired index
void adjustArray(int array[], int index){
  int i = 0, j = 0, temp = 0;

  for ( i = 1; i <= index; i++) {
    temp = array[1]; 
    for (j = 1; j <= (array[0]-1); j++) { 
      array[j] = array[j+1];
    }
    array[j] = temp;
  }
}


