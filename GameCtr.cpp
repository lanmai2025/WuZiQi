#include "GameCtr.h"
#include <windows.h>

static bool g_showTipDialog = false;

GameCtr::GameCtr(int x, int y, int rank)
	:m_x(x),m_y(y),m_rank(rank)
{
	m_cur_rank = 0;
	changeBlackSize();
	m_map = vector<vector<vector<Color>>>(rank, vector<vector<Color>>(y, vector<Color>(x,Color::Null)));
	m_cur_map = &m_map[m_cur_rank];
	m_bk_color = (Color)RGB(245, 222, 179);
	m_p1_color = Color::Black;
	m_p2_color = Color::White;
	m_totalSteps = 0;
	m_humanSteps = 0;
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
	drawRightArea();
}

void GameCtr::drawRightArea()
{
	//设置右侧面板背景
	int left = MAPWIDTH + 2 * gap;
	int top = GAMEHIGHT;
	setfillcolor(WHITE);
	fillrectangle(left + 5, gap, GAMEWIDTH - 5, GAMEHIGHT + 5);
	//绘制面板标题
	settextcolor(RGB(0, 0, 139));
	settextstyle(24, 0, _T("宋体"));
	setbkmode(TRANSPARENT);
	outtextxy(left + 20, gap + 20, _T("听说此地会"));
	outtextxy(left + 20, gap + 50, _T("随机刷新提示~"));
	//绘制分割线
	setlinecolor(BLACK);
	line(left + 10, gap + 85, GAMEWIDTH - 10, gap + 85);
	//绘制消息内容
	settextcolor(RGB(0, 0, 0));
	settextstyle(18, 0, _T("楷体"));
	//简单的自动换行显示
	std::wstring msg = m_interactionMsg;
	int lineHeight = 25;
	int startY = gap + 105;
	size_t maxWidth = (GAMEWIDTH - left - 30) / 18;
	//分行显示
	std::vector<std::wstring>lines;
	for (size_t i = 0;i < msg.length(); i += maxWidth)
	{
		lines.push_back(msg.substr(i, maxWidth));
	}
	for (size_t i = 0; i < lines.size() && i < 8;i++)
	{
		outtextxy(left + 15, startY + i * lineHeight, lines[i].c_str());
	}

	drawPrompt();
}

void GameCtr::drawStartBoard()
{
	IMAGE img;
	loadimage(&img,_T("PNG"), MAKEINTRESOURCE(IDB_PNG1), GAMEWIDTH, GAMEHIGHT); 
	putimage(0, 0, &img);
}

// 点击提示按钮
void GameCtr::handleTipButtonClick(Player& currentPlayer)
{
	g_showTipDialog = true;
}

// 关闭弹窗
void GameCtr::handleDialogClose(Player& p1, Player& p2)
{
	g_showTipDialog = false;
	// 刷新界面
	drawBK();
	drawMapLine();
	drawMapVal(p1);
	drawMapVal(p2);
	drawPrompt();
}

// 检查是否点击了提示按钮
bool GameCtr::isTipButtonClicked(int x, int y)
{
	int left = MAPWIDTH + 2 * gap;
	int btnX = left + 10;
	int btnY = gap + 200;
	int btnW = (GAMEWIDTH - 5) - (left + 5) - 10;
	int btnH = (GAMEHIGHT + 5) - btnY - 10;

	return (x >= btnX && x <= btnX + btnW &&
		y >= btnY && y <= btnY + btnH);
}

// 检查是否点击了关闭按钮
bool GameCtr::isCloseBtnClicked(int x, int y)
{
	if (!g_showTipDialog) return false;

	// 计算关闭按钮位置
	const int dialogW = 450;
	const int dialogH = 280;
	int dialogX = (GAMEWIDTH - dialogW) / 2;
	int dialogY = (GAMEHIGHT - dialogH) / 2;
	int closeX = dialogX + dialogW - 35 - 15;
	int closeY = dialogY + 15;

	return (x >= closeX && x <= closeX + 35 &&
		y >= closeY && y <= closeY + 35);
}

void GameCtr::drawPrompt()
{
	//————绘制按钮————

	int left = MAPWIDTH + 2 * gap;
	int btnX = left + 10;
	int btnY = gap + 200;
	int btnW = (GAMEWIDTH - 5) - (left + 5) - 10;
	int btnH = (GAMEHIGHT + 5) - btnY - 10;

	//绘制按钮背景
	setfillcolor(RGB(139, 69, 19));
	setlinecolor(RGB(218, 165, 32));
	fillroundrect(btnX, btnY, btnX + btnW, btnY + btnH, 15, 15);
	//绘制边框
	setlinecolor(BLACK);
	setlinestyle(PS_SOLID, 2);
	roundrect(btnX, btnY, btnX + btnW, btnY + btnH, 15, 15);
	// 绘制文字
	settextcolor(RGB(218, 165, 32));
	settextstyle(32, 0, _T("宋体"));
	setbkmode(TRANSPARENT);

	TCHAR text[] = _T("提示");
	int tw = textwidth(text);
	int th = textheight(text);
	outtextxy(btnX + (btnW - tw) / 2, btnY + (btnH - th) / 2 - 10, text);

	settextstyle(18, 0, _T("宋体"));
	settextcolor(RGB(255, 240, 180));
	TCHAR subText[] = _T("点一下试试？");
	int sw = textwidth(subText);
	outtextxy(btnX + (btnW - sw) / 2, btnY + (btnH - th) / 2 + 30, subText);

	settextstyle(14, 0, _T("宋体"));
	settextcolor(RGB(180, 200, 230));
	TCHAR smallText[] = _T("（小心被嘲讽）");
	int sw2 = textwidth(smallText);
	outtextxy(btnX + (btnW - sw2) / 2, btnY + btnH - 25, smallText);

	//————绘制弹窗————
	if (g_showTipDialog)
	{
		//绘制弹窗大小
		const int dialogW = 450;
		const int dialogH = 280;
		const int closeW = 35;
		const int closeH = 35;
		// 弹窗居中
		int dialogX = (GAMEWIDTH - dialogW) / 2;
		int dialogY = (GAMEHIGHT - dialogH) / 2;
		// 关闭按钮位置
		int closeX = dialogX + dialogW - closeW - 15;
		int closeY = dialogY + 15;

		// 弹窗背景
		setfillcolor(RGB(245, 245, 245));
		setlinecolor(BLACK);
		fillroundrect(dialogX, dialogY, dialogX + dialogW, dialogY + dialogH, 20, 20);

		setlinecolor(BLACK);
		setlinestyle(PS_SOLID, 3);
		roundrect(dialogX, dialogY, dialogX + dialogW, dialogY + dialogH, 20, 20);

		// 关闭按钮
		setfillcolor(RGB(200, 60, 60));
		fillroundrect(closeX, closeY, closeX + closeW, closeY + closeH, 8, 8);
		settextcolor(RGB(255, 255, 255));
		settextstyle(24, 0, _T("宋体"));
		outtextxy(closeX + 12, closeY + 5, _T("X"));

		// 弹窗文字
		settextcolor(BLACK);
		settextstyle(28, 0, _T("宋体"));
		setbkmode(TRANSPARENT);

		TCHAR line1[] = _T("玩个五子棋还看提示！");
		int tw1 = textwidth(line1);
		outtextxy(dialogX + (dialogW - tw1) / 2, dialogY + 80, line1);

		settextcolor(RGB(255, 100, 100));
		settextstyle(36, 0, _T("宋体"));
		TCHAR line2[] = _T("人类一败涂地！");
		int tw2 = textwidth(line2);
		outtextxy(dialogX + (dialogW - tw2) / 2, dialogY + 140, line2);
	}
	

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

void GameCtr::drawPauseTable()
{
	
}

void GameCtr::handleWinner(Player& winner, bool isFirstPlayer, bool isAIMode)
{
	SettlementAction action = showWinner(winner, isFirstPlayer, isAIMode);
	if (action == SettlementAction::RESTART)
	{
		ExMessage newEm;
		if (isAIMode)
		{
			gameLoopAI(newEm);
		}
		else
		{
			gameLoop(newEm);
		}
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
	m_totalSteps = 0;
	m_humanSteps = 0;
	m_interactionMsg.clear();//对局结束后清空消息
	
}


void GameCtr::showInteractionMessage(const wchar_t* msg, Player& cur_p)
{
	m_interactionMsg = msg;
}

void GameCtr::checkAndShowMessage(int steps, Player& cur_p)
{
	switch (steps)
	{
	case 10:
		showInteractionMessage(L"怎么还没赢啊？你们在试探什么", cur_p);
		break;
	case 15:
		showInteractionMessage(L"打得好文明呐~现代文明人~", cur_p);
		break;
	case 20:
		showInteractionMessage(L"已解锁20步成就。谁要赢了？你吗", cur_p);
		break;
	case 30:
		showInteractionMessage(L"你们是不是忘记怎么赢了", cur_p);
		break;
	case 40:
		showInteractionMessage(L"棋盘都要下满了！", cur_p);
		break;
	default:
		break;
	}
}

void GameCtr::checkAndShowAIMessage(int steps, Player& human_p)
{
	switch (steps)
	{
	case 3:
		showInteractionMessage(L"AI：这个开局还行吧~", human_p);
		break;
	case 5:
		showInteractionMessage(L"AI：谁快赢了？", human_p);
		break;
	case 8:
		showInteractionMessage(L"AI：居然让我这个水平的AI下到了第8步", human_p);
		break;
	case 10:
		showInteractionMessage(L"AI:不是吧，你还没赢！", human_p);
		break;
	case 15:
		showInteractionMessage(L"AI:如果我赢了，我将说出那句话", human_p);
		break;
	default:
		break;
	}
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
		em = getmessage(EX_MOUSE | EX_KEY);
		
		switch (em.message)
		{
		case WM_LBUTTONDOWN:
			
			//弹窗关闭
			if (isCloseBtnClicked(em.x, em.y))
			{
				handleDialogClose(p[0], p[1]);
				break;
			}
			//点击提示按钮
			if (isTipButtonClicked(em.x, em.y))
			{
				handleTipButtonClick(*cur_p);
				// 刷新界面显示弹窗
				drawBK();
				drawMapLine();
				drawMapVal(p[0]);
				drawMapVal(p[1]);
				drawPrompt();
				break;
			}

			//弹窗打开时，不能下棋
			if (g_showTipDialog)
			{
				break;  
			}

			//左键下棋
			if (em.x > MAPWIDTH || em.y > MAPHIGHT ||
				em.x < 0 || em.y < 0) continue;
			cur_p->changeCurX(em.x / size);
			cur_p->changeCurY(em.y / size);

			if (checkCanChangeMapVal(cur_p->getCurX(), cur_p->getCurY(), cur_p->getColor()))
			{
				m_totalSteps++;

				checkAndShowMessage(m_totalSteps, *cur_p);
				//落子
				changeMapVal(cur_p->getCurX(), cur_p->getCurY(), cur_p->getColor());
				drawMapVal(*cur_p);
				
				//统一刷新一次界面
				drawBK();
				drawMapLine();
				drawMapVal(*cur_p);
				drawPrompt();

				if (checkWin(*cur_p))
				{
					bool isFirstPlayer = (cur_p == &p[0]);
					handleWinner(*cur_p, isFirstPlayer, false);
					return;
				}
				else
				{
					m_cur_p_index = (m_cur_p_index + 1) % 2;
					cur_p = &p[m_cur_p_index];
				}
			}
			if (em.x > MAPWIDTH || em.y > MAPHIGHT || em.x < 0 || em.y < 0) continue;
			cur_p->changeCurX(em.x / size);
			cur_p->changeCurY(em.y / size);

		    
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
			m_totalSteps--;
			
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
		//Sleep(10);

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

		em = getmessage(EX_MOUSE | EX_KEY);


		switch (em.message)
		{
			case WM_LBUTTONDOWN:
				
				// 弹窗关闭
				if (isCloseBtnClicked(em.x, em.y))
				{
					handleDialogClose(p, p);  // 人机模式只有一个玩家，传同一个
					break;
				}

				// 处理提示按钮点击
				if (isTipButtonClicked(em.x, em.y))
				{
					handleTipButtonClick(p);
					drawBK();
					drawMapLine();
					drawMapVal(p);
					drawPrompt();
					break;
				}
				
				//弹窗打开时，不能下棋
				if (g_showTipDialog)
				{
					break;
				}


				//左键下棋
				if (em.x > MAPWIDTH || em.y > MAPHIGHT ||
					em.x < 0 || em.y < 0) continue;
				p.changeCurX(em.x / size);
				p.changeCurY(em.y / size);
				if (checkCanChangeMapVal(p.getCurX(), p.getCurY(), p.getColor()))
				{
					m_humanSteps++;
					checkAndShowAIMessage(m_humanSteps, p);

					changeMapVal(p.getCurX(), p.getCurY(), p.getColor());
					drawMapVal(p);

					drawBK();
					drawMapLine();
					drawMapVal(p);

					if (checkWin(p))
					{
						handleWinner(p, true, true);
						return;
					}
					else
					{
						AI.changeMap(m_cur_map);
						if (AI.changeCurPos(p))
						{
							changeMapVal(AI.getCurX(), AI.getCurY(), AI.getColor());
							drawMapVal(AI);
							//刷新右侧面板
							drawBK();
							drawMapLine();
							drawMapVal(p);
							drawMapVal(AI);

							if (checkWin(AI))
							{
								handleWinner(AI, false, true);
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
				clearMapVal();
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
		//Sleep(10);
	}

}

GameCtr::SettlementAction GameCtr::showWinner(Player& winner, bool isFirstPlayer, bool isAIMode)
{
	//开始批量绘图
	BeginBatchDraw();

	IMAGE settleBg;
	loadimage(&settleBg, _T("PNG"), MAKEINTRESOURCE(IDB_SETTLE_BG), GAMEWIDTH, GAMEHIGHT);
	putimage(0, 0, &settleBg);

	settextcolor(RGB(255, 215, 0));
	settextstyle(48, 0, _T("宋体"));
	setbkmode(TRANSPARENT);

	TCHAR winText[100];

	if (isAIMode)
	{
		if (isFirstPlayer)
		{
			_stprintf_s(winText, _T("人类战胜AI"));
		}
		else
		{
			_stprintf_s(winText, _T("人类一败涂地"));
		}
	}
	else
	{
		if (isFirstPlayer)
		{
			_stprintf_s(winText, _T("先手胜利！你很强哦~"));
		}
		else
			_stprintf_s(winText, _T("后手胜利！你很强哦~"));
	}

	//居中
	int textWidth = textwidth(winText);
	outtextxy((GAMEWIDTH - textWidth) / 2, GAMEHIGHT / 2 - 50, winText);
	
	//刷新显示背景和文字
	FlushBatchDraw();

	//定义按钮
	const int btnWidth = 160;
	const int btnHeight = 55;
	const int btnSpacing = 40;
	const int btnY = GAMEHIGHT - 150;

	int restartX = GAMEWIDTH / 2 - btnWidth - btnSpacing / 2;
	int menuX = GAMEWIDTH / 2 + btnSpacing / 2;

	//绘制按钮并等待点击
	ExMessage Msg;
	while (true)
	{
		//再来一局按钮
		setfillcolor(RGB(192, 192, 192));
		setlinecolor(RGB(255, 250, 240));
		fillroundrect(restartX, btnY, restartX + btnWidth, btnY + btnHeight, 15, 15);
		//settextcolor(WHITE);
		settextcolor(RGB(0, 0, 0));  
		settextstyle(28, 0, _T("宋体"));
		settextstyle(28, 0, _T("宋体"));
		setbkmode(TRANSPARENT);
		outtextxy(restartX + 35, btnY + 15, _T("再来一局"));

		//返回菜单按钮
		//setfillcolor(RGB(169, 169, 169));
		setfillcolor(RGB(192, 192, 192));  
		setlinecolor(RGB(255, 250, 240));
		fillroundrect(menuX, btnY, menuX + btnWidth, btnY + btnHeight, 15, 15);
		outtextxy(menuX + 32, btnY + 15, _T("返回菜单"));

		//刷新显示按钮
		FlushBatchDraw();

		//检测鼠标点击
		if (peekmessage(&Msg, EX_MOUSE))
		{
			if (Msg.message == WM_LBUTTONDOWN)
			{
				int mx = Msg.x;
				int my = Msg.y;

				//检查“再来一局”按钮
				if (mx >= restartX && mx <= restartX + btnWidth && my >= btnY && my <= btnY + btnHeight)
				{
					EndBatchDraw();//结束批量绘图
					clearGameData();
					return SettlementAction::RESTART;
				}

				//检查“返回菜单”按钮
				if (mx >= menuX && mx <= menuX + btnWidth && my >= btnY && my <= btnY + btnHeight)
				{
					EndBatchDraw();//结束批量绘图
					clearGameData();
					return SettlementAction::BACK_TO_MENU;
				}

			}
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
			if (peekmessage(&em, EX_MOUSE | EX_KEY)) {
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
				else if (em.message == WM_KEYDOWN)
				{

					if (em.vkcode == VK_ESCAPE)
					{
						Sleep(50);
						//closegraph();
						return;
					}
				}
			}
			Sleep(10);
		}
	closegraph();

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
	const int size_box_width = 80;  // 尺寸选择框宽度
	const int button_width = 120;
	const int button_height = 40;

	// 尺寸选项
	int size_options[] = {15, 20, 30};

	// 颜色选择框是否显示
	bool show_color_picker = false;
	int color_picker_for = -1; // 0:背景色, 1:玩家1, 2:玩家2

	// 尺寸选择框是否显示
	bool show_size_picker = false;
	int size_picker_for = -1; // 0:宽度, 1:高度

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
		setfillcolor(LIGHTGRAY);
		fillrectangle(250, start_y + 3 * (item_height + item_spacing),
			250 + size_box_width, start_y + 3 * (item_height + item_spacing) + item_height);
		rectangle(250, start_y + 3 * (item_height + item_spacing),
			250 + size_box_width, start_y + 3 * (item_height + item_spacing) + item_height);
		
		TCHAR width_text[32];
		_stprintf_s(width_text, _T("%d"), Map_y);
		outtextxy(255, start_y + 3 * (item_height + item_spacing) + 10, width_text);

		// 地图高度
		outtextxy(100, start_y + 4 * (item_height + item_spacing), _T("地图高度:"));
		setfillcolor(LIGHTGRAY);
		fillrectangle(250, start_y + 4 * (item_height + item_spacing),
			250 + size_box_width, start_y + 4 * (item_height + item_spacing) + item_height);
		rectangle(250, start_y + 4 * (item_height + item_spacing),
			250 + size_box_width, start_y + 4 * (item_height + item_spacing) + item_height);
		
		TCHAR height_text[32];
		_stprintf_s(height_text, _T("%d"), Map_y);
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

		// 尺寸选择框（如果显示）
		if (show_size_picker) {
			setfillcolor(WHITE);
			fillrectangle(400, start_y, 500, start_y + 120);
			rectangle(400, start_y, 500, start_y + 120);
			outtextxy(410, start_y + 10, _T("选择尺寸:"));

			for (int i = 0; i < 3; i++) {
				setfillcolor(LIGHTGRAY);
				fillrectangle(410, start_y + 40 + i * 30, 490, start_y + 40 + i * 30 + 25);
				rectangle(410, start_y + 40 + i * 30, 490, start_y + 40 + i * 30 + 25);
				
				TCHAR size_text[8];
				_stprintf_s(size_text, _T("%d"), size_options[i]);
				outtextxy(430, start_y + 40 + i * 30 + 5, size_text);
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

				// 检查尺寸选择框点击
				if (show_size_picker) {
					if (x >= 400 && x <= 500 && y >= start_y && y <= start_y + 120) {
						for (int i = 0; i < 3; i++) {
							if (x >= 410 && x <= 490 &&
								y >= start_y + 40 + i * 30 && y <= start_y + 40 + i * 30 + 25) {
								// 更新对应尺寸
								switch (size_picker_for) {
								case 0: Map_x = size_options[i]; break;
								case 1: Map_y = size_options[i]; break;
								}
								show_size_picker = false;
								break;
							}
						}
					}
					else {
						show_size_picker = false;
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

				// 地图宽度选择框
				if (x >= 250 && x <= 250 + size_box_width &&
					y >= start_y + 3 * (item_height + item_spacing) &&
					y <= start_y + 3 * (item_height + item_spacing) + item_height) {
					show_size_picker = true;
					size_picker_for = 0;
					drawInterface();
					continue;
				}

				// 地图高度选择框
				if (x >= 250 && x <= 250 + size_box_width &&
					y >= start_y + 4 * (item_height + item_spacing) &&
					y <= start_y + 4 * (item_height + item_spacing) + item_height) {
					show_size_picker = true;
					size_picker_for = 1;
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
					changeX(Map_y);
					changeY(Map_y);
					changeMap();
					changeBlackSize();
					return true;
				}
				break;

			case WM_KEYDOWN:
				if (em.vkcode == VK_ESCAPE) {
					if (show_color_picker) {
						show_color_picker = false;
						drawInterface();
					}
					else if (show_size_picker) {
						show_size_picker = false;
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
	m_map = vector<vector<vector<Color>>>(m_rank, vector<vector<Color>>(m_y, vector<Color>(m_y, Color::Null)));
	return true;
}


void GameCtr::fillBK()
{
	setfillcolor((long long)m_bk_color);
	fillrectangle(gap, gap, GAMEWIDTH - gap, GAMEHIGHT - gap);
}

const TCHAR* GetColorDisplayName(COLORREF color) {
	if (color == RGB(255, 0, 0))   return _T("红方");
	if (color == RGB(0, 0, 255))   return _T("蓝方");
	if (color == RGB(0, 128, 0))   return _T("绿方");
	if (color == RGB(255, 255, 0)) return _T("黄方");
	return _T("当前颜色");
}

