#include "Card.h"
#include "Board.h"

#define ID2INDEX(id) (((id)%10==0)?(id/10):(id/10+Card::NORMAL_NUMBER_CARD))
#define INDEX2ID(idx) (((idx)<=Card::NORMAL_NUMBER_CARD)?(idx0):(idx1))

using namespace std;

Card::Card()
{
}

Card::Card(int newId)
{
	id = newId;
	effect = getPlayEffect(id);
}


Card::~Card()
{
}

//�����ŃJ�[�h�̃f�[�^��S�ď��������܂�
void Card::InitDataBase()
{
	//�Ƃ肠�����S���󌂂��ł���悤�ɂ��܂��B
	for (int i = 0;i < NORMAL_NUMBER_CARD + PR_NUMBER_CARD;++i)
	{
		effects[i] = [](void* board) {board-> return true;};
	}

	//�����Ɍ��ʏ����������܂��B�n�����H
	effects[ID2INDEX(720)] = [](void* board) {
		Board *you = (Board*)board;
		you->sendNode(you->getCast(), you->getCast().size()-1);
		return true;
	};
}

int Card::getId()
{
	return id;
}

bool Card::isPlayable()
{
	if (node < -10000)
	{
		return false;
	}
	return true;
}

std::function<bool(void*)> Card::effects[NORMAL_NUMBER_CARD + PR_NUMBER_CARD]
{

};

std::function<bool(void)> effect
{

};


function<bool(void*)> getPlayEffect(int id)
{
	return Card::effects[ID2INDEX(id)];
}
