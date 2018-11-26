#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;

const int length = 15;//������ ����
const int width = 50;//������ ����
int x = width / 2;//� ������
int y = length / 2;//� ������
int fruitX, fruitY;//���������� ������
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN, EXIT};
Direction dir = STOP;
bool gameover = false;//����� ����
bool eatFruit = false;//����� �� ����
bool tail;//����������� �� �����
int score = 0; //������� �������
int tailX[100], tailY[100];//���������� ������
int ntail = 0;//���������� ��������� ������

void HideCursor()//������ �������
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void Start()//������� ����� ����
{
	x = width / 2;
	y = length / 2;
	dir = STOP;
	ntail = 0;
	score = 0;
	gameover = false;

	srand(time(NULL));
	fruitX = rand() % (width - 3) + 1;
	fruitY = rand() % (length - 3) + 1;
}

void Draw()  //��������� ����
{
	Sleep(80);
	system("cls");

	for (int i = 0; i < length; i++)             //��������� ����
	{
		cout << "#"; //����� �����

			for (int k = 0; k < width-1; k++)
			{
				if (k == x && i == y) //������
				{
					cout << "Y";
				}

				else if (k == fruitX && i == fruitY) //�����
				{
					cout << "0";
				}

				else if (i == 0 || i == length -1) //�������\������ �����
				{
					cout << "#";
				}

				else if (k == width - 2) //������ �����
				{
					cout << "#";
				}

				else
				{
					tail = false;

					for (int n = 0; n < ntail; n++)//��������� ������
					{ 
						if (tailX[n] == k && tailY[n] == i)
						{
							cout << "o";
							tail = true;
						}
						if (x == tailX[n] && y == tailY[n])//�������� �� ������������ � �������
						{
							gameover = true;
							break;
						}
					}

					if (tail == false)// ���� �����, �� ��� �������
					{
						cout << " ";
					}
				}
			}
		cout << endl;
	}
}

int Fruit() //���������� ������
{
	srand(time(NULL));

	fruitX = rand()% (width - 3)+1;
	fruitY = rand()% (length - 3)+1;

	return fruitX, fruitY;
}

void Input() //������������ ������� �����
{
	if (_kbhit())
	{
		switch (_getch())
	{
	case 'w':
		dir = UP;
		break;
	case 's':
		dir = DOWN;
		break;
	case 'a':
		dir = LEFT;
		break;
	case 'd':
		dir = RIGHT;
		break;
	case 'x':
		dir = EXIT;
		break;
	}
	}
	
}

void LogicSnake()//�������� ������
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < ntail; i++)//��������� ������ � ������ � ������ ��� ���������
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)//����������� ������ ����� ������� �������
	{
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case EXIT:
		gameover = true;;
		break;
	}

	if (x < 0 || y < 1 || x > width - 3 || y > length - 2) //������� ������������ 
	{                                                     //�� �������
		gameover = true;
	}

	if (x == fruitX && y == fruitY)
	{
		eatFruit = true;
	}


}

int main()
{
	Fruit();
	HideCursor();
	while (!gameover)
	{
	if (eatFruit)//����� �������������� ���������� ������
		{
			Fruit();
			score++;
			eatFruit = false;
			ntail++;
		}
	LogicSnake();
	Draw();
	Input();
	if (gameover)//�������
	{
		char restart;
		cout << "\n\nRestart? Y-yes, N-no\n" << endl;
		cin >> restart;
		switch (restart)
		{
		case 'y':
			Start();
			break;

		default:
			gameover = true;
			break;
		}
	}
	}
	cout << "\n\n\n" << "Your score = " << score << endl << endl;
	cin.get();
	return 0;
}