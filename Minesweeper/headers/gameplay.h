#pragma once

void setGameplayDisplay(int&, int&);
void showMineCounter(int&, int);
void showTime(int&);
void gameplayLoop();
int computeColumn(int, int&);
int computeRow(int, int&);
int computeX(int, int&);
int computeY(int, int&);
void nullFlagArr(Position*);
bool isInFlagArr(Position* , int&, int&);
bool leftButtonDown(Matrix**, Position*, int, int, int&, int&);
void markSpot(Matrix**, Position*, int, int, int&, int&, int&);
void gameOver(Position *flag_Arr, Matrix**, int, int, int&, int&);
bool checkIfGameWin(Matrix**, Position*, int&, int&);
bool leftButtomUp(Position*, Matrix**, int, int, int&, int&);
void recursiveUncovering(Matrix**, Position*, int, int, int&, int&);
void checkCell(Matrix**, Position*, int, int, int&, int&);
int loadSquare(Matrix**, int, int);