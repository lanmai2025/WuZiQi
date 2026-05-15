#include "GameCtr.h"

GameCtr::GameCtr(int x, int y, int rank)
	:m_x(x),m_y(y),m_rank(rank),cur_p(p[0])
{
	m_cur_rank = 0;
	changeBlackSize();
	m_map = vector<vector<vector<Color>>>(rank, vector<vector<Color>>(y, vector<Color>(x,Color::Null)));
	m_cur_map = m_map[m_cur_rank];
	p[0].changeColor(Color::Black);
	p[1].changeColor(Color::Red);
}

int GameCtr::getX() const
{
	return m_x;
}

int GameCtr::getY() const
{
	return m_y;
}

int GameCtr::getCurRank() const
{
	return m_cur_rank;
}

Color GameCtr::getMapVal(int x, int y) const
{
	return m_cur_map[y][x];
}

vector<vector<Color>>& GameCtr::getCurMap(int rank)
{
	return m_map[rank];
}

int GameCtr::getBlockSize() const
{
	return m_black_size;
}

bool GameCtr::changeX(int x)
{
	m_x = x;
	return true;
}

bool GameCtr::changeY(int y)
{
	m_y = y;
	return true;
}

bool GameCtr::changeCurRank(int rank)
{
	m_cur_rank = rank;
	return true;
}

bool GameCtr::changeBlackSize()
{
	m_black_size = MAPHIGHT / getY();
	return true;
}

bool GameCtr::changeMapVal(int x, int y, Color c)
{
	if (m_cur_map[y][x] != Color::Null) return false;
	m_cur_map[y][x] = c;
	return true;
}

void GameCtr::init()
{
	initgraph(GAMEWIDTH, GAMEHIGHT);
}

void GameCtr::drawBK()
{
	//绘制基本界面
	setfillcolor(WHITE);
	fillrectangle(gap, gap, GAMEWIDTH - gap, GAMEHIGHT - gap);

	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);		//更改线样式
	int left = MAPWIDTH + 2 * gap;
	int top = GAMEHIGHT;
	line(left, gap, left , top);
}

void GameCtr::drawStartBoard()
{

}

void GameCtr::drawPrompt()
{

}

void GameCtr::drawMapLine()
{
	int line_width = 1;
	setlinestyle(PS_SOLID, line_width);


	//循环绘线
	int size = getBlockSize();
	int step = size + 1;
	for (int i = gap; i < MAPWIDTH; i += step)
	{
		line(i, gap, i, MAPHIGHT+gap);
		line(gap, i, MAPWIDTH+gap, i);
	}
}

void GameCtr::drawMapVal()
{
	int size = getBlockSize();
	int step = size + 1;

	int start = gap + size / 2;
	int max_x = getX();
	int max_y = getY();
	int s_y = start;
	int p_size = cur_p.getPlayerSize();
	for (int y = 0; y < max_y; ++y)
	{
		int s_x = start;
		for (int x = 0; x < max_x; ++x)
		{
			Color c = getMapVal(x, y);
			if (c != Color::Null)
			{
				setfillcolor(long long(c));
				fillcircle(s_y, s_x, p_size);
			}
		}
	}
}

void GameCtr::clearMap()
{
	for (int y = 0; y < m_y; ++y)
		for (int x = 0; x < m_x; ++x)
			m_cur_map[y][x] = Color::Null;
}

bool GameCtr::checkWin()  //未完成
{
	
	Color c = cur_p.getColor();
	int cur_x = cur_p.getCurX();
	int cur_y = cur_p.getCurY();

	bool is_win = false;


	
	return false;
}

void GameCtr::solve()
{

}
