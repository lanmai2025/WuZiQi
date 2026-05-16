#include <iostream>
#include "Rely.h"
#include "Player.h"
#include "GameCtr.h"
#include <easyx.h>
#include <graphics.h>
#include <conio.h>


int main()
{
	GameCtr game(20, 20, 5);
	game.solve();

	_getch();
}



//vector<vector<vector<int>>> k;
//
//vector< vector <int > >& getK()
//{
//	return k[1];
//}


//int add()
//{
//	int size = 1;
//	int d = 4;
//	std::vector<int> a(size, d);
//
//	a.resize(10);
//	a.size();
//	
//	vector<vector<int>> a(10, vector<int>(1, 2));
//}
