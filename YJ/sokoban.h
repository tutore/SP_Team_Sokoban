#ifndef _SOKOBAN_
#define _SOKOBAN_

#define ESC 27
#define LEFT 75
#define RIGHT 77
#define UP 72
#define DOWN 80

#define MAXSTAGE 5 //Stage 갯수
#define MAXSIZE 200

#define putxy(x,y,c) {move(x,y); addch(c);}

char stage[20][20]; //Current Stage
int level = 0; //Current level
int x, y; //Current 캐릭터 위치
int count = 0; //EndPoint 갯수
int walk = 0;
int countdown = 60;

typedef struct point{
	int x;
	int y;
}point;

void PrintTitle();
int PrintStage();
void SetLocation();
void Handler();
void PrintEnding();
void ResetCurrentStage();
void StageTimer(int);
int SetTimer(int);

#endif
