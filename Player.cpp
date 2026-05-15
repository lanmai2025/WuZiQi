#include "Player.h"

Player::Player(int x, int y)
	:m_cur_x(x),m_cur_y(y)
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
