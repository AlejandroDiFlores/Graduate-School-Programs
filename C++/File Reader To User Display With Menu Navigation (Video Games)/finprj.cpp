//*****************************************************************************
// Author:      Alejandro Flores
// Assignment:  Final project
// Date:        04/22/2023
// Description: This program reads from a file video game stats and creates a 
//              table that can be edited by the user through a series of menus
//              including creating their own top ten list which will be output
//              to a separate file 'My Top Ten.txt'
// Input:       counts, userCounts, gameIndex, gameRating, year, pos, gamePos,
//              numberList, critic and user as ints; sales as a double;
//              menuChoice, userInput, addAnother, mainChoice, title, platform,
//              yN as char
// Output:      pos, year, critic, user as ints; fullTitle, title, platform as
//              char, sales as a double, menuNav, menuLooper, valid, validYesNo
//              badGame, validIndex, validRating, validMain, looper, validPos, 
//              validYN as booleans
// Sources:     GDIyer, Glen Sasek, IGN, Metacritic, Gamespot, Gregory Smith
//              (via Kaggle website), VG Insights
//*****************************************************************************
#include <iostream>
#include <iomanip>
#include <limits>
#include <cctype>
#include <cstring>
#include "DataValidation.h"
#include "VideoGameStats.h"

using namespace std;
const int MAX = 100;
const int USERMAX = 10;

void welcome();
bool menuOption(VideoGames videoGamesMain[], int &counts, VideoGames videoGamesUser[], int &userCounts);
void printListMenu(VideoGames videoGamesMain[], int counts, VideoGames videoGamesUser[], int userCounts);
void printList(VideoGames videoGamesMainList[], int count, bool switchList);
void addGameList(VideoGames videoGamesUser[], int gameIndex, int gamePos);
void removeGameList(VideoGames videoGamesUser[], int gameIndex);
void alterListMenu(VideoGames videoGamesMain[], int &counts, VideoGames videoGamesUser[], int &userCounts);
void alterUserList(VideoGames videoGamesMain[], int &counts, VideoGames videoGamesUser[], int &userCounts);
void addUserList(VideoGames videoGamesUser[], int &userCounts, VideoGames videoGamesMain[], int gameIndex, int gamePos);
void removeUserList(VideoGames videoGamesUser[], int &userCounts, int gameIndex);
void alterMainList(VideoGames videoGamesMain[], int &counts);
void addMainList(VideoGames videoGamesMain[], int &counts);
void removeMainList(VideoGames videoGamesMain[], int &counts);
void addRating(VideoGames videoGamesMain[], int &counts);
void findInfo(VideoGames videoGamesMain[], int counts);
void goodbye(VideoGames videoGamesUser[], int userCounts);


//Name:   main()
//Desc:   This is the starting point for program execution.
//input:  None
//output: None
//return: 0
int main() {
  bool menuNav = true; //Used to loop menu
  int counts = 0; //References videoGamesMain array population
  int userCounts = 0; //References videoGamesUser array population
  VideoGames videoGamesMain[MAX]; //Struct for main list
  VideoGames videoGamesUser[USERMAX]; //Struct for user's personal list
  
  welcome(); 
  //Load VideoGameStats.txt into program
  loadVideoGames(videoGamesMain, counts); 
  
  //Loop main menu until quit is selected which returns false
  while (menuNav == true) {
    menuNav = menuOption(videoGamesMain, counts, videoGamesUser, userCounts);
  } 
  
  //Goodbye message & uploads 'My Top Ten' list if one was created
  goodbye(videoGamesUser, userCounts);
  
  return 0;
}

//Name:   menuOption()
//Desc:   This function provides a menu of options for the user to navigate
//input:  menuChoice as a char
//output: None
//return: menuLooper as a bool
bool menuOption (VideoGames videoGamesMain[], int &counts, VideoGames videoGamesUser[], int &userCounts) {
  bool menuLooper; //Return value for function
  bool valid = false; //Loop menu itself
  char menuChoice; //User input that navigates menu
  
  //Loops menu until a valid menu option is entered (A, B, C, D, or Q)
  while (!valid) {
    cout << "\nSelect an option from the menu below: " << endl;
    cout << "(A) Print a list " << endl;
    cout << "(B) Alter a list " << endl;
    cout << "(C) Add a personal rating " << endl;
    cout << "(D) Find info on a game " << endl;
    cout << "(Q) Quit the program " << endl << endl;

    cin >> menuChoice;
    //Calls to dataValidation.cpp to validate user input
    valid = validateInputMain(menuChoice);
  } 
  //If functions to navigate to proper menu selections
  if (menuChoice == 'a' || menuChoice == 'A'){
    //Calls function to print a list (main or personal)
    printListMenu(videoGamesMain, counts, videoGamesUser, userCounts);
    return menuLooper = true;
  }
  else if (menuChoice == 'b' || menuChoice == 'B'){
    //Calls function to alter a list (main or personal)
    alterListMenu(videoGamesMain, counts, videoGamesUser, userCounts);
    return menuLooper = true;
  }
  else if (menuChoice == 'c' || menuChoice == 'C'){
    //Calls function to add rating to a game in main list
    addRating(videoGamesMain, counts);
    return menuLooper = true;
  }
  else if (menuChoice == 'd' || menuChoice == 'D'){
    //Calls function to pull full info on one game in main list
    findInfo(videoGamesMain, counts);
    return menuLooper = true;
  }
  else if (menuChoice == 'q' || menuChoice == 'Q'){
    //Returns value needed to exit out of main menu
    cout << "\nExiting menu..." << endl;
    return menuLooper = false;
  }
}

//Name:   printListMenu()
//Desc:   This function prints out a list from the VideoGameStats.txt file
//input:  userInput as char
//output: None
//return: None
void printListMenu(VideoGames videoGamesMain[], int counts, VideoGames videoGamesUser[], int userCounts){
  char userInput; //User input to navigate menu
  bool valid = false; //Loops menu until proper selection is made

  //Loops until valid menu choice is entered
  while(!valid) {
    cout << "\nWould you like to print the full list " 
         << "or your top 10 list?" << endl;
    cout << "(A) Print full list " << endl;
    cout << "(B) Print my top 10 list " << endl;
    
    cin >> userInput;
    //Calls to dataValidation.cpp to validate user input
    valid = validateInput(userInput);
  }

  //If functions to navigate menu selections
  if (userInput == 'A' || userInput == 'a') {
    //Calls to print the main list with true bool
    printList(videoGamesMain, counts, true);
  }
  else if (userInput == 'B' || userInput == 'b') {
    //Calls to print the user list with false bool
    printList(videoGamesUser, userCounts, false);
  }
}

//Name:   printList()
//Desc:   This function prints out a list from the VideoGameStats.txt file
//        or it prints out the user list if one was created
//input:  None
//output: FIELDS:#, Title, Platform, Year, Global_Sales, Critic Rate, User Rate
//return: None
void printList(VideoGames videoGamesMain[], int count, bool switchList){
  //If user list isn't built, it will direct user to build one
  if (count == 0) {
    cout << "\nYour list is lacking here." << endl;
    cout << "Select (B) in the main menu to build your list." << endl;
  }
  //Displays header field
  else {
    cout << left << setw(5) << " #";
    cout << left << setw(22) << "       Title";
    cout << left << setw(10) << "Platform";
    cout << left << setw(6) << "Year";
    cout << left << setw(13) << "Sales (mil)";
    cout << left << setw(14) << "Critic Rate";
    cout << left << setw(15) << "User Rate" << endl;
    cout << "___  ____________________  ________  ";
    cout << "____  ___________  ___________   _________" << endl << endl;
    //Displays information of struct from main list
    if (switchList == true) {
      for (int i = 0; i < count; i++) {
        cout << left << setw(5) << videoGamesMain[i].pos;
        cout << left << setw(25) << videoGamesMain[i].title;
        cout << left << setw(7) << videoGamesMain[i].platform;
        cout << left << setw(9) << videoGamesMain[i].year;
        cout << left << setw(14) << videoGamesMain[i].sales;
        cout << left << setw(14) << videoGamesMain[i].critic;
        cout << left << setw(12) << videoGamesMain[i].user << endl;
      } 
    } 
    //Display information of struct from user list
    else if (switchList == false) {
      for (int i = 0; i < 10; i++) {
        cout << left << setw(5) << videoGamesMain[i].pos;
        cout << left << setw(25) << videoGamesMain[i].title;
        cout << left << setw(7) << videoGamesMain[i].platform;
        cout << left << setw(9) << videoGamesMain[i].year;
        cout << left << setw(14) << videoGamesMain[i].sales;
        cout << left << setw(14) << videoGamesMain[i].critic;
        cout << left << setw(12) << videoGamesMain[i].user << endl;
      }  
    }   
  }
}

//Name:   addRating()
//Desc:   This function adds a user rating to a game in the main list
//input:  addAnother as a char
//output: None
//return: None
void addRating(VideoGames videoGamesMain[], int &counts){
  bool valid = true; //Loops entire function
  bool validYesNo = false; //Loops iteration to rate another game
  bool badGame = false; //Used if a game is rated zero
  bool validIndex = false; //Loops until valid index is entered
  bool validRating = false; //Loops until valid rating is entered
  char addAnother; //User input to navigate loop
  int gameIndex; //User input to select index from main list
  int gameRating; //User input to enter a game rating

  //Loops whole function
  while(valid == true) {
    //resets entire bool, in order to loop properly
    validYesNo = false;
    badGame = false;
    validIndex = false;
    validRating = false;

    //Calls function to print main list
    printList(videoGamesMain, counts, true);
    
    cout << "\nSelect the number of which game you want to add a rating to." << endl;

    //Loops until valid game index is selected
    while (validIndex == false) {
      cin >> gameIndex;
      if (gameIndex > counts){
        cout << "Please enter a number from the list." << endl;
      }
      else {
        validIndex = validateInput(gameIndex);
      }
    }

    //Translates user input to valid array component
    gameIndex = gameIndex -1;
    
    cout << "\nWhat do you rate " << videoGamesMain[gameIndex].fullTitle << " out of 100?" << endl;

    //Loops until valid rating is entered
    while (validRating == false) {
      cin >> gameRating;
      if (!cin) {
        cout << "\nPlease enter an integer." << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');   
      }
      else if (gameRating == 0) {
        badGame = true;
        validRating = true;
      }
      else if (gameRating > 100) {
        cout << "\nPlease enter a number between 0 and 100. " << endl;
      }
      else {
        validRating = validateInput(gameRating);
      }
    }

    //If functions to enter the correct rating into main list
    if (badGame == true) {
      videoGamesMain[gameIndex].user = 0;
    }
    else {
      videoGamesMain[gameIndex].user = gameRating;
    }
    
    cout << "\nYou've rated " << videoGamesMain[gameIndex].fullTitle << " a " << gameRating << "/100." << endl;
    cout << "\nWould you like to rate another game? (y/n)" << endl;

    //Loops until proper selection is made to rate another game or not
    while (validYesNo == false) {
      cin >> addAnother;   
      if (addAnother == 'Y' | addAnother == 'y') {
        valid = true;
        validYesNo = true;
      }
      else if (addAnother == 'N' || addAnother == 'n') {   
        valid = false;
        validYesNo = true;
      }
      else {
        cout << "\nPlease enter y or n." << endl;
      }
    }
  }
}

//Name:   alterListMenu()
//Desc:   This function presents a menu for the user to alter the main or personal list
//input:  menuChoice and mainChoice as char
//output: None
//return: None
void alterListMenu(VideoGames videoGamesMain[], int &counts, VideoGames videoGamesUser[], int &userCounts){
  bool menuLooper = false; //Loops whole function
  bool valid = false; //Loops selection until main or personal list is selected
  bool validMain = false; //Loops menu choice for eithe rmain or personal list
  char menuChoice; //User input for main menu selection
  char mainChoice; //User input for main or personal list selection

  //Loops whole function
  while (menuLooper == false){
    //Resets valid for proper looping function
    valid = false;
    //Loops until proper menu selection is made
    while (valid == false) {
      cout << "\nWhich list do you wish to alter?" << endl;
      cout << "\n(A) Main List" << endl;
      cout << "(B) Personal List" << endl;
      
      cin >> menuChoice;
      valid = validateInput(menuChoice);
    }

    //If functions to determine which menu choice was made
    if(menuChoice == 'A' || menuChoice == 'a') {
      cout << "\nDo you want to add or remove from the main list?: " << endl;
      cout << "\n(A) Add to main list" << endl;
      cout << "(B) Remove from main list" << endl;

      //Loops until proper menu choice is made from main list
      while (validMain == false) {
        cin >> mainChoice;
        
        //If functions to determine which menu choice was made
        if (mainChoice == 'A' || mainChoice == 'a') {
          //Calls function to add to main list
          addMainList(videoGamesMain, counts);
          validMain = true;
        }
        else if (mainChoice == 'B' || mainChoice == 'b') {
          //Calls functions to print list to choose from in main and to remove from that list
          printList(videoGamesMain, counts, true);
          removeMainList(videoGamesMain, counts);
          validMain = true; 
        }
        else {
          cout << "Please select A or B" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');     
        }
      }
      validMain = false;
    }
      
    else if(menuChoice == 'B' || menuChoice == 'b'){
      //Calls function to alter user list
      alterUserList(videoGamesMain, counts, videoGamesUser, userCounts);
    }
  
    cout << "\nDo you want to: " << endl;
    cout << "\n(A) Alter another list" << endl;
    cout << "(B) Return to main menu" << endl;
    cin >> menuChoice;

    //If functions to determine menu choice, to return to main menu or to run function again
    if (menuChoice == 'A' || menuChoice == 'a') {
      menuLooper = false;
    }
    else if (menuChoice == 'B' || menuChoice == 'b') {
      menuLooper = true;
    }
    else {
      cout << "\nInvalid response. Please enter A or B." << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');     
    }
  } 
}  

//Name:   addMainList()
//Desc:   This function adds a game to the main list
//input:  FIELDS for struct by user as char, int, and double
//output: None
//return: None
void addMainList(VideoGames videoGamesMain[], int &counts){
  //Fields for struct
  char title[50];
  char platform[5];
  int year;
  double sales;
  double critic;
  double user;
  
  bool valid = false; //Used to loop user entries until valid selection is entered
  
  cout << "\nTo add a game to this list, answer the following questions:" << endl;
  cout << "\nEnter the title of the game. (Capitalize the start of each word):" << endl;
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get(title, 50, '\n');
  strncpy(videoGamesMain[counts].title, title, 20);
  strcpy(videoGamesMain[counts].fullTitle, title);
  
  cout << "\nEnter the platform " << videoGamesMain[counts].fullTitle << " released on. "
       << "(if released on multiple platforms, select only one):" << endl;
  cin.clear();
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  cin.get(platform, 5, '\n');
  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  strcpy(videoGamesMain[counts].platform, platform);
  
  cout << "\nEnter the year it was released: " << endl;
  while (valid == false) {
    cin >> year;
    if(!cin) {
      cout << "\nPlease enter a valid year: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');     
    }
    else if (year < 0) {
      cout << "\nPlease enter a valid year: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');    
    }
    else {
      videoGamesMain[counts].year = year;
      valid = true;
    }
  }
  //Reset bool for each data entry by user
  valid = false;
  
  cout << "\nEnter how many units were sold in millions (ex: 82.74): " << endl;
  while (valid == false){
    cin >> sales;
    if(!cin || sales <0) {
      cout << "\nPlease enter a valid amount: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
      videoGamesMain[counts].sales = sales;
      valid = true;
    }
  }
  valid = false;
  
  cout << "\nEnter the rating " << videoGamesMain[counts].title << " received from critics"
       << " out of 100. (IGN, Metacritic, or Gamespot are critics) : " << endl;
    while (valid == false){
    cin >> critic;
    if(!cin || critic <0 || critic > 100) {
      cout << "\nPlease enter a valid rating: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
      videoGamesMain[counts].critic = critic;
      valid = true;
    }
  }
  valid = false;
  
  cout << "\nEnter your own rating of the game out of 100: " << endl;
    while (valid == false){
    cin >> user;
    if(!cin || user <0 || user > 100) {
      cout << "\nPlease enter a valid amount: " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
      videoGamesMain[counts].user = user;
      valid = true;
    }
  }
  counts++;
  videoGamesMain[counts-1].pos = counts;
  valid = false;
}

//Name:   removeMainList()
//Desc:   This function removes a game from the main list
//input:  pos as int
//output: None
//return: None
void removeMainList(VideoGames videoGamesMain[], int &counts){
  bool valid = false; //Loops user input of pos until valid entry
  int pos = 0; //Pos relating to main list index
  int bucket = 0; //to reset index number displayed
  
  cout << "\nSelect a number from the list of which game you'd like to remove:" << endl;
  //Loops until valid entry of pos
  while (valid == false) {
    cin >> pos;
    //Reduce pos in order to relate to proper index of array
    pos--;
    
    if (!cin) {
      cout << "\nPlease enter an item off the list:" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else if (pos == 0) {
      for (int i = 0; i < counts-1; i++) {
        bucket = videoGamesMain[i].pos;
        videoGamesMain[i] = videoGamesMain[i+1];
        videoGamesMain[i].pos = bucket;
      }
      counts--;
      videoGamesMain[counts].pos = 0;
      strcpy(videoGamesMain[counts].fullTitle, " ");
      strcpy(videoGamesMain[counts].title, " ");
      strcpy(videoGamesMain[counts].platform, " ");
      videoGamesMain[counts].year = 0;
      videoGamesMain[counts].sales = 0;
      videoGamesMain[counts].critic = 0;
      videoGamesMain[counts].user = 0;
      valid = true;
    }
    else if (pos < 0 || pos > counts-1) {
      cout << "\nPlease enter an item off the list:" << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    else {
      for (int i = pos; i < counts-1; i++) {
        videoGamesMain[i] = videoGamesMain[i+1];
      }
      counts--;
      videoGamesMain[counts].pos = 0;
      strcpy(videoGamesMain[counts].fullTitle, " ");
      strcpy(videoGamesMain[counts].title, " ");
      strcpy(videoGamesMain[counts].platform, " ");
      videoGamesMain[counts].year = 0;
      videoGamesMain[counts].sales = 0;
      videoGamesMain[counts].critic = 0;
      videoGamesMain[counts].user = 0;
      valid = true;
    }
  }
}

//Name:   alterUserList()
//Desc:   This function presents a menu selection to add or remove from the user list
//input:  menuChoice and yN as char
//output: None
//return: None
void alterUserList(VideoGames videoGamesMain[], int &counts, VideoGames videoGamesUser[], int &userCounts){
  //Booleans to loop menu
  bool looper = false;
  bool valid = false;
  bool validIndex = false;
  bool validPos = false;
  bool validYN = false;
  
  char menuChoice; //Menu choices
  char yN; // Y or N menu choices
  int gameIndex; //Index from main list to choose
  int gamePos; //Pos to add to personal list
  
  cout << "\nHere's a list of games available to choose from: " << endl;
  
  //Print main list with true
  printList(videoGamesMain, counts, true);
  cout << "\nYour list is as follows: " << endl;

  //If user list isn't built it will display empty, other wise it displays list
  if (userCounts == 0) {
    cout << "Empty." << endl;
  }
  else {
    cout << endl;
    //Print user list
    printList(videoGamesUser, userCounts, false);
  }

  //Loops menu 
  while (looper == false) {
    //Resets bools to function properly
    looper = false;
    valid = false;
    validIndex = false;
    validPos = false;
    validYN = false;
    
    cout << "\nDo you want to add or remove from your list?" << endl;
    cout << "\n(A) Add to my list" << endl;
    cout << "(B) Remove from my list" << endl;

    //Loops menu selection until valid response
    while (valid == false) {
      cin >> menuChoice;
      valid = validateInput(menuChoice);
    }

    //If function to navigate menu
    if (menuChoice == 'a' || menuChoice == 'A') {
      cout << "\nSelect the number of which game you would like to add." << endl;
      //Loops until valid game is chosen from main list
      while (validIndex == false) {
        cin >> gameIndex;
        validIndex = validateInput(gameIndex);
      }
      
      cout << "\nEnter the number you would like to rank this out of ten." << endl;
      //Loops until valid position out of ten is entered
      while (validPos == false) {
        cin >> gamePos;
        if (!cin) {
          cout << "\nPlease enter a valid number (1-10): " << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else if (gamePos > 10 || gamePos < 0) {
          cout << "\nPlease enter a number within range (1-10):" << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        else {
          validPos = validateInput(gamePos);
        }
      }

      //Calls function to add to user list
      addUserList(videoGamesUser, userCounts, videoGamesMain, gameIndex, gamePos);
      cout << endl;
      printList(videoGamesUser, userCounts, false);
      
      cout << "\nIf you'd like to continue editing? (y/n)" << endl;
      //Loops to verify valid option of y or n
      while (validYN == false) {
        cin >> yN;
        if (yN == 'y' || yN == 'Y') {   
          validYN = true;
        }
        else if (yN == 'n' || yN == 'N') {
          validYN = true;
          looper = true;
        }
        else {
          cout << "Invalid response. Enter y or n." << endl;
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');     
          validYN = false;
        }
      }
    }

    //If function to remove from user list if populated, with data validation akin to previous if function
    if (menuChoice == 'b' || menuChoice == 'B') {
      if (userCounts == 0) {
        cout << "Your list is empty. There is nothing to remove." << endl;
      }
      else {
        cout << "\nSelect the number of the game you would like to remove from"
             << " your list." << endl;
        while(validPos == false) {
          cin >> gamePos;
          if (gamePos < 11 && gamePos >= 0) {
            validPos = validateInput(gamePos);
          }
          else {
            cout << "\nPlease enter a number in range." << endl;
          }
        }
        removeUserList(videoGamesUser, userCounts, gamePos);
        cout << endl;
        printList(videoGamesUser, userCounts, false);
        cout << "\nIf you'd like to continue editing? (y/n)" << endl;
        
        while (validYN == false) {
          cin >> yN;
          if (yN == 'y' || yN == 'Y') {   
            validYN = true;
          }
          else if (yN == 'n' || yN == 'N') {
            validYN = true;
            looper = true;
          }
          else {
            cout << "Invalid response. Enter y or n." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');     
            validYN = false;
          }
        }
      }
    }
  }
}

//Name:   findInfo()
//Desc:   This function displays info on one game from the main list
//input:  
//output: None
//return: None
void findInfo(VideoGames videoGamesMain[], int counts){
  int numberList = 0; //Selects number from main list
  bool valid = false; //Loops until valid choice is made
  
  cout << "\nEnter the number of which game you want more info on: " << endl;
  //Loops until valid number form list is made
  while (valid == false) {
    cin >> numberList;
    if (numberList > 0 && numberList <= counts) {
      valid = validateInput(numberList);
    }
    else {
      cout << "\nPlease select a number from the list. " << endl;
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');     
    }
  }
  //Reduce user entry numberList to relate to index of array
  numberList--;
  //Pulls info from struct to displaly for user
  cout << "\n";
  cout << "Title: " << videoGamesMain[numberList].fullTitle << endl;
  cout << "Platform: " << videoGamesMain[numberList].platform << endl;
  cout << "Year: " << videoGamesMain[numberList].year << endl;
  cout << "Sales: " << videoGamesMain[numberList].sales << endl;
  cout << "Critic Ratings: " << videoGamesMain[numberList].critic << endl;
  
  //If no rating was fulfilled for game, instructions on adding rating are relayed to user
  if (videoGamesMain[numberList].user == 0) {
    cout << "You have not rated this game." << endl;
    cout << "You can add a rating by selecting (C) in the main menu." << endl;
  }
  else {
    cout << "User Rating: " << videoGamesMain[numberList].user << endl;
  }
}

//Name:   addUserList()
//Desc:   This function adds a game to the user list by ranking
//input:  gamePos and gameIndex as ints
//output: None
//return: None
void addUserList(VideoGames videoGamesUser[], int &userCounts, VideoGames videoGamesMain[], int gameIndex, int gamePos){
  //Reduce to relate displayed number to index of struct
  gamePos = gamePos-1;
  //reduce to relate displayed number to index of struct
  gameIndex = gameIndex-1;
  //Relating position back to user list index
  videoGamesUser[gamePos].pos = gamePos+1;
  //Copies values entered from main list to user list
  strcpy(videoGamesUser[gamePos].fullTitle, videoGamesMain[gameIndex].fullTitle);
  strcpy(videoGamesUser[gamePos].title, videoGamesMain[gameIndex].title);
  strcpy(videoGamesUser[gamePos].platform, videoGamesMain[gameIndex].platform);
  videoGamesUser[gamePos].year = videoGamesMain[gameIndex].year;
  videoGamesUser[gamePos].sales = videoGamesMain[gameIndex].sales;
  videoGamesUser[gamePos].critic = videoGamesMain[gameIndex].critic;
  videoGamesUser[gamePos].user = videoGamesMain[gameIndex].user;
  userCounts++;
}

//Name:   removeUserList()
//Desc:   This function removes an entry from the user list
//input:  None
//output: None
//return: None
void removeUserList(VideoGames videoGamesUser[], int &userCounts, int gameIndex){
  //If function to determine if values entered into function are within range
  if(videoGamesUser[gameIndex].pos < 0 || videoGamesUser[gameIndex].pos > 10) {
    cout << "\nThis is outside the list of 10." << endl;
  }
  else {
    //Reset gameIndex to relate to array index 
    gameIndex = gameIndex-1;
    //If functions to determine if a game can be removed
    if (videoGamesUser[gameIndex].pos == 0) {
      cout <<"\nThere is no game here to remove." << endl;
    }
    else {
      videoGamesUser[gameIndex].pos = 0;
      strcpy(videoGamesUser[gameIndex].fullTitle, " " );
      strcpy(videoGamesUser[gameIndex].title, " ");
      strcpy(videoGamesUser[gameIndex].platform," ");
      videoGamesUser[gameIndex].year = 0;
      videoGamesUser[gameIndex].sales = 0;
      videoGamesUser[gameIndex].critic = 0;
      videoGamesUser[gameIndex].user = 0;
      if(videoGamesUser[gameIndex].pos == 0) {
        userCounts++;
      }
      userCounts--;      
    }
  }
}

//Name:   welcome()
//Desc:   This function greets the user and preludes the program
//input:  None
//output: prompt
//return: None
void welcome() {
  cout << "Greetings! This program will read input from a file containing " 
       << "a list of video games and information pertaining to those games. " 
       << "This includes sales a well as reviews from critics. A series of "
       << "options will be presented to the user via a menu. " << endl;
}

//Name:   goodbye()
//Desc:   This function alerts the user that the program is ending and exports user list to 'My Top Ten.txt' if it was populated
//input:  None
//output: None
//return: None
void goodbye(VideoGames videoGamesUser[], int userCounts) {
  cout << "\nThank you for using my program!" << endl;
  //Checks if user list was populated, if so, then outputs to file
  if (userCounts > 0) {
    cout << "\nUploading top 10 list to file: 'My Top Ten' " << endl;
    uploadFile(videoGamesUser, userCounts);
  }
  cout << "\nTerminating program... " << endl; 
  cout << "See you next time space cowboy..." << endl;
}