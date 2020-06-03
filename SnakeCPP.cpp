#include <iostream>
#include <conio.h>
using namespace std;
bool died;
int width = 50;
int height = 20;
int x, y;
int objectPosX, objectPosY;
int score;
int partsX[100], partsY[100];
int parts;

enum Direction {
	STOP, LEFT, RIGHT, UP, DOWN
};

Direction dir;

void Draw() {
	system("cls");
	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;

	for (int i = 0; i < height; i++) {
		for (int a = 0; a < width; a++) {
			if (a == 0)
				cout << "#";
			if (i == y && a == x)
				cout << "@";
			else if (i == objectPosY && a == objectPosX)
				cout << "$";

			else {
				bool print = false;
				for (int k = 0; k < parts; k++) {
					if (partsX[k] == a && partsY[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
					cout << " ";
				
			}
			if (a == width - 1)
				cout << "#";
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
		cout << "#";
	cout << endl;
	cout << "Score: " << score << endl;
}

void Setup() {
	died = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	objectPosX = rand() % width;
	objectPosY = rand() % height;
	score = 0;
}

void Logic() {
	int previousX = partsX[0];
	int previousY = partsY[0];
	int prev2X, prev2Y;
	partsX[0] = x;
	partsY[0] = y;
	for (int i = 1; i < parts; i++) {
		prev2X = partsX[i];
		prev2Y = partsY[i];
		partsX[i] = previousX;
		partsY[i] = previousY;
		previousX = prev2X;
		previousY = prev2Y;
	}
	switch (dir) {
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
	}
	if (x > width || x < 0 || y > height || y < 0) {
		died = true;
	}
	if (x == objectPosX && y == objectPosY) {
		score++;
		objectPosX = rand() % width;
		objectPosY = rand() % height;
		parts++;
	}
}

void Input() {
	if (_kbhit()) {
		switch (_getch()) {
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
		}
	}
}

int main()
{
	Setup();
	while (!died) {
		Draw();
		Logic();
		Input();
	}
	return 0;
}


