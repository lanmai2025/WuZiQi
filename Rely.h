#pragma once
/*
*	本文件包含部分依赖，包括简单的类、结构体等
*	保证这些依赖不变
*/

//颜色
#include <easyx.h>

enum class Color
{
	Null = -1,
	White = WHITE,
	Black = BLACK,
	Red = RED,
	Yellow = YELLOW
	
};

//坐标
struct Point
{
	int x;
	int y;

};


//分数
struct Score
{
	int x;				//坐标x
	int y;				//坐标y
	int	attack_score;	//攻击分数
	int defend_score;	//防守分数
	//int total_score;	//总分数

	bool operator < (const Score& s) const
	{
		if (defend_score != s.defend_score) return defend_score <= s.defend_score;
		return attack_score <= s.attack_score;
		//return total_score < s.total_score;
	}

	bool operator > (const Score& s) const
	{
		if (defend_score != s.defend_score) return defend_score >= s.defend_score;
		return attack_score >= s.attack_score;
		//return total_score > s.total_score;
	}
};