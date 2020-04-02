#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>

/*  functions  */

//stdin内のキャッシュをすべて削除します。これによって連打による誤爆を最低限に抑えることができます。
void clear_buff(void);

//commsに存在する文字が入力された場合に、その文字を返却します。これはキーの入力判定として用いられます。これはプログラムの流れを一時的に停止させます。
//comm_numは必ずcommsのサイズ以内にしてください。
char command_set(const char *comms, int comm_num);

//画面中央（多分）にタイピングを行う様なアニメーションと共にmain_stringを表示します。改行にも対応しています。
void print_center(std::string main_string, char * window_mode, int print_sleep_time = 2000, int char_sleep_time = 60);

//ウィンドウのサイズを2パターンに分けます。
char window_size(char *window);


/* templates */

//vectorによる配列の中身をシャッフルします
template <typename T>
void shuffle(std::vector<T>& list)
{
	std::random_device rnd;			// 非決定的な乱数生成器
	std::mt19937 mt(rnd());			// メルセンヌ・ツイスタの32ビット版、引数は初期シード
	std::uniform_int_distribution<> rand_make(0, list.size() - 1);

	for (size_t i = 0; i < list.size(); ++i) {
		unsigned int j = rand_make(mt);
		std::swap(list[i], list[j]);
	}
};

//配列の中身を良い感じに標準出力します
template <typename T>
void show(std::vector<T> list, std::string name)
{
	std::cout << name << ":";
	for (auto n : list)
	{
		std::cout << "[" << n << "]";
	}
	std::cout << std::endl;
};