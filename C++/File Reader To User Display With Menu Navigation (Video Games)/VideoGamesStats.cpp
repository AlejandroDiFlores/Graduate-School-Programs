#include "VideoGameStats.h"
#include <fstream>
#include <iostream>
#include <limits>
#include <iomanip>

//Name:   openFile()
//Desc:   This function opens a file for input and alerts user if there was an error
//input:  None
//output: None
//return: bool true or false
bool openFile(ifstream& infile, string fileName){
  infile.open(fileName);
  if (!infile) {
    return false;
  }
  return true;
}

//Name:   loadVideoGames()
//Desc:   This function opens a file and loads it into a struct
//input:  None
//output: None
//return: None
void loadVideoGames(VideoGames videoGamesMain[], int &counts){
  ifstream inFile;
  bool willLoad = openFile(inFile, "VideoGameStats.txt");
  int secondCount = 0;
  int removal = 0;

  if (willLoad == true) {
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    //does not reach end of file 
    while(!inFile.eof() && counts < 50){
      inFile >> videoGamesMain[counts].pos;
      inFile.clear();
      inFile.ignore(numeric_limits<streamsize>::max(), ';'); 

      inFile.get(videoGamesMain[counts].title, 20, ';');
      inFile.ignore(numeric_limits<streamsize>::max(), ';'); 
      
      inFile.get(videoGamesMain[counts].platform, 5, ';');
      inFile.ignore(numeric_limits<streamsize>::max(), ';');
      
      inFile >> videoGamesMain[counts].year;
      inFile.clear();
      inFile.ignore(numeric_limits<streamsize>::max(), ';');
      
      inFile >> videoGamesMain[counts].sales;
      inFile.clear();
      inFile.ignore(numeric_limits<streamsize>::max(), ';');
      
      inFile >> videoGamesMain[counts].critic;
      inFile.clear();
      inFile.ignore(numeric_limits<streamsize>::max(), ';');
      
      inFile >> videoGamesMain[counts].user;
      inFile.clear();
      inFile.ignore(numeric_limits<streamsize>::max(), '\n');

      counts++;
    }
    inFile.clear();
    inFile.seekg(0);
    inFile.ignore(numeric_limits<streamsize>::max(), '\n');
    while(!inFile.eof() && secondCount < 50){
      inFile >> removal;
      inFile.ignore(numeric_limits<streamsize>::max(), ';');
      inFile.get(videoGamesMain[secondCount].fullTitle, 50, ';');
      inFile.ignore(numeric_limits<streamsize>::max(), '\n');
      secondCount++;
    }
  }
  inFile.close();
}

//Name:   uploadFile()
//Desc:   This function outputs user list to 'My Top Ten.txt' file
//input:  None
//output: None
//return: None
void uploadFile(VideoGames videoGamesUser[], int userCounts){
  ofstream outFS;
  int counts = userCounts;

  outFS.open("My Top Ten.txt");
  
  if (!outFS.is_open()){
    cout << "File could not be opened." << endl;
  }
    
  else {
    outFS << left << setw(5) << " #";
    outFS << left << setw(22) << "       Title";
    outFS << left << setw(10) << "Platform";
    outFS << left << setw(6) << "Year";
    outFS << left << setw(13) << "Sales (mil)";
    outFS << left << setw(14) << "Critic Rate";
    outFS << left << setw(15) << "User Rate" << endl;
    outFS << "___  ____________________  ________  ";
    outFS << "____  ___________  ___________   _________" << endl << endl;

    for (int i = 0; i < 10; i++) {
      outFS << left << setw(5) << videoGamesUser[i].pos;
      outFS << left << setw(25) << videoGamesUser[i].title;
      outFS << left << setw(7) << videoGamesUser[i].platform;
      outFS << left << setw(9) << videoGamesUser[i].year;
      outFS << left << setw(14) << videoGamesUser[i].sales;
      outFS << left << setw(14) << videoGamesUser[i].critic;
      outFS << left << setw(12) << videoGamesUser[i].user << endl;
    }
  }
  outFS.close();
}