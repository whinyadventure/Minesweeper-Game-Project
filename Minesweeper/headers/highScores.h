#include <stdio.h>
#pragma once
#define INFO_X 340
#define INFO_Y 30

struct LoadedData {
	int time;
	char nickname[10];
};

LoadedData* loadData(int);
void printScores(int, int);
void saveData(LoadedData*);
void sortScores(LoadedData*, char[], int);
void highScoresLoop();
int getDiffLvl();
bool isEmpty(FILE*);
void nullTheStructArr(LoadedData*);