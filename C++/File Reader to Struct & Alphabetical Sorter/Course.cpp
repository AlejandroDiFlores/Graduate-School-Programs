//The implementation file for Course.h
//It loads students from a text file.
#include <iostream>
#include <cstring>
#include <limits>

#include "Course.h"
#include "Student.h"
using namespace std;

//initiaizes a course variable and returns it. The array is empty
//and the number of students is set to 0.
Course initCourse() {
	Course course;
	course.numStudents = 0;
	return course;
}

//reads a student from the file and calls AddStudent
void readStudent(ifstream &inFile, Course &course)
{
 /*Add code here to read from the file and call addStudent to add each student to the roster.*/ 
  Student student;
  do {
    inFile.get(student.first, 20, ';');
    inFile.ignore(numeric_limits<streamsize>::max(), ';');
    inFile.get(student.last, 20, ';');
    inFile.ignore(numeric_limits<streamsize>::max(), ';');
    inFile >> student.gpa;
    inFile.clear();
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    addStudent(student, course);
  } while (!inFile.eof());
}

//adds a student to the roster, and increment count
//modify this function to add the student sorted by name
//do not use any sorting functions.
//See this example in zyBooks Section 14.7 [https://learn.zybooks.com/zybook/PCCCS161BSpring23/chapter/14/section/7]
void addStudent(Student student, Course &course) {
  int i;
  int j;
  
  if(course.numStudents == 20) {
    cout << "Array full!" << endl;
  }
  else {
    bool found = false; //self contained within loop
    for(i = 0; i < course.numStudents && !found; i++){
      int result = strcmp(student.last, course.roster[i].last);
      if(result < 0) {
        for ( int k = course.numStudents; k >i; k--) {
          course.roster[k] = course.roster[k-1];
        }
        course.roster[i] = student;
        found = true;
      }
    }
    if (!found) {
      course.roster[course.numStudents] = student;
    }
  }
  course.numStudents++;
}

//prints a whole Course roster calling student print.
//use a for loop and print all the students
//must call the printStd function in Student.h
void printRoster(Course course)
{
  /*Add your code here*/
  int i;
  for(i = 0; i < course.numStudents; i++) {
    printStd(course.roster[i]);
  }
}

//add code and function comments for the below 2 functions.
//receives the name of a student and the course and removes the student with
//that name from the roster, only if it exist
void dropStudent(char *lastname, Course &course){
  int i;
  int j;
  bool found = false;
  int studentElement;
  
  for (i = 0; i < course.numStudents && !found; i++){
    if (strcmp(lastname,course.roster[i].last) == 0) {
      studentElement = i;
      found = true;
    }
  }

  if(found) {
    for (j = studentElement; j < course.numStudents-1; j++) {
      course.roster[j] = course.roster[j+1];
    }
  }
  course.numStudents--;
}

//goes through roster and returns a student with the highest gpa
Student findStudentHighestGPA(Course course){
  int i;
  double maxGPA = course.roster[0].gpa;
  int elementMaxGPA = 0;
  
  for (i = 0; i < course.numStudents; i++) {
    if (maxGPA < course.roster[i].gpa) {
      maxGPA = course.roster[i].gpa;
      elementMaxGPA = i;
    }
  }
  return course.roster[elementMaxGPA];
}
