#include "Card.h"
#include "Board.h"
#include "UshirisUtl.h"

using namespace std;

#define EFFECT(x) effects[ID2INDEX(x)] = [](void* board)
#define MAKE_BOARD Board *you = ((Board*)board)
#define CARD_SELF you->getCast(), you->getCast().size() - 1
#define DISCARD_SELF you->discard(CARD_SELF)
#define SHUFFLE shuffle(you->getDeck())
#define MANA_CHARGE(x) for(int i=0;i<(x);i++)you->sendNode(you->getDeck(), 0)

//�����ŃJ�[�h�̃f�[�^��S�ď��������܂�
void Card::InitDataBase()
{
	//�Ƃ肠�����S���󌂂��ł���悤�ɂ��܂��B
	for (int i = 0; i < NORMAL_NUMBER_CARD + PR_NUMBER_CARD; ++i)
	{
		effects[i] = [](void* board) {
			MAKE_BOARD;
			DISCARD_SELF;
			return true;
		};
	}

	//�����Ɍ��ʏ����������܂��B�n�����H
#pragma region CARD_EFFECT_DEFINE_AREA

	//�e���v���[�g�B����͉��������ʂ��������A������Ƀv���C�G���A����j������܂��B�����͐��������Ƃ݂Ȃ���܂��B
	EFFECT(0) {
		MAKE_BOARD;
		DISCARD_SELF;
		return true;
	};

	EFFECT(720) {
		MAKE_BOARD;
		you->sendNode(CARD_SELF);

		return true;
	};

	EFFECT(12030) {
		MAKE_BOARD;
		you->sarch(12030);
		SHUFFLE;
		MANA_CHARGE(1);

		DISCARD_SELF;
		return true;
	};

#pragma endregion
}