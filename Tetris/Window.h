#pragma once
#include "Shape.h"

#include <graphics.h>
class Window
{
public:
	Window();
	~Window();
	void display();//刷新后重新绘制
	bool check();//判断有无撞墙
	void begin();//游戏开始
	void setobs(int dec);//建墙
	void checkline();//检查有无可消除的边
	void deletline(int index);//消除边
private:
	int score;//分数
	int obstacle[24][24];//墙
	Shape *s;
};

