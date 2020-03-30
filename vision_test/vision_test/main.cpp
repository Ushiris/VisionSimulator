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

void makeDeckList(vector<int> &list)
{
	for (int i = 0;i < 3;++i)
	{
		list.push_back(720);
		list.push_back(12030);
	}
}

bool TestPlay(Board &player)
{
	return false;
}

int main(void)
{
	Init();
	Board player;
	vector<vector<int>> targets(4, vector<int>(3,999));
	targets[0][0] = 0;
	targets[0][1] = 1;
	targets[0][2] = 2;
	targets[1][0] = 3;
	targets[2][0] = 4;
	targets[3][0] = 5;

	vector<int> deckList;
	makeDeckList(deckList);
	player.setDeckList(deckList);

	unsigned int test_time = 0;
	unsigned int success = 0;
	long double result_end = 0;

	clear_buff();

	while (test_time <= MAXUINT - 1001)
	{
		for (int i = 0;i < 1000;++i)
		{
			player.draw(7);
			if (player.inHand(targets[0]))
			{
				success++;
			}

			player.resetDeck();
			test_time++;
		}

		long double result = (long double)success / test_time * 100;
		system("cls");
		cout << setprecision(5) << result << '%' << "\ntime:" << test_time << endl;

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