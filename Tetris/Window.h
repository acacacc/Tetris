#pragma once
#include "Shape.h"

#include <graphics.h>
class Window
{
public:
	Window();
	~Window();
	void display();//ˢ�º����»���
	bool check();//�ж�����ײǽ
	void begin();//��Ϸ��ʼ
	void setobs(int dec);//��ǽ
	void checkline();//������޿������ı�
	void deletline(int index);//������
private:
	int score;//����
	int obstacle[24][24];//ǽ
	Shape *s;
};

