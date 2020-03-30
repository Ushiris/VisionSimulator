#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <iostream>
#include <string>
#include <random>

#include "UshirisUtl.h"

using namespace std;

vector<string> split(const string &s, char delim) {
	vector<string> elems;
	string item;
	for (char ch : s) {
		if (ch == delim) {
			if (!item.empty())
				elems.push_back(item);
			item.clear();
		}
		else {
			item += ch;
		}
	}
	if (!item.empty())
		elems.push_back(item);
	return elems;
}

void clear_buff(void)
{
	while (_kbhit())
	{
		_getch();
	}
}

char command_set(const char *comms, int comm_num)
{
	int i;
	char comm;
	bool check = false;

	while (1)
	{
		clear_buff();
		comm = _getch();
		for (i = 0; i < comm_num + 1; i++)
		{
			if (comms[i] == comm)
			{
				check = true;
				break;
			}
		}
		if (check)
		{
			break;
		}
		else {
			printf("\aERROR:It isn't command.\n");
		}
	}

	return comm;
}

void print_center(string main_string, char * window_mode, int print_sleep_time, int char_sleep_time)
{
	char window = window_size(&*window_mode);

	vector<string> strings = split(main_string, '\n');

	system("cls");

	//goto start line
	for (unsigned int i = 0; i < 12 - strings.size() / 2; i++)
	{
		_putch('\n');
	}

	clear_buff();

	//main logic
	for (size_t j = 0; j <= strings.size(); j++)
	{
		//goto start position
		for (unsigned int i = 0; i < window - strings[j].size() / 2; i++)
		{
			_putch(' ');
		}

		//print string
		for (size_t i = 0; i < strings[j].size(); i++)
		{
			//skip animation
			if (_kbhit()){
				clear_buff();
				char_sleep_time = 0;
			}

			Sleep(char_sleep_time);				//typing delay animation
			_putch(strings[j][i]);
		}
	}

	clear_buff();
	for (int x = 0; x < print_sleep_time; ++x)
	{
		if (_kbhit())
		{
			clear_buff();
			print_sleep_time = 0;
		}
		Sleep(1);
	}

	system("cls");
}

char window_size(char *window)
{
	if (*window == 'n')
	{
		return 39;
	}
	else if (*window == 'w')
	{
		return 55;
	}
	printf("Window size...\n[N]...Nomal  [W]...Wide\n");
	printf("もし、この文章がウィンドウの右端で折り返されているなら、Nを選択することをおすすめします。");
	*window = command_set("nw", 2);
	if (*window == 'n')
	{
		return 39;
	}
	else
	{
		return 55;
	}

	return 1;
};