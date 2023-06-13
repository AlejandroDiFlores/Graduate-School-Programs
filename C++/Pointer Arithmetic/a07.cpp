//*****************************************************************************
// Author:      Alejandro Flores
// Assignment:  Assignment 7
// Date:        6/2/2023
// Description: This program prompts the user for two integers and then runs 
//              them through some formulas, returning the values to the user.
// Input:       a and b as ints
// Output:      a and b as ints
// Sources:     zyBook, GD Iyer
//*****************************************************************************
#include <iostream>
using namespace std;

void swapArgs(int * valueA, int * valueB);
void divideArgs(int * valueA, int * valueB);
void powerArgs(int * valueA, int * valueB);

//Name:   main()
//Desc:   This function is the starting point for program execution
//input:  a and b as ints.
//output: prompts;
//return: 0;
int main() {
  //create two int variables
  int a = 0, b = 0;
  //prompt user for two ints
  cout << "Enter integer 1: ";
  cin >> a;
  cout << "Enter integer 2: ";
  cin >> b;
  //pass their address to the pointer parameters
  //if user enters two zero's, print "No operations performed!" and end program
  if (a == 0 && b == 0) {
    cout << "\nNo operations performed!";
  }
  else {
    //Output values of two integers entered
    cout << "\nBefore call to swapArgs a: " << a << " b: " << b << endl;
    //Output values of integers after each value
    swapArgs(&a, &b);
    cout << "After call to swapArgs a: " << a << " b: " << b << endl;
    divideArgs(&a, &b);
    cout << "After call to divideArgs a: " << a << " b: " << b << endl;
    powerArgs(&a, &b);
    cout << "After call to powerArgs a: " << a << " b: " << b << endl; 
    cout << "\nGoodbye!";
  }
	return 0;
}

//Name:   swapArgs()
//Desc:   This function that takes 2 pointers to integers and swaps the 
//        integers read in main().
//input:  valueA and valueB as pointers
//output: None
//return: 0;
void swapArgs(int * valueA, int * valueB){
  int bucket = *valueA;
  *valueA = *valueB;
  *valueB = bucket;
}

//Name:   divideArgs()
//Desc:   This function that takes 2 pointers to integers and stores the
//        integer quotient in the first pointer parameter and the remainder in
//        the second pointer parameter.
//input:  valueA and valueB as pointers
//output: None
//return: 0;
void divideArgs(int * valueA, int * valueB){
  int quotient = 0, remainder = 0;

  quotient = (*valueA)/(*valueB);
  remainder = (*valueA)%(*valueB);

  *valueA = quotient;
  *valueB = remainder;
}

//Name:   powerArgs()
//Desc:   This function that takes 2 pointers to integers, raises the first 
//        integer to the power of the second integer, and stores the result in
//        the first integer.
//input:  valueA and valueB as pointers
//output: None
//return: 0;
void powerArgs(int * valueA, int * valueB){
  if (*valueB == 0) {
    *valueA = 1;
  }
  else if (*valueB < 0){
    //keep values the same, but can't use break
    *valueA = *valueA;
  }
  else {
    int multi = *valueA;
    for (int i = 1; i < *valueB; i++) {
      *valueA = (*valueA)*(multi);
    }
  }
}