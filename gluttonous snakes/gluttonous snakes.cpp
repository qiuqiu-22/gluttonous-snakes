#define _CRT_SECURE_NO_WARNINGS 1
#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<graphics.h>

int flag = 0;
int screen;

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

//��ҳ����
void HomePage()
{
	
	//��ҳҳ�����
	initgraph(640, 480, EX_DBLCLKS);
	
	//����
	wchar_t word1[] = L"���ո�ʼ��Ϸ";
	wchar_t word2[] = L"�������Ҽ������߱���";
	wchar_t word3[] = L"���ո���ͣ";
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

		case ' ': //��Ϸ��ͣ�߼�
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

//�ж��Ƿ��ʳ��
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
			//��ֹ�˳�
		}
	
	
	return 0;
}