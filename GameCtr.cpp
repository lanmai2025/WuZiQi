#include "GameCtr.h"

GameCtr::GameCtr(int x, int y, int rank)
	:m_x(x),m_y(y),m_rank(rank),m_cur_p_index(0)
{
	m_cur_rank = 0;
	changeBlackSize();
	m_map = vector<vector<vector<Color>>>(rank, vector<vector<Color>>(y, vector<Color>(x,Color::Null)));
	m_cur_map = &m_map[m_cur_rank];
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
	return (*m_cur_map)[y][x];
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

bool GameCtr::changeCurMap()
{
	m_cur_map = &m_map[m_cur_rank];
	return true;
}

bool GameCtr::addCurRank()
{
	m_cur_rank = (m_cur_rank + 1) % m_rank;
	return true;
}

bool GameCtr::subCurRank()
{
	m_cur_rank = (m_cur_rank + m_rank - 1) % m_rank;
	return true;
}

bool GameCtr::changeBlackSize()
{
	m_black_size = MAPHIGHT / getY();
	return true;
}

bool GameCtr::changeMapVal(int x, int y, Color c)
{
	int pre_rank = getCurRank();
	addCurRank();
	changeCurMap();
	for (int new_y = 0; new_y < m_y; ++new_y)
	{
 		for (int new_x = 0; new_x < m_x; ++new_x)
			(*m_cur_map)[new_y][new_x] = m_map[pre_rank][new_y][new_x];
	}
	(*m_cur_map)[y][x] = c;
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
	Player& cur_p = p[m_cur_p_index];

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
				setfillcolor(COLORREF(c));
				fillcircle(s_x, s_y, p_size);
			}
			s_x += step;
		}
		s_y += step;
	}
}

void GameCtr::clearMapVal()
{
	for (int y = 0; y < m_y; ++y)
		for (int x = 0; x < m_x; ++x)
			(*m_cur_map)[y][x] = Color::Null;
}

void GameCtr::clearMap()
{
	drawBK();
	drawMapLine();
}

bool GameCtr::checkWin()  
{
	Player& cur_p = p[m_cur_p_index];
	Color c = cur_p.getColor();
	int cur_x = cur_p.getCurX();
	int cur_y = cur_p.getCurY();

	//查x轴
	int cnt = 1;
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x + i;
		if (x >= m_x) break;
		if ((*m_cur_map)[cur_y][x] == c)
			++cnt;
	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		if (x < 0) break;
		if ((*m_cur_map)[cur_y][x] == c)
			++cnt;
	}
	if (cnt >= 5) return true;

	//查y轴
	cnt = 1;
	for (int i = 1; i < 5; ++i)
	{
		int y = cur_y + i;
		if (y >= m_y) break;
		if ((*m_cur_map)[y][cur_x] == c)
			++cnt;
	}
	for (int i = 1; i < 5; ++i)
	{
		int y = cur_y - i;
		if (y < 0) break;
		if ((*m_cur_map)[y][cur_x] == c)
			++cnt;
	}
	if (cnt >= 5) return true;

	//查主对角线
	cnt = 1;
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x + i;
		int y = cur_y + i;
		if (x >= m_x || y >= m_y) break;
		if ((*m_cur_map)[y][x] == c)
			++cnt;
	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		int y = cur_y - i;
		if (x < 0 || y < 0) break;
		if ((*m_cur_map)[y][x] == c)
			++cnt;
	}
	if (cnt >= 5) return true;

	//查副对角线
	cnt = 1;
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x + i;
		int y = cur_y - i;
		if (x >= m_x || y < 0) break;
		if ((*m_cur_map)[y][x] == c)
			++cnt;
	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		int y = cur_y + i;
		if (x < 0 || y >= m_y) break;
		if ((*m_cur_map)[y][x] == c)
			++cnt;
	}
	if (cnt >= 5) return true;

	return false;
}

bool GameCtr::checkCanChangeMapVal(int x, int y, Color c)
{
	if ((*m_cur_map)[y][x] == Color::Null) return true;
	return false;
}

void GameCtr::solve()
{
	init();
	drawBK();
	drawMapLine();

	ExMessage em;
	Player* cur_p = &p[m_cur_p_index];
	int size = getBlockSize() + 1;


	while (true)
	{
		em = getmessage(EX_MOUSE);

		switch (em.message)
		{
		case WM_MOUSEMOVE:
			// 鼠标移动的时候画红色的小点
			putpixel(em.x, em.y, RED);
			break;

		case WM_LBUTTONDOWN:
			//左键下棋
			if (em.x > MAPWIDTH || em.y > MAPHIGHT ||
				em.x < 0 || em.y < 0) continue;
			cur_p->changeCurX(em.x / size);
			cur_p->changeCurY(em.y / size);
			if (checkCanChangeMapVal(cur_p->getCurX(), cur_p->getCurY(), cur_p->getColor()))
			{
				changeMapVal(cur_p->getCurX(), cur_p->getCurY(), cur_p->getColor());
				drawMapVal();
				if (checkWin())
				{
					std::cout << "Win" << std::endl;
					_getch();
				}
				else
				{
					m_cur_p_index = (m_cur_p_index + 1) % 2;
					cur_p = &p[m_cur_p_index];
				}
			}
			break;

		case WM_RBUTTONDOWN:
			//右键悔棋
			clearMap();
			clearMapVal();

			subCurRank();
			changeCurMap();
			drawMapVal();
			m_cur_p_index = (m_cur_p_index + 1) % 2;
			cur_p = &p[m_cur_p_index];
			break;

		}
		//Sleep(50);

	}
}
