#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>

//表示蛇宝宝的方向
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//给蛇宝宝一个结构体
struct Snake
{
	int size; //蛇宝宝的大小
	int dir; //蛇宝宝的方向
	int speed; //蛇宝宝的速度
	POINT coor[500]; //蛇宝宝的位置 最大节数为500
}snake;

//给食物一个结构体
struct Food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;

//结构体的初始化
void GameInit()
{
	//init 初始化 graph 图形窗口
	initgraph(640, 480);
	//设置随机数种子
	srand(GetTickCount());
	
	//初始化蛇宝宝
	snake.size = 3;
	snake.dir = RIGHT;
	snake.speed = 10;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - 10*i;
		snake.coor[i].y = 10;
	}
	
	//食物的初始化
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = 10;
	food.flag = true;
}

//绘制
void GameDraw()
{
	//双缓冲
	BeginBatchDraw();
	//设置背景颜色
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//绘制蛇宝宝
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 6);
	}
	//绘制食物
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);

	}
	EndBatchDraw();
}

//让蛇宝宝动起来
void SnakeMove()
{
	for (int i = snake.size -1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir) //可以穿墙
	{
	case UP:
		snake.coor[0].y -= snake.speed;
		if (snake.coor[0].y <= 0)
		{
			snake.coor[0].y = 480;
		}
		break;
	
	case DOWN:
		snake.coor[0].y += snake.speed;
		if (snake.coor[0].y >= 480)
		{
			snake.coor[0].y = 0;
		}
		break;
	
	case LEFT:
		snake.coor[0].x -= snake.speed;
		if (snake.coor[0].x <= 0)
		{
			snake.coor[0].x = 640;
		}
		break;
	
	case RIGHT:
		snake.coor[0].x += snake.speed;
		if (snake.coor[0].x >= 640)
		{
			snake.coor[0].x = 0;
		}
		break;
	}

}

//通过按键改变蛇宝宝的方向
void KeyControl()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		
		case 's':
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		
		case 'a':
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		
		case 'd':
			if (snake.dir != LEFT)
			{
				snake.dir = RIGHT;
			}
			break;

		case ' ': //游戏暂停逻辑
			while (1)
			{
				if (_getch() == ' ')
				{
					return;
				}
			}
		}
	}
}

//判断是否吃食物
void EatFood()
{
	if (food.flag && snake.coor[0].x >= food.x - food.r && snake.coor[0].x <= food.x + food.r &&
		snake.coor[0].y >= food.y - food.r && snake.coor[0].y <= food.y + food.r)
	{
		food.flag = false;
		snake.size++;
	}

	if (!food.flag)
	{
		//食物的初始化
		food.x = rand() % 640;
		food.y = rand() % 480;
		food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
		food.r = 10;
		food.flag = true;
	}
}



int main()
{
	GameInit();
		while (1)
	{
		GameDraw();
		SnakeMove();
		KeyControl();
		EatFood();
		Sleep(50);
		//防止退出
	}
	return 0;
}