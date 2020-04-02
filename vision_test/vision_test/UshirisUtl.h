#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>

/*  functions  */

//stdin���̃L���b�V�������ׂč폜���܂��B����ɂ���ĘA�łɂ��딚���Œ���ɗ}���邱�Ƃ��ł��܂��B
void clear_buff(void);

//comms�ɑ��݂��镶�������͂��ꂽ�ꍇ�ɁA���̕�����ԋp���܂��B����̓L�[�̓��͔���Ƃ��ėp�����܂��B����̓v���O�����̗�����ꎞ�I�ɒ�~�����܂��B
//comm_num�͕K��comms�̃T�C�Y�ȓ��ɂ��Ă��������B
char command_set(const char *comms, int comm_num);

//��ʒ����i�����j�Ƀ^�C�s���O���s���l�ȃA�j���[�V�����Ƌ���main_string��\�����܂��B���s�ɂ��Ή����Ă��܂��B
void print_center(std::string main_string, char * window_mode, int print_sleep_time = 2000, int char_sleep_time = 60);

//�E�B���h�E�̃T�C�Y��2�p�^�[���ɕ����܂��B
char window_size(char *window);


/* templates */

//vector�ɂ��z��̒��g���V���b�t�����܂�
template <typename T>
void shuffle(std::vector<T>& list)
{
	std::random_device rnd;			// �񌈒�I�ȗ���������
	std::mt19937 mt(rnd());			// �����Z���k�E�c�C�X�^��32�r�b�g�ŁA�����͏����V�[�h
	std::uniform_int_distribution<> rand_make(0, list.size() - 1);

	for (size_t i = 0; i < list.size(); ++i) {
		unsigned int j = rand_make(mt);
		std::swap(list[i], list[j]);
	}
};

//�z��̒��g��ǂ������ɕW���o�͂��܂�
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