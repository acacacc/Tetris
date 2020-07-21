#include "Shape.h"

Shape::Shape()
{
	posx = 220, posy = 0;
	shapevar = randomshape();
	char s[5];
	sprintf(s,"%d",shapevar);
	outtextxy(540,400,s);
	copyarr(shapevar);
}


Shape::~Shape()
{
}

int Shape::randomshape() {
	randomize();
	return random(19);
}

void Shape::updatepos() {
	int cnt = 0;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (nowshape[i][j]) {
				shapepos[cnt].x = posx+j*SQUARE_SIZE;
				shapepos[cnt].y = posy+i*SQUARE_SIZE;
				cnt++;
			}
		}
	}
}

void Shape::change() {
	if (shapevar < 6) {
		if (shapevar & 1)
			shapevar--;
		else
			shapevar++;
	}
	else {
		switch (shapevar)
		{
		case 6:
		case 7:
		case 8:shapevar++;
			break;
		case 9:shapevar = 6;
			break;
		case 10:
		case 11:
		case 12:shapevar++;
			break;
		case 13:shapevar = 10;
			break;
		case 14:
		case 15:
		case 16:shapevar++;
			break;
		case 17:shapevar = 14;
			break;
		default:
			return;
		}
	}
	copyarr(shapevar);
}

void Shape::move(int dir) {
	switch (dir)
	{
	case 'a':
		posx -= 20;
		break;
	case 'd':
		posx += 20;
		break;
	case 's':
		posy += 20;
		break;
	default:
		break;
	}
	updatepos();
}

void Shape::copyarr(int index) {
	for(int i=0; i<3; i++)
		for (int j = 0; j < 3; j++) 
			nowshape[i][j] = varies[index][i][j];
	updatepos();
}