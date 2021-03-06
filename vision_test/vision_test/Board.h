#pragma once

#include <vector>

using std::vector;

class Board
{
private:
	static const int DECK_LIMIT = 50;
	static const int SIDE_LIMIT = 10;

	Board *enemy;
	vector<void*> _cardData;			//collection 

	vector<int> deck;					//collection index. 0 is top of deck
	vector<int> deckList;				//collection ID.
	vector<int> side;
	vector<int> hands;
	vector<int> node;
	vector<int> nether;
	vector<int> field;
	vector<int> dummy = vector<int>();
	vector<int> playLimitCard = vector<int>();

	bool _isHell = false;
	bool _isSetNode = false;
	bool _isPlayChara = false;

public:
	Board();
	Board(vector<int> &newDeckList);
	~Board();

	/* share */
	static vector<int> cast;

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
	vector<int>& getPlayLimitCard();
	bool isHell();

	void* getCardData(int deck_list_id);

	/* setter */
	void setDeckList(vector<int> list);

	/* other */
	void draw(int amount = 1);							//カードをドローする
	void addDeck(vector<int> &add_list_idx);						//add内のカード全てをデッキに送る
	void resetDeck();									//全てのカードをデッキに戻してシャッフルする
	bool playCard(vector<int> &cards, int idx);			//プレイ条件を無視してカードのプレイを行う
	bool playRequest(vector<int> &cards, int idx);		//正式にカードのプレイをしようとします
	bool playRequest(int id);								//手札の[ID]を選びます
	void addEnemy(Board *newEnemy);						//対戦相手の盤面を規定する
	void sendNode(vector<int> &cards, int idx = 0);		//ノードにカードを移動させる
	void discard(vector<int> &cards, int idx);			//カードを破棄する
	bool sarch(int id);									//デッキからカードを手札に加える
	void nodeSet(int hand_idx);							//メインフェイズ既定のノードセットを行う
	void nodeSet(vector<int> ignore_id);					//ignore_id以外のカードをセットします。ない場合はセットしません。
	void addLimit(int id);								//プレイされたターン一回制限のカードのIDを記録します
	
	
	bool inHand(vector<int> deck_idx);					//手札にデッキリストのN番目のカードが存在するか調べる
	bool inHand(int id);									//手札に[ID]があるかどうか調べます
	bool inOnePairOver(int id);							//手札に[ID]が二枚以上あるかどうか調べる
	bool inDeck(vector<int> deck_idx);					//デッキにデッキリストのN番目のカードが存在するか調べる
	bool inDeck(int id);									//デッキに[ID]があるかどうか調べます

	bool checkPlayable(void* playCard);
	bool checkPlayable(int hand_idx);
};
