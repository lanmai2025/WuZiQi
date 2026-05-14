#pragma once

#include <vector>
#include <easyx.h>
#include "Rely.h"

using std::vector;

class GameCtr
{
public:
	//初始化
	GameCtr();

	//获取

	//获取横轴格子数
	int getX() const;
	//获取竖轴格子数
	int getY() const;
	//获取当前地图层次
	int getCurRank() const;
	//获取地图元素
	Color getMapVal() const;
	//获取当前地图引用
	vector<vector<Color> >& getCurMap() const;

	//修改
	
	//修改横轴格子数
	bool changeX();
	//修改竖轴格子数
	bool changeY();
	//修改当前地图层级
	bool changeCurRank();
	
	//绘制

	//绘制开始界面
	void drawStartBoard();
	//绘制提示界面
	void drawPrompt();
	//绘制棋盘线
	void drawMapLine();
	//绘制棋子
	void drawMapVal();
	//绘制暂停界面
	void drawPauseTable();
	
	//游戏主循环
	void solve();

	
private:
	vector<vector<vector<Color> > > m_map;
	vector<vector<Color> > m_cur_map;
	int m_x;
	int m_y;
	int m_rank;
	int m_cur_rank;

	

};

