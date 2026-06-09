#include "Player.h"

Player::Player(int x, int y, Color c)
	:m_cur_x(x), m_cur_y(y), m_color(c)
{
	m_size = 8;
}

int Player::getCurX() const
{
	return m_cur_x;
}

int Player::getCurY() const
{
	return m_cur_y;
}

Color Player::getColor() const
{
	return m_color;
}

int Player::getPlayerSize() const
{
	return m_size;
}

bool Player::changeCurX(int x)
{
	m_cur_x = x;
	return true;
}

bool Player::changeCurY(int y)
{
	m_cur_y = y;
	return true;
}

bool Player::changeColor(Color color)
{
	m_color = color;
	return true;
}

bool Player::changePlayerSize(int size)
{
	m_size = size;
	return true;
}

AIPlayer::AIPlayer(int x, int y, Color c, vector<vector<Color>>* p)
	:Player(0, 0, c), m_map(p), m_x(x), m_y(y)
{
}

bool AIPlayer::changeMap(vector<vector<Color>>* p)
{
	m_map = p;
	return false;
}

bool AIPlayer::changeCurPos(Player& p)
{
	int cur_x = p.getCurX();
	int cur_y = p.getCurY();
	Score max_score(0, 0);
	for (int y = cur_y; y < m_y; ++y)
	{
		for (int x = cur_x; x < m_x; ++x)
		{
			if ((*m_map)[y][x] == Color::Null)
			{
				Score s = getScore(x, y);
				if (s.attack_score > 2 || s.defend_score > 2)
				{
					changeCurX(x);
					changeCurY(y);
					return true;
				}
				else if (s > max_score)
				{
					max_score = s;
					changeCurX(x);
					changeCurY(y);
				}
			}
		}
	}
	for (int y = 0; y < cur_y; ++y)
	{
		for (int x = 0; x < m_x; ++x)
		{
			if ((*m_map)[y][x] == Color::Null)
			{
				Score s = getScore(x, y);
				if (s.attack_score > 3 || s.defend_score > 3)
				{
					changeCurX(x);
					changeCurY(y);
					return true;
				}
				else if (s > max_score)
				{
					max_score = s;
					changeCurX(x);
					changeCurY(y);
				}
			}
		}
	}
	return true;
}

Score AIPlayer::getScore(int cur_x,int cur_y)
{
	Score s(0, 0), ans(0,0);
	
	//查x轴
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x + i;
		if (x >= m_x) break;
		if ((*m_map)[cur_y][x] == getColor())
			++s.attack_score;
		else if ((*m_map)[cur_y][x] != Color::Null)
			++s.defend_score;
		else break;
	}

	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		if (x < 0) break;
		if ((*m_map)[cur_y][x] == getColor())
			++s.attack_score;
		else if ((*m_map)[cur_y][x] != Color::Null)
			++s.defend_score;
		else break;
	}

	ans = s > ans ? s : ans;
	s = Score(0, 0);

	//查y轴
	for (int i = 1; i < 5; ++i)
	{
		int y = cur_y + i;
		if (y >= m_y) break;
		if ((*m_map)[y][cur_x] == getColor())
			++s.attack_score;
		else if ((*m_map)[y][cur_x] != Color::Null)
			++s.defend_score;
		else break;

	}
	for (int i = 1; i < 5; ++i)
	{
		int y = cur_y - i;
		if (y < 0) break;
		if ((*m_map)[y][cur_x] == getColor())
			++s.attack_score;
		else if ((*m_map)[y][cur_x] != Color::Null)
			++s.defend_score;
		else break;

	}
	ans = s > ans ? s : ans;
	s = Score(0, 0);

	//查斜线
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x + i;
		int y = cur_y + i;
		if (x >= m_x || y >= m_y) break;
		if ((*m_map)[y][x] == getColor())
			++s.attack_score;
		else if ((*m_map)[y][x] != Color::Null)
			++s.defend_score;
		else break;

	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		int y = cur_y - i;
		if (x < 0 || y < 0) break;
		if ((*m_map)[y][x] == getColor())
			++s.attack_score;
		else if ((*m_map)[y][x] != Color::Null)
			++s.defend_score;
		else break;

	}
	ans = s > ans ? s : ans;
	s = Score(0, 0);

	//查反斜线
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x - i;
		int y = cur_y + i;
		if (x < 0 || y >= m_y) break;
		if ((*m_map)[y][x] == getColor())
			++s.attack_score;
		else if ((*m_map)[y][x] != Color::Null)
			++s.defend_score;
		else break;

	}
	for (int i = 1; i < 5; ++i)
	{
		int x = cur_x + i;
		int y = cur_y - i;
		if (x >= m_x || y < 0) break;
		if ((*m_map)[y][x] == getColor())
			++s.attack_score;
		else if ((*m_map)[y][x] != Color::Null)
			++s.defend_score;
		else break;

	}
	ans = s > ans ? s : ans;

	return ans;
}


