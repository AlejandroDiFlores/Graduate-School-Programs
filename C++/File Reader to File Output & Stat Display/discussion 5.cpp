/******************************************************************************
# Author:           Alejandro Flores, Kyle Carlson, Sam Wilson
# Lab:              Discussion #5
# Date:             May 14, 2023
# Description:      This program reads from stem.txt file and calculates the 
                    percentage of men and women in the fields of Engineering, 
                    Biology, and Health. Then the program outputs the 
                    percentages into stemout.txt file and closes the file.
# Input:            stem.txt
# Output:           stemout.txt
# Sources:          Zybooks
#******************************************************************************/
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

//function prototypes
bool openFile(ifstream& inFile, string fileName);
void ratioCalc(ifstream& inFile);
void goodbye();
void majorComparison(ifstream& inFile);


//Name:   main()
//Desc:   This function is the starting point for program execution
//input:  stem.txt 
//output: prompt
//return: 0;
int main()
{
  ifstream inFile;
	string fileName = "stem.txt";
	if (!openFile(inFile, fileName)){
		cout << "\nfile did not open. Program terminating!!!" << endl;
		return 0;
	}
  else {
    cout << "\n...reading from file..." << endl;
  }
	ratioCalc(inFile);
  majorComparison(inFile);
	inFile.close();
  //CALL goodbye() function
  goodbye();
}

//Name:   openFile(ifstream& inFile, string fileName)
//Desc:   Opens txt file and returns true or false depending on if there were
//        any errors opening the file or not.
//input:  text file
//output: None
//return: true or false bool
bool openFile(ifstream& inFile, string fileName){
	inFile.open(fileName);
	if (!inFile.is_open()){
		return false;
	}
  else {
    return true;
  }
}

//Name:    ratioCalc(ifstream& inFile)
//Desc:    Calculates the % of men & women in each major and writes the name
//         of the major, the % of men & % of women and outputs it to the
//         stemout.txt
//input:   text file
//output:  
//return:  None
void ratioCalc(ifstream& inFile){
  //declare variables
  string major = " ";
  int intDiscard = 0;
  string strDiscard = " ";
  ofstream outFS;
  int total = 0;
  int men = 0;
  int women = 0;
  //open stemout.txt file
  outFS.open("stemout.txt");
  
  //ignore the first row of text file
  inFile.ignore(200, '\n');
 
  //calculate stats by major
  while(!inFile.eof()){
    inFile >> intDiscard >> major >> strDiscard >> total >> men >> women 
           >> intDiscard;
    outFS << fixed << setprecision(2);
    outFS << major << ": " << total << " students" << endl;
    outFS << "     Percentage of men  : " 
          << (static_cast<double>(men)/static_cast<double>(total))*100.00 
          << "%" << endl;
    outFS << "     Percentage of women: " 
          << (static_cast<double>(women)/static_cast<double>(total))*100.00 
          << "%" << endl;
  }
  
  //close stem.out.txt file
  outFS.close();
  //reset input file back to beginning to run next function
  inFile.clear();
  inFile.seekg(0);
}

//Name:    majorComparison(ifstream& inFile)
//Desc:    This will calculate the difference in men & women who have
//         enrolled in a major category and output that into the steamout.txt
//input:   file txt
//output:  menPerEng, womenPerEng, menPerLife, womenPerLife, menPerHealth and
//         womenPerHealth as doubles
//return:  None
void majorComparison(ifstream& inFile){
  //declare variables
  int men = 0; //to categorize men from file
  int women = 0; // to categorize women from file
  int totalStudents = 0; // to categorize total of men & women
  int engMen = 0; // amount of men with engineering majors
  int engWomen = 0; //amount of women with engineering majors
  int lifeMen = 0; //amount of men with Biology-And-Life science majors
  int lifeWomen = 0;//amount of women with Biology-And-Life science majors
  int healthMen = 0; // amount of men with Health majors
  int healthWomen = 0; // amount of women with Health majors
  int totalEng = 0; //total count of men and women with Engineering majors
  int totalLife = 0; //total count of men and women with Bio-n-life sci majors
  int totalHealth = 0; //total count of men and women with Health majors
  double menPerEng = 0.0; //percent of men with Engineering majors
  double womenPerEng = 0.0; //percent of women with Engineering majors
  double menPerLife = 0.0; //percent of men with Bio-n-life sci majors
  double womenPerLife = 0.0; //percent of women with Bio-n-life sci majors
  double menPerHealth = 0.0; //percent of men with Health majors
  double womenPerHealth = 0.0; //percent of women with Health majors
  string majorCat; //there are 24 majors but only 3 major cats
  int intDiscard = 0;
  string strDiscard;
  ofstream outFS;
  //open stemout.txt file
  outFS.open("stemout.txt",ios_base::app);
  
  //ignore the first row of text file
  inFile.ignore(200, '\n');
  
  //use if functions to tally up totals per category
  while (!inFile.eof()){
    //read only relevant info to gather for output
    inFile >> intDiscard >> strDiscard >> majorCat >> intDiscard >> men 
           >> women >> intDiscard;
    if(majorCat == "Engineering") {
      engMen = engMen + men;
      engWomen = engWomen + women;
    }
    else if(majorCat == "Biology-And-LifeScience"){
      lifeMen += men;
      lifeWomen += women;
    }
    else if(majorCat == "Health") {
      healthMen += men;
      healthWomen += women;
    }
  }

  //calculate stats by major
  totalEng = engMen + engWomen;
  totalLife = lifeMen + lifeWomen;
  totalHealth = healthMen + healthWomen;
  totalStudents = totalEng + totalLife + totalHealth;
  menPerEng = (static_cast<double>(engMen)/
               static_cast<double>(totalEng))*100.0;
  womenPerEng = (static_cast<double>(engWomen)/
                 static_cast<double>(totalEng))*100.0;
  menPerLife = (static_cast<double>(lifeMen)/
                static_cast<double>(totalLife))*100.0;
  womenPerLife = (static_cast<double>(lifeWomen)/
                  static_cast<double>(totalLife))*100.0;
  menPerHealth = (static_cast<double>(healthMen)/
                  static_cast<double>(totalHealth))*100.0;
  womenPerHealth = (static_cast<double>(healthWomen)/
                    static_cast<double>(totalHealth))*100.0;
  
  outFS << "_________________________________________________________" << endl;
  outFS << "Major Category " << "% of Men " << "% of Women" << endl;
  outFS << "Engineering " << menPerEng << "% " << womenPerEng << "%" << endl;
  outFS << "Biology-And-LifeScience "<< menPerLife << "% " << womenPerLife
       << "% " << endl;
  outFS << "Health " << menPerHealth << "% " << womenPerHealth << "%" << endl;
  //close stem.out.txt file
  outFS.close();
}

//Name:    goodbye()
//Desc:    Alerts the user that the program has ended.
//input:   None.
//output:  Prompt.
//return:  None.
void goodbye(){
  cout << "\nThank you for using our program!" << endl;
  cout << "Terminating program..." << endl << "See you space cowboy..." 
       << endl; 
}

