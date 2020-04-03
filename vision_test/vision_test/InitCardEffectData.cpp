#include "Card.h"
#include "Board.h"
#include "UshirisUtl.h"

using namespace std;

#define EFFECT(x) effects[ID2INDEX(x)] = [](void* board)
#define MAKE_BOARD Board *you = ((Board*)board)
#define CARD_SELF you->getCast(), you->getCast().size() - 1
#define DISCARD_SELF you->discard(CARD_SELF)

//ここでカードのデータを全て初期化します
void Card::InitDataBase()
{
	//とりあえず全部空撃ちできるようにします。
	for (int i = 0; i < NORMAL_NUMBER_CARD + PR_NUMBER_CARD; ++i)
	{
		effects[i] = [](void* board) {
			MAKE_BOARD;
			DISCARD_SELF;
			return true;
		};
	}

	//ここに効果処理を書きます。地獄か？
#pragma region CARD_EFFECT_DEFINE_AREA

	//テンプレート。これは何も実効果を持たず、解決後にプレイエリアから破棄されます。解決は成功したとみなされます。
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
		if (you->sarch(12030) == false) return false;
		shuffle(you->getDeck());
		you->sendNode(you->getDeck(), 0);
		DISCARD_SELF;

		return true;
	};

#pragma endregion
}