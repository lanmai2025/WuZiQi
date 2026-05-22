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
	game.gameLoopAI();

	_getch();
}

//≥¢ ‘