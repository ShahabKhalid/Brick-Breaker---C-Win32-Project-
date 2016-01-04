//================================================================================================
//												INCLUDES
//================================================================================================
#include <windows.h>
#include <pThread.h>
#include <stdio.h>
#include <stdlib.h>
#include "resource.h"
//================================================================================================
//												DEFINES
//================================================================================================
#define MAXBRICKS					40

#define NORMBRICK					121
#define SOLIDBRICK					122
#define EXSOLIDBRICK				123




//================================================================================================
//										   Variable & Structs 
//================================================================================================
HINSTANCE g_hInst;
bool Start = false;
int Menu = 2;
pthread_t ballMovement;
HWND g_hwnd;
char ballDir[5] = "up";
int bAngle = 0;
int bSpeed = 3;
int brickSpeed = 25;
int cBricks;
int countbShows = 0;
int level = 0;
int menuSpos[2] = {300,350};
int menuSelect = 0;
bool brickMag = false;
int bonus[3] = {0,0,0};
bool GameOver = false;
bool keyNotice = 0;
int score = 0;
int spcontler = 0;
//tmp
int del = 0;


int bHits[3][2] = {
	{ NORMBRICK, 1 },
	{ SOLIDBRICK, 3 },
	{ EXSOLIDBRICK, 5 } };
//================================================================================================
//											   OWN STRUCTS
//================================================================================================
struct sBrick
{
	int startX;
	int startY;
	int endX;
	int endY;
	int hide;
} brick = {600,780,650,780,false};




struct sBricks
{
	int left;
	int top;
	int right;
	int bottom;
	int type;
	bool show;
	int hits;
} bricks[MAXBRICKS];


struct sball
{
	int left;
	int top;
	int right;
	int bottom;
} ball = {620,765,630,775};



//================================================================================================
//											FUNCTION DECLERATION
//================================================================================================
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void moveBrick(char dir[]);
void *moveBall(void *);
bool bCollideWithpBrick();
void bCollideWithSideWalls();
void bCollideWithBricks();
void resetLevel();
bool loadLevel(char[]);
bool changeLevel(char[]);
void b_fscanf(char str[],sBricks &);
//================================================================================================
//												EXTRA FUNCTIONS
//================================================================================================


int getrand(int min,int max)
{
	return (rand() % (max+1-min))+min;
}