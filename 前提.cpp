//// （1） 常量：大写+下划线分隔 
//const int MAP_HIGHT = 10;
//#define MAP_WIDTH 10
//
////（2） 普通变量：小写+下划线分隔
//int cur_map_hight = 1;
//
////（3） 成员变量：public:m_名称，private:直接名称
//class Block
//{
//private:
//	int x;
//	int y;
//
//public:
//	int m_cur_x;
//	int m_cur_y;
//};
//
////（4） 函数：开头小写，后面大写，半驼峰命名
//class Block2
//{
//public:
//	void move(int op);
//	void drawCurOption();
//	int getX();
//	
//private:
//	int x;
//};
//
////（5） 类名 / 名称空间 / 结构体 / enum枚举类：首字母大写
//struct Point {};
//enum class Dir
//{
//	DOWN, UP, LEFT, RIGHT
//};
//namespace MyName {}


//（1） 文档前： /* 介绍 */

/********************************************
*	
*	例子：这是一个规范格式
* 
*********************************************/

//（2） 类中：函数前加注释（简单函数不用加说明）
class Block2
{
public:
	//0下，1上，2左，3右
	void move(int op);
	//绘制当前位置
	void drawCurOption();
	int getX();
	
private:
	int x;
	int y;
};

//（3） 函数内：每部分后跟注释（简洁）

void Block2::move(int op)
{
	if (op > 3 || op < 0) return; //越界直接返回
	switch (op)  //改变坐标
	{
	case 0:
		y += 1;  //这里不规范哈，应该写专门的更新函数
		break;
	case 1:
		y -= 1;
		break;
	case 2:
		x -= 1;
		break;
	case 3:
		x += 1;
		break;
	}
}

//（4）其余注释参考以上规范