#pragma once

#include <easyx.h>

class Player
{
public:
	//构造函数
	Player(int x, int y);
	
	//获取

	//获取当前x
	int getCurX() const;
	//获取当前y
	int getCurY() const;
	//获取当前颜色
	long long getColor() const;

	//修改

	//修改当前x
	bool changeCurX(int x);
	//修改当前y
	bool changeCurY(int y);
	//修改当前棋子颜色
	bool changeColor(long long color);
	
	//绘制
	bool draw();


private:
	int m_cur_x;
	int m_cur_y;
	long long m_color;

};

