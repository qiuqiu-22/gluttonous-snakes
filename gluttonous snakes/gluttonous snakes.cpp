#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>

int flag = 0;
int screen;

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

//主页设置
void HomePage()
{
	
	//主页页面设计
	initgraph(640, 480, EX_DBLCLKS);
	
	//文字
	wchar_t word1[] = L"按空格开始游戏";
	wchar_t word2[] = L"上下左右键控制蛇宝宝";
	wchar_t word3[] = L"按空格暂停";
	outtextxy(220, 240, word1);
	outtextxy(220, 280, word2);
	outtextxy(220, 300, word3);

	while(1)
		if (_kbhit())
		{
			if (_getch() == ' ')
			{
				cleardevice();
				screen = 1;
				break;
			}
		}
}

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
		case 72:
			if (snake.dir != DOWN)
			{
				snake.dir = UP;
			}
			break;
		
		case 80:
			if (snake.dir != UP)
			{
				snake.dir = DOWN;
			}
			break;
		
		case 75:
			if (snake.dir != RIGHT)
			{
				snake.dir = LEFT;
			}
			break;
		
		case 77:
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
		case 27:
			screen = 0;
			break;
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
		flag++;
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
	
	HomePage(); 
	GameInit();

	while (1)
		switch (screen)
		{
		case 0 :
			HomePage();
			cleardevice();
		case 1 :
		
			GameDraw();
			SnakeMove();
			KeyControl();
			EatFood();
			Sleep(60 - flag);
			//防止退出
		}
	
	
	return 0;
}