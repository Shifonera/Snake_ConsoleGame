#include<iostream>
#include<ctime>
#include<conio.h>
#include<Windows.h>
using namespace std;

const int length = 15;//длинна поля
const int width = 50;//ширина поля
int x = width / 2;//Х змейки
int y = length / 2;//У змейки
int fruitX, fruitY;//координаты фрукта
enum Direction {STOP = 0, LEFT, RIGHT, UP, DOWN, EXIT};
Direction dir = STOP;
bool gameover = false;//конец игры
bool eatFruit = false;//фрукт на поле
bool tail;//отрисовался ли хвост
int score = 0; //счетчик фруктов
int tailX[100], tailY[100];//координаты хвоста
int ntail = 0;//количество элементов хвоста

void HideCursor()//скрыть каретку
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = false;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void Start()//условия новой игры
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

void Draw()  //отрисовка поля
{
	Sleep(80);
	system("cls");

	for (int i = 0; i < length; i++)             //Отрисовка поля
	{
		cout << "#"; //Левая рамка

			for (int k = 0; k < width-1; k++)
			{
				if (k == x && i == y) //Змейка
				{
					cout << "Y";
				}

				else if (k == fruitX && i == fruitY) //Фрукт
				{
					cout << "0";
				}

				else if (i == 0 || i == length -1) //Верхняя\нижняя рамка
				{
					cout << "#";
				}

				else if (k == width - 2) //Правая рамка
				{
					cout << "#";
				}

				else
				{
					tail = false;

					for (int n = 0; n < ntail; n++)//отрисовка хвоста
					{ 
						if (tailX[n] == k && tailY[n] == i)
						{
							cout << "o";
							tail = true;
						}
						if (x == tailX[n] && y == tailY[n])//проверка на столкновение с хвостом
						{
							gameover = true;
							break;
						}
					}

					if (tail == false)// если хвост, то нет пробела
					{
						cout << " ";
					}
				}
			}
		cout << endl;
	}
}

int Fruit() //координаты фрукта
{
	srand(time(NULL));

	fruitX = rand()% (width - 3)+1;
	fruitY = rand()% (length - 3)+1;

	return fruitX, fruitY;
}

void Input() //отслеживание клавиши ввода
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

void LogicSnake()//Движение змейки
{
	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < ntail; i++)//обработка хвоста и запись в массив его координат
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}
	switch (dir)//перемещение змейки после нажатия клавиши
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

	if (x < 0 || y < 1 || x > width - 3 || y > length - 2) //условие столкновения 
	{                                                     //со стенкой
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
	if (eatFruit)//новое местоположение съеденного фрукта
		{
			Fruit();
			score++;
			eatFruit = false;
			ntail++;
		}
	LogicSnake();
	Draw();
	Input();
	if (gameover)//рестарт
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