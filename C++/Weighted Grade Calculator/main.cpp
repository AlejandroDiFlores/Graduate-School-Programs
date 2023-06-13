/*****************************************************************************
# Author:           Alejandro Guzman Flores
# Assignment:       Assignment 1
# Date:             04/09/2023
# Description:      This program prompts the user to enter information on
#                   their grades from Assignments and Exam score and then
#                   returns the user's final score and letter grade. 
# Input:            number of assignments (int), assignment scores (double),
#                   midterm score (double), final exame score(double).
# Output:           Error message for values outside desired range, prompts
#                   for number of assignments, and scores for assignments and
#                   the final numeric score and grade, sandwhiched between a
#                   welcome and goodbye message. 
# Sources:          zyBook,  
#****************************************************************************/
#include <iostream>
#include <iomanip> 
#include <cmath>

using namespace std;
//DECLARE constants for weighted scores
const double assignWeighted = 0.6;
const double midtermWeighted = 0.2;
const double finalExamWeighted = 0.2;
//DECLARE FUNCTIONS globally
void welcome();
int readInt(string prompt);
void readScore(string prompt, double& num);
double assignAverage(int numAssigns);
void getInput(double& midtermScore, double& finalScore);
double calcFinalScore(double assignAvg, double midtermScore,
double finalScore);
void calcLetterGrade(double finalScore, char& letter);

//Name:   main()
//Desc:   This function is the starting point for program execution
//input:  None
//output: integer
//return: 0
int main() {
  double midtermScore = 0.0;
  double finalExamScore = 0.0;
  char letterGrade = 'A';
  int numAssigns = 0;
  double avg = 0.0;
  double numericalGrade = 0.0;
  
  welcome();
  cout << endl;
  
  numAssigns = readInt("Enter the number of assignments (0 to 10): ");
  avg = assignAverage(numAssigns);
  cout << endl;
  
  getInput(midtermScore, finalExamScore);
  cout << endl;
  
  numericalGrade = calcFinalScore(avg, midtermScore, finalExamScore);
  calcLetterGrade(numericalGrade, letterGrade);
  cout << "Your Final Grade is " << letterGrade << endl;    
  cout << endl;
  
  cout << "Thank you for using my Grade Calculator!" << endl;
  
  return 0;
}

//Name:   welcome()
//Desc:   This function displays a welcome message
//input:  None
//output: None
//return: None
void welcome() {
  cout << "Welcome to my Final Grade Calculator!" << endl; 
  cout << "Please enter the following information and I will" <<
  " calculate your Final Numerical Grade and Letter Grade for you!" << endl; 
  cout << "The number of assignments must be between 0 and 10." << endl;
  cout << "All scores entered must be between 0 and 4." << endl;
}

//Name:   readInt(string prompt)
//Desc:   This function prompts the user to enter the number of assignments
//input:  1 string
//output: integer
//return: int (numOfAssigns)
int readInt(string prompt) {
  int numAssigns = 0;
  bool assigns = false;
  while (assigns != true) {
    cout << prompt;
    cin >> numAssigns;
    if (cin.fail()) {
      cout << "Illegal Value! Please try again!!" << endl;
      cin.clear();
      cin.ignore(100, '\n');
    }
    else if (numAssigns > 10 || numAssigns < 0 ) {
      cout << "Illegal Value! Please try again!!" <<endl;
    }
    else {
      assigns = true;
    }
  }
  return numAssigns;
}

//Name:   readScore(string prompt, double& num)
//Desc:   This function prompts the user to enter their assignment scores
//input:  1 string, 1 double
//output: None
//return: None
void readScore(string prompt, double& num) {
  bool scores = false;
  while (scores != true) {
    cout << prompt;
    cin >> num;
    if (cin.fail()) {
      cout << "Illegal Score! Please try again!" << endl;
      cin.clear();
      cin.ignore(100, '\n');
    }
    if (num > 4 || num < 0) {
      cout << "Illegal Score! Please try again!" <<endl;
    } 
    else {
      scores = true;
    }
  }
}

//Name:   assignAverage(int numAssigns)
//Desc:   This function collects scores entered and calculates an average
//input:  1 integer
//output: double
//return: double (avg)
double assignAverage(int numAssigns) {
  double total = 0.0;
  double avg = 0.0;
  double score = 0.0;
  string scoreCount = "";
  for(int i = 0; i < numAssigns; i++){
    scoreCount = to_string(i+1);
    readScore(("Enter score " + scoreCount + ": "), score);
    total = total + score;
  }
  avg = total / numAssigns;
  return avg;
}

//Name:   getInput(double& midtermScore, double& finalExamScore)
//Desc:   This function prompts the user to enter exam scores
//input:  2 doubles
//output: None
//return: None
void getInput(double& midtermScore, double& finalExamScore) {
  readScore("Enter your midterm exam score: ", midtermScore);
  readScore("Enter your final exam score: ", finalExamScore);
}

//Name:   calcFinalScore(double assignAvg, double midtermScore, 
//        double finalScore)
//Desc:   This function calculates the final numeric score
//input:  3 doubles
//output: double
//return: double (numerical grade)
double calcFinalScore(double assignAvg, double midtermScore, 
double finalScore) {
  /* To calculate the weighted scores, each type is multiplied by their
  predetermined weight. */
  double numericalGrade = ((assignAvg*assignWeighted) + 
  (midtermScore*midtermWeighted) + (finalScore*finalExamWeighted));
  numericalGrade = round(numericalGrade*10)/10;
  cout << "Your Final Numeric score is " << numericalGrade << endl;
  return numericalGrade;
}

//Name:   calcLetterGrade(double finalScore, char& letter)
//Desc:   This function references the finalScore to a letter grade
//input:  double, char
//output: None
//return: None
void calcLetterGrade(double finalScore, char& letter) {
  if(finalScore >= 3.3 && finalScore <= 4.0) {
    letter = 'A';
  } 
  else if(finalScore >= 2.8 && finalScore < 3.3) {
    letter = 'B';
  } 
  else if(finalScore >= 2.0 && finalScore < 2.8) {
    letter = 'C';
  } 
  else if(finalScore >= 1.2 && finalScore < 2.0) {
    letter = 'D';
  } 
  else if(finalScore >= 0.0 && finalScore < 1.2) {
    letter = 'F';
  }
}
