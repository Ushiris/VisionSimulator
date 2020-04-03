#include <iostream>
#include <vector>
#include <random>
#include <iomanip>
#include <conio.h>
#include <windows.h>
#include <algorithm>

#include "UshirisUtl.h"
#include "Board.h"
#include "Card.h"

using namespace std;

void Init()
{
	cout << fixed;
	Card::InitDataBase();
}

vector<int> makeDeckList()
{
	vector<int> deckList;
	for (int i = 0;i < 3;++i)
	{
		deckList.push_back(720);
		deckList.push_back(12030);
	}
	return deckList;
}

bool TestPlay(Board &player)
{
	//最初のドロー
	player.draw(7);

	//霞網2枚パターン
	if (player.inOnePairOver(12030))return true;

	//turn 1
	player.playRequest(720);
	player.nodeSet({ 720,12030 });

	//turn 2
	player.playRequest(720);
	player.playRequest(12030);
	player.draw(1);

	return false;
}

int main(void)
{
	Init();

	vector<int> deckList = makeDeckList();
	Board player(deckList);

	unsigned int test_time = 0;
	unsigned int success = 0;
	long double result_end = 0;

	clear_buff();

	while (test_time <= MAXUINT - 1001)
	{
		for (int i = 0;i < 1000;++i)
		{
			if (TestPlay(player)) success++;

			player.resetDeck();
			test_time++;
		}

		long double result = (long double)success / test_time * 100;
		system("cls");
		cout << setprecision(5) << result <<"%\ntime:" << test_time << endl;

		if (_kbhit())
		{
			result_end = result;
			break;
		}
	}

	clear_buff();
	cout << "[E]:exit" << endl;
	command_set("e", 1);

	return 0;
}