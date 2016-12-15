#include <stdio.h>
#include <curses.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
#include <signal.h>

#include "sokoban.h"
#include "stage.h"

int main()
{
	initscr();
	clear();

	PrintTitle(); // 타이틀을 출력합니다.
	getch();
	
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
	while(1){
		
		memcpy(stage, Stage[level], sizeof(Stage)); // Stage를 하나씩 불러와 현재 스테이지인 stage에 저장한다.
		clear();

		SetLocation(); // 가져온 stage 데이터에서  현재 캐릭터의  위치를 읽는다.

		while(1){
			if (PrintStage() == 1) // 게임 스테이지를 출력한다.8
				break;
			
			refresh();
			Handler();
		}

		if (level == MAXSTAGE){
			PrintEnding();
			break;
		}
			
	}

	sleep(1);
	endwin();
	return 0;
}

void PrintTitle() // 타이틀을 출력합니다.
{
	int i;

	for(i=0;i<50;i++){
		putxy(5,15+i,'=');
		putxy(17,65-i,'=');
	}

	move(11,36);
	addstr("Sokoban Game");	
	move(13,38);
	addstr("Press any key");

	move(LINES-1,COLS-1);
}

int PrintStage() // 게임 스테이지를 출력합니다.
{
	int stagex, stagey;
	char stagelv[2];
	int stageclear = 1; //1 : 클리어
	sprintf(stagelv, "Stage %d", level);

	for(stagex=0;stagex<20;stagex++){
		for(stagey=0;stagey<20;stagey++){
			putxy(stagex, stagey, stage[stagex][stagey]);
			if (stage[stagex][stagey] == '1') stageclear = 0; //도착점이 있을 경우 클리어X
		}
	}

	putxy(x, y, '@'); // 캐릭터를 출력합니다.

	// 현재 스테이지 난이도를 출력합니다.
	move(2, 30);
	addstr(stagelv);
	
	if ( stageclear == 0 ) {
	// 조작키 설명을 출력합니다.
		move(8,31);
		addstr("key");
		move(10,27);
		addstr(" w = 'up'   ");
		move(11,27);
		addstr(" a = 'left' ");
		move(12,27);
		addstr(" s = 'down' ");
		move(13,27);
		addstr(" d = 'right'");
		move(14, 27);
		addstr(" r = 'reset'");
		move(16,27);
		addstr(" q = 'quit' ");
	}
	else if(stageclear == 1){
		clear();
		move(8,31);
		addstr("Stage clear!");
		refresh();
		sleep(1);
		count = 0;
		level++;
	}

	move(LINES-1, COLS-1);
	return stageclear;
}

void SetLocation() // 가져온 stage에서 현재 캐릭터의 위치를 읽는다.
{
	int i, j;

	for(i=0;i<20;i++){
		for(j=0;j<20;j++){
			if(stage[i][j] == '2'){
				x = i;
				y = j;
				stage[i][j] = ' '; // 위치 좌표를 읽은 후 맵에서 데이터를 지워준다.
			}
		}
	}
}

void Handler()
{
	int i;
	int dx = 0, dy = 0;
	int next_x, next_y; //이동시 x, y좌표
	int nextbox_x, nextbox_y; //상자 이동시 x, y좌표
	static point end_point[MAXSIZE];
	char c;
	
	c = getchar();
	switch(c){
	case 'w':
		dx=-1, dy=0;
		break;
	case 's':
		dx=1, dy=0;
		break;
	case 'a':
		dx=0, dy=-1;
		break;
	case 'd':
		dx=0, dy=1;	
		break;
	case 'r':
		ResetCurrentStage();
		return;
	case 'q':
		endwin();
		exit(0);
	}

	next_x = x+dx, next_y = y+dy;
	nextbox_x = next_x+dx, nextbox_y = next_y+dy;
	if(stage[next_x][next_y] == '#') // 진행 방향에 벽이 있으면
		return;

	if(stage[next_x][next_y] == '0'){ // 진행 방향에 공이 있으면
		if(stage[nextbox_x][nextbox_y] == ' '){ // 공의 뒤가 비어 있을 때
			stage[next_x][next_y] = ' ';
			stage[nextbox_x][nextbox_y] = '0';
		}
		else if(stage[nextbox_x][nextbox_y] == '#' || 
			stage[nextbox_x][nextbox_y] == '0'){ // 공의 뒤가 막혀 있을 때
			return;
		}
		else if(stage[nextbox_x][nextbox_y] == '1'){ // 공의 뒤가 바구니일 때
			stage[next_x][next_y] = ' ';
			stage[nextbox_x][nextbox_y] = '0';
			end_point[count].x = nextbox_x;
			end_point[count++].y = nextbox_y;
		}
	}

	for(i=0;i<count;i++)
	{
		if(stage[end_point[i].x][end_point[i].y] == ' ') // 바구니에 들어간 공이 다시 나왔을 때
			stage[end_point[i].x][end_point[i].y] = '1'; // 다시 바구니를 세팅해준다.
	}

	x += dx;
	y += dy;
}

void PrintEnding(){

	clear();

	move(11, 28);
	addstr("Game Complited!!");
	refresh();

	move(LINES - 1, COLS - 1);
}

void ResetCurrentStage(){
	memcpy(stage, Stage[level], sizeof(Stage)); // Stage를 하나씩 불러와 현재 스테이지인 stage에 저장한다.
	
	SetLocation(); // 가져온 stage 데이터에서  현재 캐릭터의  위치를 읽는다.

	count = 0;
}