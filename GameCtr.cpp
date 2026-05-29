#include "GameCtr.h"

GameCtr::GameCtr(int x, int y, int rank)
	:m_x(x),m_y(y),m_rank(rank)
{
	m_cur_rank = 0;
	changeBlackSize();
	m_map = vector<vector<vector<Color>>>(rank, vector<vector<Color>>(y, vector<Color>(x,Color::Null)));
	m_cur_map = &m_map[m_cur_rank];
	m_bk_color = Color::White;
	m_p1_color = Color::Black;
	m_p2_color = Color::Red;
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
	fillBK();

	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 5);		//更改线样式
	int left = MAPWIDTH + 2 * gap;
	int top = GAMEHIGHT;
	line(left, gap, left , top);
}

void GameCtr::drawStartBoard()
{
	IMAGE img;
	loadimage(&img,_T("PNG"), MAKEINTRESOURCE(IDB_PNG1), GAMEWIDTH, GAMEHIGHT); 
	putimage(0, 0, &img);
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

void GameCtr::drawMapVal(Player& cur_p)
{
	//Player& cur_p = p[m_cur_p_index];

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

void GameCtr::clearGameData()
{
	//清空地图数据
	for (int rank = 0; rank < m_rank; ++rank)
	{
		for (int y = 0; y < m_y; ++y)
			for (int x = 0; x < m_x; ++x)
				m_map[rank][y][x] = Color::Null;
	}

	m_cur_rank = 0;
	changeCurMap();
}

bool GameCtr::checkWin(Player& cur_p)  
{
	//Player& cur_p = p[m_cur_p_index];
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
		else break;

	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		if (x < 0) break;
		if ((*m_cur_map)[cur_y][x] == c)
			++cnt;
		else break;

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
		else break;
	}
	for (int i = 1; i < 5; ++i)
	{
		int y = cur_y - i;
		if (y < 0) break;
		if ((*m_cur_map)[y][cur_x] == c)
			++cnt;
		else break;
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
		else break;
	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		int y = cur_y - i;
		if (x < 0 || y < 0) break;
		if ((*m_cur_map)[y][x] == c)
			++cnt;
		else break;
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
		else break;
	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		int y = cur_y + i;
		if (x < 0 || y >= m_y) break;
		if ((*m_cur_map)[y][x] == c)
			++cnt;
		else break;
	}
	if (cnt >= 5) return true;

	return false;
}

bool GameCtr::checkCanChangeMapVal(int x, int y, Color c)
{
	if ((*m_cur_map)[y][x] == Color::Null) return true;
	return false;
}

void GameCtr::gameLoop(ExMessage& em)
{
	em = {};
	clearGameData();
	drawBK();
	drawMapLine();

	//Player* cur_p = &p[m_cur_p_index];
	Player p[2] = {
		Player(0, 0, m_p1_color),
		Player(0, 0, m_p2_color)
	};
	int size = getBlockSize() + 1;
	int m_cur_p_index = 0;
	Player* cur_p = &p[m_cur_p_index];

	bool running = true;
	while (running)
	{
		peekmessage(&em, EX_MOUSE|EX_KEY);

		switch (em.message)
		{
		case WM_LBUTTONDOWN:
			//左键下棋
			if (em.x > MAPWIDTH || em.y > MAPHIGHT ||
				em.x < 0 || em.y < 0) continue;
			cur_p->changeCurX(em.x / size);
			cur_p->changeCurY(em.y / size);
			if (checkCanChangeMapVal(cur_p->getCurX(), cur_p->getCurY(), cur_p->getColor()))
			{
				changeMapVal(cur_p->getCurX(), cur_p->getCurY(), cur_p->getColor());
				drawMapVal(*cur_p);
				if (checkWin(*cur_p))
				{
					std::cout << "Win" << std::endl;
					//绘制赢了的界面
					clearGameData();
					running = false;
					return;
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
			drawMapVal(*cur_p);
			m_cur_p_index = (m_cur_p_index + 1) % 2;
			cur_p = &p[m_cur_p_index];
			break;


			// ESC键退出
		case WM_KEYDOWN:
			if (em.vkcode == VK_ESCAPE)
			{
				running = false;
				clearGameData();
				return;
			}
			break;
		}
		Sleep(10);

	}
}

void GameCtr::gameLoopAI(ExMessage& em)
{
	em = {};
	clearGameData();
	//init();
	drawBK();
	drawMapLine();

	//ExMessage em = getmessage(EX_MOUSE);

	Player p = Player(0, 0, m_p1_color);
	AIPlayer AI = AIPlayer(getX(), getY(), m_p2_color, m_cur_map);

	int size = getBlockSize() + 1;

	bool running = true;
	while (running)
	{
		peekmessage(&em,EX_MOUSE|EX_KEY);

		switch (em.message)
		{
			case WM_LBUTTONDOWN:
				//左键下棋
				if (em.x > MAPWIDTH || em.y > MAPHIGHT ||
					em.x < 0 || em.y < 0) continue;
				p.changeCurX(em.x / size);
				p.changeCurY(em.y / size);
				if (checkCanChangeMapVal(p.getCurX(), p.getCurY(), p.getColor()))
				{
					changeMapVal(p.getCurX(), p.getCurY(), p.getColor());
					drawMapVal(p);
					if (checkWin(p))
					{
						std::cout << "Player Win" << std::endl;
						//绘制赢了的界面
						clearGameData();
						running = false;
						return;
					}
					else
					{
						AI.changeMap(m_cur_map);
						if (AI.changeCurPos(p))
						{
							changeMapVal(AI.getCurX(), AI.getCurY(), AI.getColor());
							drawMapVal(AI);
							if (checkWin(AI))
							{
								std::cout << "AI Win" << std::endl;
								//绘制赢了的界面
								clearGameData();
								running = false;
								return;
							}
						}
					}
				}
				break;
			case WM_RBUTTONDOWN:
				//右键悔棋
				clearMap();
				clearMapVal();

				subCurRank();
				subCurRank();
				changeCurMap();
				drawMapVal(p);
				AI.changeMap(m_cur_map);
				break;

				//ESC键退出
			case WM_KEYDOWN:
				if (em.vkcode == VK_ESCAPE) 
				{
					running = false;
					clearGameData();
					return;
				}
				break;
		}
		Sleep(10);
	}

}

void GameCtr::menu()
{
	bool should_exit = false;

	while (!should_exit) {
		// 每次循环都重新绘制菜单
		init();
		drawBK();
		drawMapLine();
		drawStartBoard();

		// 绘制菜单按钮
		setlinecolor(RED);
		int sx = GAMEWIDTH / 2 - 60;
		int ex = GAMEWIDTH / 2 + 100;
		int y1 = GAMEHIGHT / 2 - 90;
		int y2 = GAMEHIGHT / 2 - 40;
		int y3 = GAMEHIGHT / 2 + 30;
		int y4 = GAMEHIGHT / 2 + 80;

		ExMessage em;
		bool menu_handled = false;

		while (!menu_handled) {
			if (peekmessage(&em, EX_MOUSE)) {
				if (em.message == WM_LBUTTONDOWN) {
					int x = em.x;
					int y = em.y;

					if (x >= sx && x <= ex) {
						if (y >= y1 && y <= y2) {
							// 开始游戏
							cleardevice();
							ExMessage new_em;
							gameLoop(new_em);
							menu_handled = true;  // 游戏结束，重新显示菜单
						}
						else if (y >= y2 && y <= y3) {
							// AI对战
							cleardevice();
							ExMessage new_em;
							gameLoopAI(new_em);
							menu_handled = true;
						}
						else if (y >= y3 && y <= y4) {
							// 游戏设置
							cleardevice();
							ExMessage new_em;
							gameSet(new_em);
							menu_handled = true;
						}
					}
				}
			}
			Sleep(10);
		}
	}
}




bool GameCtr::gameSet(ExMessage& em)
{
	cleardevice();
	fillBK();
	Color bk_color = m_bk_color;
	Color p1_color = m_p1_color;
	Color p2_color = m_p2_color;
	int Map_x = getX();
	int Map_y = getY();

	// 定义界面元素位置和尺寸
	const int item_height = 40;
	const int item_spacing = 20;
	const int start_y = 100;
	const int label_width = 120;
	const int color_box_size = 30;
	const int input_width = 100;
	const int button_width = 120;
	const int button_height = 40;

	// 当前选中的项目（用于输入框）
	int selected_item = -1;
	TCHAR input_text[32] = _T("");  // 改为TCHAR数组

	// 颜色选择框是否显示
	bool show_color_picker = false;
	int color_picker_for = -1; // 0:背景色, 1:玩家1, 2:玩家2

	// 预定义颜色选项
	Color color_options[] = {
		Color::White, Color::Black, Color::Red, Color::Green,
		Color::Blue, Color::Yellow, Color::Cyan, Color::Magenta
	};

	// 绘制初始界面
	auto drawInterface = [&]() {
		cleardevice();
		fillBK();

		settextcolor(BLACK);
		settextstyle(20, 0, _T("宋体"));
		setbkmode(TRANSPARENT);

		// 标题
		outtextxy(GAMEWIDTH / 2 - 60, 50, _T("游戏设置"));

		// 背景颜色设置
		outtextxy(100, start_y, _T("背景颜色:"));
		setfillcolor((long long) bk_color);
		fillrectangle(250, start_y, 250 + color_box_size, start_y + color_box_size);
		rectangle(250, start_y, 250 + color_box_size, start_y + color_box_size);

		// 玩家1颜色
		outtextxy(100, start_y + item_height + item_spacing, _T("玩家1颜色:"));
		setfillcolor((long long) p1_color);
		fillrectangle(250, start_y + item_height + item_spacing,
			250 + color_box_size, start_y + item_height + item_spacing + color_box_size);
		rectangle(250, start_y + item_height + item_spacing,
			250 + color_box_size, start_y + item_height + item_spacing + color_box_size);

		// 玩家2颜色
		outtextxy(100, start_y + 2 * (item_height + item_spacing), _T("玩家2颜色:"));
		setfillcolor((long long) p2_color);
		fillrectangle(250, start_y + 2 * (item_height + item_spacing),
			250 + color_box_size, start_y + 2 * (item_height + item_spacing) + color_box_size);
		rectangle(250, start_y + 2 * (item_height + item_spacing),
			250 + color_box_size, start_y + 2 * (item_height + item_spacing) + color_box_size);

		// 地图宽度
		outtextxy(100, start_y + 3 * (item_height + item_spacing), _T("地图宽度:"));
		if (selected_item == 0) {
			setlinecolor(RED); // 选中状态高亮
		}
		else {
			setlinecolor(BLACK);
		}
		rectangle(250, start_y + 3 * (item_height + item_spacing),
			250 + input_width, start_y + 3 * (item_height + item_spacing) + item_height);
		setlinecolor(BLACK);

		// 使用TCHAR字符串输出
		TCHAR width_text[32];
		if (selected_item == 0 && _tcslen(input_text) > 0) {
			_tcscpy_s(width_text, input_text);
		}
		else {
			_stprintf_s(width_text, _T("%d"), Map_x);
		}
		outtextxy(255, start_y + 3 * (item_height + item_spacing) + 10, width_text);

		// 地图高度
		outtextxy(100, start_y + 4 * (item_height + item_spacing), _T("地图高度:"));
		if (selected_item == 1) {
			setlinecolor(RED);
		}
		else {
			setlinecolor(BLACK);
		}
		rectangle(250, start_y + 4 * (item_height + item_spacing),
			250 + input_width, start_y + 4 * (item_height + item_spacing) + item_height);
		setlinecolor(BLACK);

		// 修正：使用TCHAR字符串输出
		TCHAR height_text[32];
		if (selected_item == 1 && _tcslen(input_text) > 0) {
			_tcscpy_s(height_text, input_text);
		}
		else {
			_stprintf_s(height_text, _T("%d"), Map_y);
		}
		outtextxy(255, start_y + 4 * (item_height + item_spacing) + 10, height_text);

		// 确认按钮
		setfillcolor(LIGHTGRAY);
		fillrectangle(GAMEWIDTH / 2 - button_width / 2, start_y + 5 * (item_height + item_spacing),
			GAMEWIDTH / 2 + button_width / 2, start_y + 5 * (item_height + item_spacing) + button_height);
		rectangle(GAMEWIDTH / 2 - button_width / 2, start_y + 5 * (item_height + item_spacing),
			GAMEWIDTH / 2 + button_width / 2, start_y + 5 * (item_height + item_spacing) + button_height);
		outtextxy(GAMEWIDTH / 2 - 30, start_y + 5 * (item_height + item_spacing) + 10, _T("确认"));

		// 颜色选择框（如果显示）
		if (show_color_picker) {
			setfillcolor(WHITE);
			fillrectangle(400, start_y, 600, start_y + 200);
			rectangle(400, start_y, 600, start_y + 200);
			outtextxy(410, start_y + 10, _T("选择颜色:"));

			for (int i = 0; i < 8; i++) {
				int row = i / 4;
				int col = i % 4;
				setfillcolor((long long) color_options[i]);
				fillrectangle(410 + col * 45, start_y + 40 + row * 40,
					410 + col * 45 + 40, start_y + 40 + row * 40 + 30);
				rectangle(410 + col * 45, start_y + 40 + row * 40,
					410 + col * 45 + 40, start_y + 40 + row * 40 + 30);
			}
		}
		};

	drawInterface();

	int x, y;

	// 主循环
	while (true) {
		if (peekmessage(&em, EX_MOUSE | EX_KEY)) {
			switch (em.message) {
			case WM_LBUTTONDOWN:
				x = em.x;
				y = em.y;
				// 检查颜色选择框点击
				if (show_color_picker) {
					if (x >= 400 && x <= 600 && y >= start_y && y <= start_y + 200) {
						for (int i = 0; i < 8; i++) {
							int row = i / 4;
							int col = i % 4;
							if (x >= 410 + col * 45 && x <= 410 + col * 45 + 40 &&
								y >= start_y + 40 + row * 40 && y <= start_y + 40 + row * 40 + 30) {
								// 更新对应颜色
								switch (color_picker_for) {
								case 0: bk_color = color_options[i]; break;
								case 1: p1_color = color_options[i]; break;
								case 2: p2_color = color_options[i]; break;
								}
								show_color_picker = false;
								break;
							}
						}
					}
					else {
						show_color_picker = false;
					}
					drawInterface();
					continue;
				}

				// 背景颜色选择
				if (x >= 250 && x <= 250 + color_box_size &&
					y >= start_y && y <= start_y + color_box_size) {
					show_color_picker = true;
					color_picker_for = 0;
					drawInterface();
					continue;
				}

				// 玩家1颜色选择
				if (x >= 250 && x <= 250 + color_box_size &&
					y >= start_y + item_height + item_spacing &&
					y <= start_y + item_height + item_spacing + color_box_size) {
					show_color_picker = true;
					color_picker_for = 1;
					drawInterface();
					continue;
				}

				// 玩家2颜色选择
				if (x >= 250 && x <= 250 + color_box_size &&
					y >= start_y + 2 * (item_height + item_spacing) &&
					y <= start_y + 2 * (item_height + item_spacing) + color_box_size) {
					show_color_picker = true;
					color_picker_for = 2;
					drawInterface();
					continue;
				}

				// 地图宽度输入框
				if (x >= 250 && x <= 250 + input_width &&
					y >= start_y + 3 * (item_height + item_spacing) &&
					y <= start_y + 3 * (item_height + item_spacing) + item_height) {
					selected_item = 0;
					_stprintf_s(input_text, _T("%d"), Map_x);
					drawInterface();
					continue;
				}

				// 地图高度输入框
				if (x >= 250 && x <= 250 + input_width &&
					y >= start_y + 4 * (item_height + item_spacing) &&
					y <= start_y + 4 * (item_height + item_spacing) + item_height) {
					selected_item = 1;
					_stprintf_s(input_text, _T("%d"), Map_y);
					drawInterface();
					continue;
				}

				// 确认按钮
				if (x >= GAMEWIDTH / 2 - button_width / 2 && x <= GAMEWIDTH / 2 + button_width / 2 &&
					y >= start_y + 5 * (item_height + item_spacing) &&
					y <= start_y + 5 * (item_height + item_spacing) + button_height) {
					// 保存设置并返回
					setBKColor(bk_color);
					setP1Color(p1_color);
					setP2Color(p2_color);
					if (_tcslen(input_text) > 0) {
						int value = _ttoi(input_text);
						if (selected_item == 0) Map_x = value;
						else if (selected_item == 1) Map_y = value;
						changeX(Map_x);
						changeY(Map_y);
						changeMap();
						changeBlackSize();
					}
					return true;
				}
				break;

			case WM_CHAR:
				if (selected_item >= 0) {
					if (em.ch >= _T('0') && em.ch <= _T('9')) {
						if (_tcslen(input_text) < 10) { // 限制长度
							TCHAR new_char[2] = { em.ch, _T('\0') };
							_tcscat_s(input_text, new_char);
						}
					}
					else if (em.ch == _T('\b') && _tcslen(input_text) > 0) {
						input_text[_tcslen(input_text) - 1] = _T('\0');
					}
					drawInterface();
				}
				break;

			case WM_KEYDOWN:
				if (em.vkcode == VK_ESCAPE) {
					if (show_color_picker) {
						show_color_picker = false;
						drawInterface();
					}
					else if (selected_item >= 0) {
						selected_item = -1;
						input_text[0] = _T('\0');
						drawInterface();
					}
					else {
						return true; // 直接返回菜单
					}
				}
				break;
			}
		}
		Sleep(10);
	}

	return true;
}


bool GameCtr::setBKColor(Color c)
{
	m_bk_color = c;
	return true;
}

bool GameCtr::setP1Color(Color c)
{
	m_p1_color = c;
	return true;
}

bool GameCtr::setP2Color(Color c)
{
	m_p2_color = c;
	return true;
}
bool GameCtr::changeMap()
{
	m_map = vector<vector<vector<Color>>>(m_rank, vector<vector<Color>>(m_y, vector<Color>(m_x, Color::Null)));
	return true;
}


void GameCtr::fillBK()
{
	setfillcolor((long long)m_bk_color);
	fillrectangle(gap, gap, GAMEWIDTH - gap, GAMEHIGHT - gap);
}
