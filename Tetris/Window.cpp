#include "Window.h"

Window::Window()
{
	s = new Shape;
	score = 0;
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 24; j++)
			obstacle[i][j] = 0;
	display();
	begin();
}


Window::~Window()
{
}

void Window::display() {
	cleardevice();
	setcolor(WHITE);
	line(480, 0, 480, 480);
	char str[5];
	sprintf(str, "%d", score);
	outtextxy(560, 120, str);
	setfillcolor(WHITE);
	for (int i = 0; i < 4; i++)
		if (s->shapepos[i].x || s->shapepos[i].y)
			bar(s->shapepos[i].x, s->shapepos[i].y, s->shapepos[i].x + SQUARE_SIZE, s->shapepos[i].y + SQUARE_SIZE);
	setfillcolor(RED);
	for (int i = 0; i < 24; i++)
		for (int j = 0; j < 24; j++)
			if (obstacle[i][j]) {
				bar(j*SQUARE_SIZE, i*SQUARE_SIZE, j*SQUARE_SIZE + SQUARE_SIZE, i*SQUARE_SIZE + SQUARE_SIZE);
			}
}

bool Window::check() {
	int num = 4;
	if (s->shapevar == 4 || s->shapevar == 5)
		num = 3;
	for (int i = 0; i < num; i++) {
		if (s->shapepos[i].x > 460 || s->shapepos[i].x < 0)
			return false;
		if (s->shapepos[i].y == 480) {
			setobs(2);
			delete s;
			s = new Shape;
			return false;
		}
		if (obstacle[s->shapepos[i].y / SQUARE_SIZE][s->shapepos[i].x / SQUARE_SIZE]) {
			setobs(2);
			delete s;
			s = new Shape;
			return false;
		}
	}
	return true;
}

void Window::begin() {
	int temp;
	while (1) {
		DWORD startTime = GetTickCount();
		while (kbhit()) {
			int num = 4;
			if (s->shapevar == 4 || s->shapevar == 5)
				num = 3;

			int dir = getch();
			if (dir == 'w') {
				temp = s->shapevar;
				s->change();
				if (!check()) {
					s->shapevar = temp;
					s->copyarr(temp);
				}
			}
			else {
				if (dir == 'a') {
					int flag = 0;

					for (int i = 0; i < num; i++) {
						if (s->shapepos[i].x - SQUARE_SIZE < 0 || obstacle[s->shapepos[i].y / 20][(s->shapepos[i].x - SQUARE_SIZE) / 20]) {
							flag = 1;
							break;
						}
					}
					if (!flag)
						s->move('a');
				}
				if (dir == 'd') {
					int flag = 0;
					for (int i = 0; i < num; i++) {
						if (s->shapepos[i].x + SQUARE_SIZE > 460 || obstacle[s->shapepos[i].y / 20][(s->shapepos[i].x + SQUARE_SIZE) / 20]) {
							flag = 1;
							break;
						}
					}
					if (!flag)
						s->move('d');
				}
			}
		}
		s->move('s');
		check();
		display();
		int vis = 0;
		for (int i = 0; i < 24; i++) {
			if (obstacle[0][i]) {
				setcolor(WHITE);
				outtextxy(520,100,"GAME OVER");
				vis = 1;
				break;
			}
		}
		if (vis)
			break;
		DWORD EndTime = GetTickCount();
		Sleep(300 - (EndTime - startTime));
	}

}

void Window::setobs(int dec) {
	int num = 4;
	if (s->shapevar == 4 || s->shapevar == 5)
		num = 3;
	if (dec == 2) {
		for (int i = 0; i < num; i++)
			s->shapepos[i].y -= SQUARE_SIZE;
	}
	for (int i = 0; i < num; i++) {
		obstacle[s->shapepos[i].y / SQUARE_SIZE][s->shapepos[i].x / SQUARE_SIZE] = 1;
	}
	checkline();
}

void Window::checkline() {
	for (int i = 23; i >= 0; i--) {
		int cnt = 0;
		for (int j = 0; j < 24; j++) {
			if (obstacle[i][j])
				cnt++;
			else
				continue;
		}
		if (cnt == 24) {
			deletline(i);
		}
	}
}

void Window::deletline(int index) {
	for (int i = index; i > 0; i--) {
		for (int j = 0; j < 24; j++) {
			obstacle[i][j] = obstacle[i - 1][j];
		}
	}
	score += 1;
	checkline();
}

