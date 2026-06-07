#pragma once

#include <vector>
#include <easyx.h>
#include <conio.h>
#include "Rely.h"
#include "Player.h"
#include <iostream>
#include <string>
#include "resource.h"
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
	//修改设置
	bool gameSet(ExMessage& em);
	//修改游戏参数
	bool reSetGame();
	//修改背景颜色
	bool setBKColor(Color c);
	//修改玩家颜色
	bool setP1Color(Color c);
	bool setP2Color(Color c);
	//修改map
	bool changeMap();

	//绘制

	//初始化窗口
	void init();
	//绘制游戏背景
	void drawBK();
	//绘制右侧区域
	void drawRightArea();
	//填充背景
	void fillBK();
	//绘制开始界面
	void drawStartBoard();
	//绘制提示界面
	void handleTipButtonClick(Player& currentPlayer);
	void handleDialogClose(Player& p1, Player& p2);
	bool isTipButtonClicked(int x, int y);
	bool isCloseBtnClicked(int x, int y);

	void drawPrompt();
	//绘制棋盘线
	void drawMapLine();
	//绘制棋子
	void drawMapVal(Player& cur_p);
	//绘制暂停界面
	void drawPauseTable();
	//结算页面按钮
	enum class SettlementAction
	{
		RESTART,
		BACK_TO_MENU
	};
	//绘制结算界面
	void showWinner(Player& winner, bool isFirstPlayer);
	SettlementAction showWinner(Player& winner, bool isFirstPlayer, bool isAIMode);
	void handleWinner(Player& winner, bool isFirstPlayer, bool isAIMode);
	
	//清除

	//重置地图
	void clearMapVal();
	//清空地图界面
	void clearMap();
	//清空游戏数据
	void clearGameData();

	//局内互动
	void showInteractionMessage(const wchar_t* msg, Player& cur_p);
	//根据步数显示对应消息
	void checkAndShowMessage(int steps, Player& cur_p);
	void checkAndShowAIMessage(int steps, Player& human_p);
	//检查

	//检查是否赢了
	bool checkWin(Player& cur_p);
	//检查是否可以更改地图
	bool checkCanChangeMapVal(int x, int y, Color c);

	
	//游戏循环
	void gameLoop(ExMessage& em); //真人vs
	void gameLoopAI(ExMessage& em); //真人vsAI

	//菜单
	void menu();

private:
	vector< vector < vector <Color> > > m_map;
	vector<vector<Color> >* m_cur_map;
	int m_x;
	int m_y;
	int m_rank;
	int m_cur_rank;
	int m_black_size;
	Color m_bk_color;
	Color m_p1_color;
	Color m_p2_color;
	
	int m_totalSteps; //双人对弈总步数
	int m_humanSteps;//人机对弈中玩家步骤
    std::wstring m_interactionMsg;//当前要显示的互动消息,宽字符显示
	
	//Player p[2];
	//Player& cur_p;
	//int m_cur_p_index;
};

