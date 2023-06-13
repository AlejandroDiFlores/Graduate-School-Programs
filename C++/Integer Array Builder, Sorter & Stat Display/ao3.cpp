//*****************************************************************************
// Author: Alejandro Flores
// Assignment: Assignment 3
// Date: 04/18/2023
// Description: This program will receive a list of numbers from the user and
//              sort them into an array and present stats about that list
// Input: integers as array
// Output: integers, doubles, bool
// Sources: zyBook, GDIyer, Glen Sasek
//*****************************************************************************

#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

//DECLARE global constants
const int maxSize = 20;

//DECLARE prototype functions
void readInput(int list[], int &count);
void maxmin(int list[], int count, int &max, int &min);
double avgArray(int list[], int count);
bool isPalindrome(int list[], int count);
void sort(int list[], int count);
double median(int list[], int count);
void welcome();

//Name:   main()
//Desc:   This function is the starting point for program execution
//input:   
//output: max, min, mean and middle as integers. palindrome as bool
//return: 0;
int main() {
  int posNumList[maxSize];
  int count = 0;
  int max = 0;
  int min = 0;
  double mean = 0;
  double middle = 0;
  bool palindrome;

  //Call function welcome for greeting message
  welcome();
  cout << "\n" << endl;

  //Call function readInput to build array from user input
  readInput(posNumList, count);

  //Call functions to read out desired stats
  cout << "Your stats are below: " << endl;
  //Call function to get min and max values and display them
  maxmin(posNumList, count, max, min);
  cout << "Minimum: " << min << endl;
  cout << "Maximum: " << max << endl;
  //Call function to get the mean value of the array and display it
  mean = avgArray(posNumList, count);
  cout << "Mean: " << mean << endl;
  //Call function to check array and see if it is a palindrome and display it
  palindrome = isPalindrome(posNumList, count);
  if(palindrome == false) {
    cout << "Palindrome: false" << endl;
  }
  else {
    cout << "Palindrome: true" << endl;
  }
  //Call function to get the median value of the array and display it
  middle = median(posNumList, count);
  cout << "Median: " << middle << endl;

  //Display goodbye message
  cout << "\n" << "Thank you for using my Array Statistics program!!" << endl;
  
	return 0;
}

//Name:   readInput()
//Desc:   Reads a list of positive integers from the user
//input:  temp as int
//output: stillPos as bool, list as int array
//return: None
void readInput(int list[], int &count){
  bool stillPos = true;
  int i;
  int temp;
  cout << "Please enter the values for the array " << 
          "(negative number will end input): " << endl;
  for(i = 0; i < maxSize && stillPos; i++){
    cin >> temp; 
    if (cin.fail()) {
      cout << "Incorrect value! Please try again!" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      stillPos = true;
    }
    if (temp >= 0) {
      list[i] = temp;
      count++;
      stillPos = true;
    }
    else if (temp < 0){
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      stillPos = false;
    }
  }
}

//Name:   maxmin()
//Desc:   Loops through array to return min and max values within
//input:  None
//output: None
//return: min and max values as int
void maxmin(int list[], int count, int &max, int &min){
  int i;
  min = list[0];
  max = list[0];

  for(i = 0; i < count; i++) {
    if(list[i] < min) {
      min = list[i];
    }
  }
  for(i = 0; i < count; i++) {
    if(list[i] > max) {
      max = list[i];
    }
  }
}

//Name:   avgArray()
//Desc:   Loops through array to calculate the mean
//input:  None
//output: None
//return: avg as a double
double avgArray(int list[], int count){
  int i;
  int sum = 0;
  double avg;

  for(i = 0; i < count; i++) {
    sum = sum + list[i];
  }
  avg = sum / (count*1.0);
  avg = round(avg*10)/10;
  return avg;
}

//Name:   isPalindrome()
//Desc:   Loops through the array to check if it is a palindrome
//input:  None
//output: None
//return: palindrome as a bool
bool isPalindrome(int list[], int count){
  int i;
  int j = 0;
  int reverseList[count];
  bool palindrome = true;

  for(i = count -1; i >= 0; i--) {
    reverseList[j++] = list[i];
  }
  
  for(i = 0; i < count; i++) {
    if(list[i] != reverseList[i]) {
      palindrome = false;
    }
  }
  return palindrome;
}

//Name:   sort()
//Desc:   Sorts through array and organizes it smallest to largest
//input:  None
//output: None
//return: list as int array
void sort(int list[], int count){
  int i;
  int j;
  double minVal;
  int minIndex;
  for(i = 0; i < count-1; i++) {
    minVal = list[i];
    minIndex = i;

    for (j = i+1; j < count; j++) {
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

//Name:   median()
//Desc:   Find the median value of the array
//input:  None
//output: None
//return: median as a double
double median(int list[], int count){
  double median;
  double lowMed;
  double highMed;
  
  //Calls function sort to organize array, which makes finding the median easy
  sort(list, count);
  //Checks if array size is even or odd, if so it calculates the median value
  if (count%2 == 0) {
    lowMed = list[(count/2)-1];
    highMed = list[(count/2)];
    median = (lowMed + highMed)/2.0;
  }
  else {
    median = (list[count/2])*1.0;
  }
  return median;
}

//Name:   welcome()
//Desc:   Displays a greeting
//input:  None
//output: prompt
//return: None
void welcome(){
  cout << "Welcome to my Array Statistics program!" << endl;
}
