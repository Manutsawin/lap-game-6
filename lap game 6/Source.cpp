#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<windows.h>
#include<conio.h>
void setcolor(int fg, int bg);
void setcursor(bool visible);
void gotoxy(int x, int y);
void draw_ship(int x, int y);
void erase_ship(int x, int y);
void erase_fire(int x, int y);
void draw_fire(int x, int y);
void draw_star(int x, int y);
char cursor(int x, int y);
void draw_score(int x);
int main()
{
	setcursor(0);
	char ch = ' ';
	int x = 40, y = 20, direcship = 0, loop,
		fire[5], xfire[5], yfire[5], bullet = 0,
		xstar[20], ystar[20],
		score = 0;
	for (loop = 0; loop < 5; loop++)
	{
		fire[loop] = 0;
		xfire[loop] = x;
		yfire[loop] = y;

	}
	for (loop = 0; loop < 20; loop++)
	{
		xstar[loop] = (rand() % 80) + 3;
		ystar[loop] = rand() % 5;
		draw_star(xstar[loop], ystar[loop]);
	}
	draw_ship(x, y);
	draw_score(score);

	do {

		if (_kbhit()) {
			ch = _getch();

			if (ch == 'd')
			{
				direcship = 1;
			}
			if (ch == 'a')
			{
				direcship = 2;
			}
			if (ch == 's')
			{
				direcship = 0;
			}
			if (ch == ' ' && bullet < 5)
			{
				fire[bullet] = 1;
				yfire[bullet] = y - 1;
				xfire[bullet] = x;
				bullet++;

			}
			fflush(stdin);
		}
		if (direcship == 1 && x < 80)
		{
			erase_ship(x, y);
			draw_ship(++x, y);

		}
		if (direcship == 2 && x > 0)
		{
			erase_ship(x, y);
			draw_ship(--x, y);

		}
		for (loop = 0; loop < 5; loop++)
		{

			if (fire[loop] == 1 && yfire[loop] >= 0)
			{

				erase_fire(xfire[loop], yfire[loop]);
				if (yfire[loop] < 1)
				{

					fire[loop] = 0;
					if (loop == 5 - 1)
					{
						bullet = 0;
					}

				}
				else if (fire[loop] == 1)
				{

					draw_fire(xfire[loop] + 3, --yfire[loop]);
					if (cursor(xfire[loop] + 3, yfire[loop] - 1) == '*')
					{
						Beep(700, 50);
						score = score + 1;
						draw_score(score);
						fire[loop] = 0;
						erase_fire(xfire[loop], yfire[loop]);
						erase_fire(xfire[loop], yfire[loop] - 1);
						draw_star((rand() % 80) + 3, rand() % 5);
						if (loop == 5 - 1)
						{

							bullet = 0;

						}


					}


				}

			}
		}
		Sleep(100);
	} while (ch != 'x');
	return 0;
}
void gotoxy(int x, int y)
{
	COORD c = { x, y };
	SetConsoleCursorPosition(
		GetStdHandle(STD_OUTPUT_HANDLE), c);
}
void draw_ship(int x, int y)
{
	setcolor(4, 15);
	gotoxy(x, y);
	printf(" <^I^> ");
}

void erase_ship(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x, y);
	printf("       ");
}

void erase_fire(int x, int y)
{
	setcolor(0, 0);
	gotoxy(x + 3, y);
	printf(" ");
}

void setcursor(bool visible)
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO lpCursor;
	lpCursor.bVisible = visible;
	lpCursor.dwSize = 20;
	SetConsoleCursorInfo(console, &lpCursor);
}

void setcolor(int fg, int bg)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, bg * 16 + fg);
}

void draw_fire(int x, int y)
{
	setcolor(7, 12);
	gotoxy(x, y);
	printf("^");
}
void draw_star(int x, int y)
{
	setcolor(6, 15);
	gotoxy(x, y);
	printf("*");
}
char cursor(int x, int y)
{
	HANDLE hStd = GetStdHandle(STD_OUTPUT_HANDLE);
	char buf[2]; COORD c = { x,y }; DWORD num_read;
	if (!ReadConsoleOutputCharacter(hStd, (LPTSTR)buf, 1, c, (LPDWORD)&num_read))
		return '\0';
	else
		return buf[0];

}
void draw_score(int x)
{
	setcolor(3, 0);
	gotoxy(90, 0);
	printf("=============");
	gotoxy(90, 1);
	printf("  score = %d ", x);
	gotoxy(90, 2);
	printf("=============");
}


