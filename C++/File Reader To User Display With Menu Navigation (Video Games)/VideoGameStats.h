#ifndef VIDEOGAMESTATS_H
#define VIDEOGAMESTATS_H

#include <fstream>
using namespace std;

const int STRUCTMAX = 50;

struct VideoGames {
  int pos;
  char fullTitle[STRUCTMAX];
  char title[STRUCTMAX];
  char platform[STRUCTMAX];
  int year;
  double sales;
  int critic;
  int user;
};

bool openFile(ifstream& infile, string fileName);
void loadVideoGames(VideoGames videoGamesMain[], int &counts);
void updateUserList(ofstream& outfile, VideoGames videoGamesUser);
void uploadFile(VideoGames videoGamesMain[], int userCounts);

#endif