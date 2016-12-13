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
	void ctrl_c_handler(int);

	initscr();
	tty_mode(0);
	set_cr_noecho_mode();
	clear();

	PrintTitle(); // 타이틀을 출력합니다.
	getch();
	
	signal(SIGINT, ctrl_c_handler);
	signal(SIGQUIT, SIG_IGN);
	while(1){
		
		memcpy(stage, Stage[level], sizeof(Stage)); // Stage를 하나씩 불러와 현재 스테이지인 stage에 저장한다.
		clear();

		set_location(); // 가져온 stage 데이터에서  현재 캐릭터의  위치를 읽는다.

		while(1){
			PrintStage(&level); // 게임 스테이지를 출력한다.
			refresh();
			handler();
		}
	}
	getch();
	endwin();
	tty_mode(1);
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

void set_cr_noecho_mode()
{
	struct termios ttystate;

	tcgetattr(0, &ttystate);
	ttystate.c_lflag &= ~ICANON;
	ttystate.c_lflag &= ~ECHO;
	ttystate.c_cc[VMIN] = 1;
	tcsetattr(0, TCSANOW, &ttystate);
}

void PrintStage(int *lv) // 게임 스테이지를 출력합니다.
{
	int stagex, stagey;
	char stagelv[2];
	int stageclear = 0;
	sprintf(stagelv, "Stage %d", *lv);

	for(stagex=0;stagex<20;stagex++){
		for(stagey=0;stagey<20;stagey++){
			putxy(stagex, stagey, stage[stagex][stagey]);
			if (stage[stagex][stagey] == '1') stageclear = 1;
		}
	}

	putxy(x, y, '@'); // 캐릭터를 출력합니다.

	// 현재 스테이지 난이도를 출력합니다.
	move(2, 30);
	addstr(stagelv);
	
	if ( stageclear == 1 ) {
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
		move(15,27);
		addstr(" q = 'quit' ");
	}
	else {
		move(8,31);
		addstr("clear!");
		*lv++;
		return;
		
	}
	move(LINES-1, COLS-1);
}

void set_location() // 가져온 stage에서 현재 캐릭터의 위치를 읽는다.
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

void handler()
{
	int i;
	int dx = 0, dy = 0;
	int next_x, next_y; //이동시 x, y좌표
	int nextbox_x, nextbox_y; //상자 이동시 x, y좌표
	static point end_point[MAXSIZE];
	static int count = 0;
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
	case 'q':
		endwin();
		tty_mode(1);
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

	for(i=0;i<=count;i++)
	{
		if(stage[end_point[i].x][end_point[i].y] == ' ') // 바구니에 들어간 공이 다시 나왔을 때
			stage[end_point[i].x][end_point[i].y] = '1'; // 다시 바구니를 세팅해준다.
	}

	x += dx;
	y += dy;
}

void ctrl_c_handler(int signum)
{
	endwin();
	tty_mode(1);
	exit(1);
}

void tty_mode(int how)
{
	static struct termios original_mode;
	static int original_flags;
	static int stored = 0;

	if(how == 0){
		tcgetattr(0, &original_mode);
		original_flags = fcntl(0, F_GETFL);
		stored = 1;
	}
	else if(stored){
		tcsetattr(0, TCSANOW, &original_mode);
		fcntl(0, F_SETFL, original_flags);
	}
}
