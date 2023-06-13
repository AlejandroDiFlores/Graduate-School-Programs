//*****************************************************************************
// Author: Alejandro Flores & Danielle Moreno,
// Assignment: Discussion 2
// Date: 04/15/2023
// Description: This program will generate a password for the user
// Input:
// Output:
// Sources: zyBook, Glen Sasek
//*****************************************************************************
#include <cctype>
#include <cstring>
#include <iostream>
#include <limits>

using namespace std;

const int maxPhrase = 20;
const int maxYears = 4;
const int maxPass = maxPhrase + maxYears + 1; // 1 for symbol

const char passwordIs[] = "Your strong password is: ";

// Read a character repeat until in range.
char getCharacterInRange(char low, char high);

void generatePassword(char phrase[], char year[], char symbol, char password[]);

int main() {
  char phrase[maxPhrase + 1]; // Plus 1 for null terminator.
  char year[maxYears + 1];
  char symbol;
  char password[maxPass + 1];

  cout << "Enter phrase or word: " << endl;
  cin.getline(phrase, maxPhrase);
  cout << "Enter year or number (max limit of 4): " << endl;
  for (int i = 0; i < maxYears; i++) {
    year[i] = getCharacterInRange('0', '9');
  }
  year[maxYears] = '\0';

  cin.ignore(numeric_limits<streamsize>::max(), '\n');
  
  cout << "Enter a single unique symbol: " << endl;
  symbol = cin.get();

  generatePassword(phrase, year, symbol, password);

  cout << passwordIs << password;

  return 0;
}

void generatePassword(char phrase[], char year[], char symbol,
                      char password[]) {
  int i = -1;
  do {
    i++;
    password[i] = phrase[i];
  } while (i < strlen(phrase) && !isspace(phrase[i]));

  password[i] = '\0';

  strcat(password, year);

  i = strlen(password);

  password[i] = symbol;
  password[i + 1] = '\0';
}

char getCharacterInRange(char low, char high) {
  char c = '\0';
  do {
    c = cin.get();
  } while (c < low || c > high);
  return c;
}