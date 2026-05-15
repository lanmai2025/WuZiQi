#pragma once

#include <easyx.h>
#include "Rely.h"

class Player
{
public:
	//构造函数
	Player(int x = 0, int y = 0);

	//获取

	//获取当前x
	int getCurX() const;
	//获取当前y
	int getCurY() const;
	//获取当前颜色
	Color getColor() const;
	//获取棋子大小
	int getPlayerSize() const;

	//修改

	//修改当前x
	bool changeCurX(int x);
	//修改当前y
	bool changeCurY(int y);
	//修改当前棋子颜色
	bool changeColor(Color color);
	//修改当前棋子大小
	bool changePlayerSize(int size);

	//绘制
	bool draw();


private:
	int m_cur_x;
	int m_cur_y;
	Color m_color;
	int m_size;
};