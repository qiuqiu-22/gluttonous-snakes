#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>

//��ʾ�߱����ķ���
enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

//���߱���һ���ṹ��
struct Snake
{
	int size; //�߱����Ĵ�С
	int dir; //�߱����ķ���
	int speed; //�߱������ٶ�
	POINT coor[500]; //�߱�����λ�� ������Ϊ500
}snake;

//��ʳ��һ���ṹ��
struct Food
{
	int x;
	int y;
	int r;
	bool flag;
	DWORD color;
}food;

//�ṹ��ĳ�ʼ��
void GameInit()
{
	//init ��ʼ�� graph ͼ�δ���
	initgraph(640, 480);
	//�������������
	srand(GetTickCount());
	
	//��ʼ���߱���
	snake.size = 3;
	snake.dir = RIGHT;
	snake.speed = 10;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coor[i].x = 40 - 10*i;
		snake.coor[i].y = 10;
	}
	
	//ʳ��ĳ�ʼ��
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.color = RGB(rand() % 256, rand() % 256, rand() % 256);
	food.r = 10;
	food.flag = true;
}

//����
void GameDraw()
{
	//˫����
	BeginBatchDraw();
	//���ñ�����ɫ
	setbkcolor(RGB(28, 115, 119));
	cleardevice();
	//�����߱���
	for (int i = 0; i < snake.size; i++)
	{
		solidcircle(snake.coor[i].x, snake.coor[i].y, 6);
	}
	//����ʳ��
	if (food.flag)
	{
		solidcircle(food.x, food.y, food.r);

	}
	EndBatchDraw();
}

//���߱���������
void SnakeMove()
{
	for (int i = snake.size -1; i > 0; i--)
	{
		snake.coor[i] = snake.coor[i - 1];
	}
	switch (snake.dir) //���Դ�ǽ
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

//ͨ�������ı��߱����ķ���
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

		case ' ': //��Ϸ��ͣ�߼�
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

//�ж��Ƿ��ʳ��
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
		//ʳ��ĳ�ʼ��
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
		//��ֹ�˳�
	}
	return 0;
}