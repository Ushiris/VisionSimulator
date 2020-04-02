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
	vector<vector<int>> targets(4, vector<int>(3, 999));
	targets[0][0] = 0;
	targets[0][1] = 1;
	targets[0][2] = 2;
	targets[1][0] = 3;
	targets[2][0] = 4;
	targets[3][0] = 5;

	player.draw(7);

	bool result = false;

	result = player.inHand(targets[0]);


	return result;
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