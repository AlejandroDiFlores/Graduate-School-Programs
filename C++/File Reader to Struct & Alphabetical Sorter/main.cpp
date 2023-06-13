//The client file or the driver file
//This file has the main() function
//Add header comments here.
//*****************************************************************************
// Author:      Alejandro Flores
// Assignment:  Assignment 6
// Date:        5/26/2023
// Description: This program keeps track of a course and its roster. It loads 
//              from a file the students' first and last names as well as their
//              gpa. It then provides a menu to add or remove a student as well
//              as print the roster, a student, or student with the highest gpa
// Input:       
// Output:      
//              
// Sources:     zyBook, GD Iyer
//*****************************************************************************
#include <iostream>
#include <cstring>

#include "Student.h"
#include "Course.h"

using namespace std;

int main() {
	Course course = initCourse();
  char lastName[20];
  Student bestStudent;
  ifstream inFile;
  cout << "Welcome to my Course Roster Program\n" << endl;
  inFile.open("students.txt");
  if(!inFile)
  {
    cout << "File did not open! Program Exiting!!" << endl;
    return 0;
  }
  //calls readStudent to read from the file
  readStudent(inFile, course);
  //calls printRoster to print the roster
  cout << "Here is the course roster: " << endl;
  printRoster(course);
  cout << endl;

  //calls dropStudent to drop a student from the roster.
  //read a last name into a char array and pass to function.
  //declare variables if needed

  /*Add code here to call function*/
  cout << "Enter the last name of the student to drop: ";
  cin >> lastName;
  dropStudent(lastName, course);
  //calls printRoster to print the roster after the student drop.
  //Uncomment the next 2 lines once you have dropped a student
  cout << "\nHere is the course roster: " << endl;
  printRoster(course);
  //calls findStudentHighestGPA to get Student with highest GPA
  //declare variables if needed
  /*Add code here to call function*/
  bestStudent = findStudentHighestGPA(course);

  //calls printStd to print the student with the highest GPA
  /*Add code here to call function*/
  cout << endl << "The student with the highest GPA: " << endl;
  printStd(bestStudent);
  cout << endl;
  cout << "Thank you for using my Student Roster program!!" << endl;
	return 0;
}