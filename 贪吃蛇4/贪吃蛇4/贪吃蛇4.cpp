#include<string>
#include "stdafx.h"
#include<graphics.h>
#include<stdio.h>
#include<conio.h>
#include<time.h>
#include<mmsystem.h>
#include<string.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
#pragma comment(lib,"winmm.lib")
#define SIZE 20 
#define N 10000  //蛇最大节数
struct Coor
{
	int x;
	int y;
};
enum Ch{up=72,down=80,LEFT=75,RIGHT=77};//上下左右四个方向

struct Snake
{
	int n;//蛇的节数
	Coor scr[N];

	Ch ch;//接收蛇的方向;
}snake;

struct Food
{
	Coor fsr;//食物坐标
	int flag;//标志食物有没有被吃掉，1表示没吃掉；
}food;
IMAGE snakeLEFT,snakeRIGHT,snakeup,snakedown,snakebody,eating;

void GameInit();
void FoodCoor();

void FoodPaint(IMAGE eating);

void SnakeMove();
void SnakePaint(IMAGE snakeRIGHT,IMAGE snakeLEFT,IMAGE snakeup,IMAGE snakedown,IMAGE snakebody);
void EatFood();
void ChangeSnakeCh();

void GameBack();
void OverGame();

int _tmain(int argc, _TCHAR* argv[])
{

	GameInit();
	mciSendString("open 甩葱歌.mp3 alias music",0,0,0);

	mciSendString("play 甩葱歌.mp3 repeat",0,0,0);
	while(1)
	{
		while(!kbhit())
		{
			if(food.flag==0)
			FoodCoor();
			cleardevice();
			FoodPaint(eating);//绘制食物
			SnakeMove();//蛇移动
			SnakePaint(snakeRIGHT,snakeLEFT,snakeup,snakedown,snakebody);
			Sleep(200);
			EatFood();
			GameBack();
		}
		ChangeSnakeCh();
	}
	while(1);
	return 0;
}

void GameInit()
{

	char ss[100][100];
	strcpy(ss[0],"草莓.jpg");
	strcpy(ss[1],"葡萄.jpg");
	strcpy(ss[2],"樱桃.jpg");
	strcpy(ss[3],"西瓜.jpg");
	//strcpy(ss[4],"蓝莓.jpg");
	//strcpy(ss[5],"橙子.jpg");
	//strcpy(ss[6],"柚子.jpg");
	//strcpy(ss[7],"树莓.jpg");
	initgraph(640,480);//作用：制作游戏窗口
	int t=rand()%4;
	setbkcolor(WHITE);//设置背景颜色
	cleardevice();//刷新；使上面的语句作用体现出来
	loadimage(&snakeRIGHT,"蛇头右.jpg",SIZE,SIZE);
	loadimage(&snakeup,"蛇头上.jpg",SIZE,SIZE);
	loadimage(&snakedown,"蛇头下.jpg",SIZE,SIZE);
	loadimage(&snakeLEFT,"蛇头左.jpg",SIZE,SIZE);
    loadimage(&snakebody,"蛇身.jpg",SIZE,SIZE);
	loadimage(&eating,ss[t],SIZE,SIZE);
	//蛇初始化
	snake.scr[0].x=0;
	snake.scr[0].y=0;
	snake.n=1;
	snake.ch=RIGHT;
	food.flag=0;
}
void FoodCoor()
{
	srand((unsigned int)time(NULL));
	food.fsr.x=(rand()%31+1)*SIZE;
	food.fsr.y=(rand()%23+1)*SIZE;
	food.flag=1;
}
void FoodPaint(IMAGE eating)
{
	putimage(food.fsr.x,food.fsr.y,&eating);
}
void SnakeMove()
{
	for(int i=snake.n-1;i>0;i--)
	{
		//Sleep(500);
		snake.scr[i].x=snake.scr[i-1].x;
		snake.scr[i].y=snake.scr[i-1].y;
	}
	switch (snake.ch)
	{
	case up:snake.scr[0].y-=SIZE;break;
	case down:snake.scr[0].y+=SIZE;break;
	case LEFT:snake.scr[0].x-=SIZE;break;
	case RIGHT:snake.scr[0].x+=SIZE;break;
	default:
		break;
	}
}
void SnakePaint(IMAGE snakeRIGHT,IMAGE snakeLEFT,IMAGE snakeup,IMAGE snakedown,IMAGE snakebody)
{
	switch(snake.ch)
	{
	case up:
		putimage(snake.scr[0].x,snake.scr[0].y,&snakeup);
		break;
	case down:
		putimage(snake.scr[0].x,snake.scr[0].y,&snakedown);
		break;
	case RIGHT:
				putimage(snake.scr[0].x,snake.scr[0].y,&snakeRIGHT);
				break;
	case LEFT:
				putimage(snake.scr[0].x,snake.scr[0].y,&snakeLEFT);
				break;
	default:
		break;
	}
	for(int i=snake.n-1;i>0;i--)
	{
		putimage(snake.scr[i].x,snake.scr[i].y,&snakebody);
	}
}
void ChangeSnakeCh()
{
	switch (getch())
	{
	case 72:
		if(snake.ch!=up)
		{
			snake.ch=up;
		}
		break;
    case 80:
		if(snake.ch!=down)
			snake.ch=down;
		break;
	case 75:
		if(snake.ch!=RIGHT)
			snake.ch=LEFT;
		break;
	case 77:
		if(snake.ch!=LEFT)
			snake.ch=RIGHT;
		break;
	default:break;
	}
}
void EatFood()
{
	if(snake.scr[0].x==food.fsr.x&&snake.scr[0].y==food.fsr.y)
	{
	snake.n++;
	food.flag=0;
	char ss[100][100];
	strcpy(ss[0],"草莓.jpg");
	strcpy(ss[1],"葡萄.jpg");
	strcpy(ss[2],"樱桃.jpg");
	strcpy(ss[3],"西瓜.jpg");
	//strcpy(ss[4],"蓝莓.jpg");
	//strcpy(ss[5],"橙子.jpg");
	//strcpy(ss[6],"柚子.jpg");
	//strcpy(ss[7],"树莓.jpg");
	int t=rand()%4;
	loadimage(&eating,ss[t],SIZE,SIZE);
	}
}
void GameBack()
{
	if(snake.scr[0].y<-1||snake.scr[0].y>470||snake.scr[0].x<-1||snake.scr[0].x>631)
	{
		OverGame();
	}
	for(int i=snake.n-1;i>0;i--)
	{
		if(snake.scr[0].x==snake.scr[i].x&&snake.scr[0].y==snake.scr[i].y)
		{
			OverGame();
		}
	}
}
void OverGame()
{
	cleardevice();
	settextcolor(GREEN);

	settextstyle(50,0,"黑体");
	outtextxy(200,200,"game over");
	settextcolor(YELLOW);
	settextstyle(50,0,"楷体");

	char str[100]="您的分数:";
	char str1[54];

	itoa(snake.n,str1,10);

	strcat(str,str1);
	outtextxy(100,100,str);
	//MessageBox(0, TEXT("不要灰心！┭┮﹏┭┮"), TEXT("(づ￣ 3￣)づ"), 0);
	Sleep(2000);
	exit;
}