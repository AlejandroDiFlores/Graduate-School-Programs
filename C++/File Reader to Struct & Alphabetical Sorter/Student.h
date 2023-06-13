//The student struct
#ifndef STUDENT_H_
#define STUDENT_H_

struct Student {
	char first[20] = {0};
	char last[20] = {0};
	double gpa = 0.0;
};

//Function Prototypes
Student initStudent(char *first, char *last, double gpa);
void getLastName(char *studentName, Student student);
double getGPA(Student student);
void printStd(Student student);

#endif