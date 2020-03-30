#pragma once

#include <vector>

using std::vector;

class Board
{
private:
	static const int DECK_LIMIT = 50;
	static const int SIDE_LIMIT = 10;

	Board *enemy;
	vector<void*> _cardData;

	vector<int> deck;
	vector<int> deckList;
	vector<int> side;
	vector<int> hands;
	vector<int> node;
	vector<int> nether;
	vector<int> cast;
	vector<int> field;

	bool _isHell;

public:
	Board();
	~Board();

	/* getter */
	Board* getEnemy();
	vector<int>& getDeck();
	vector<int>& getDeckList();
	vector<int>& getSide();
	vector<int>& getHands();
	vector<int>& getNode();
	vector<int>& getNether();
	vector<int>& getCast();
	vector<int>& getField();

	void* getCardData(int idx);
	bool checkPlayable(void* playCard);
	bool checkPlayable(int hand_idx);

	/* setter */
	void setDeckList(vector<int> list);

	/* other */
	void draw(int amount = 1);							//カードをドローする
	void addDeck(vector<int> &add);						//add内のカード全てをデッキに送る
	void resetDeck();									//全てのカードをデッキに戻してシャッフルする
	void playCard(vector<int> &cards, int idx);			//プレイ条件を無視してカードのプレイを行う
	void playReqest(vector<int> &cards, int idx);		//正式にカードのプレイを宣言する
	void addEnemy(Board *newEnemy);						//対戦相手の盤面を規定する
	void sendNode(vector<int> &cards, int idx = 0);		//ノードにカードを移動させる
	void discard(vector<int> &cards, int idx);			//カードを破棄する
	
	
	bool inHand(vector<int> targets);					//手札にtarget内のカードが存在するか調べる
	bool inDeck(vector<int> targets);					//デッキにtarget内のカードが存在するか調べる
	bool isHell();
};
