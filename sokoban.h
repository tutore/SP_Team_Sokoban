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

typedef struct point{
	int x;
	int y;
}point;

void PrintTitle();
void set_cr_noecho_mode();
void PrintStage(int *);
void set_location();
void handler();
void tty_mode(int);
void ctrl_c_handler(int);

#endif
