#pragma once

#include <vector>
#include <easyx.h>
#include <conio.h>
#include "Rely.h"
#include "Player.h"
#include <iostream>

using std::vector;

#define GAMEWIDTH 900
#define GAMEHIGHT 640
#define MAPWIDTH 630
#define MAPHIGHT 630

const int gap = 5;


class GameCtr
{
public:
	//初始化
	GameCtr(int x, int y, int rank);

	//获取

	//获取横轴格子数
	int getX() const;
	//获取竖轴格子数
	int getY() const;
	//获取当前地图层次
	int getCurRank() const;
	//获取地图元素
	Color getMapVal(int x, int y) const;       
	//获取当前地图引用
	vector<vector<Color> >& getCurMap(int rank);
	//获取方格边长；
	int getBlockSize() const;

	//修改
	
	//修改横轴格子数
	bool changeX(int x);
	//修改竖轴格子数
	bool changeY(int y);
	//修改当前地图
	bool changeCurMap(); 
	//地图层级+1
	bool addCurRank();
	//地图层级-1
	bool subCurRank();
	//修改方格边长
	bool changeBlackSize();
	//修改地图
	bool changeMapVal(int x, int y, Color c);

	//绘制

	//初始化窗口
	void init();
	//绘制背景
	void drawBK();
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

	//清除

	//重置地图
	void clearMapVal();
	//清空地图界面
	void clearMap();


	//检查

	//检查是否赢了
	bool checkWin();
	//检查是否可以更改地图
	bool checkCanChangeMapVal(int x, int y, Color c);

	
	//游戏主循环
	void solve();

	
private:
	vector< vector < vector <Color> > > m_map;
	vector<vector<Color> >* m_cur_map;
	int m_x;
	int m_y;
	int m_rank;
	int m_cur_rank;
	int m_black_size;

	Player p[2];
	//Player& cur_p;
	int m_cur_p_index;
};

