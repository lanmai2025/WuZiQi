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