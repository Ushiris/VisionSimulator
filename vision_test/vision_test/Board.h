#pragma once

#include <vector>

using std::vector;

class Board
{
private:
	static const int DECK_LIMIT = 50;
	static const int SIDE_LIMIT = 10;

	Board *enemy;

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
	vector<int> getDeck();
	vector<int> getDeckList();
	vector<int> getSide();
	vector<int> getHands();
	vector<int> getNode();
	vector<int> getNether();
	vector<int> getCast();
	vector<int> getField();

	/* setter */
	void setDeckList(vector<int> list);

	/* other */
	void draw(int amount = 1);							//�J�[�h���h���[����
	void addDeck(vector<int> &add);						//add���̃J�[�h�S�Ă��f�b�L�ɑ���
	void resetDeck();									//�S�ẴJ�[�h���f�b�L�ɖ߂��ăV���b�t������
	void playCard(vector<int> &cards, int idx);			//�v���C�����𖳎����ăJ�[�h�̃v���C���s��
	void playReqest(vector<int> &cards, int idx);		//�����ɃJ�[�h�̃v���C��錾����
	void addEnemy(Board *newEnemy);						//�ΐ푊��̔Ֆʂ��K�肷��
	void sendNode(vector<int> &cards, int idx = 0);		//�m�[�h�ɃJ�[�h���ړ�������
	void discard(vector<int> &cards, int idx);
	
	
	bool inHand(vector<int> targets);					//��D��target���̃J�[�h�����݂��邩���ׂ�
	bool inDeck(vector<int> targets);					//�f�b�L��target���̃J�[�h�����݂��邩���ׂ�
	bool isHell();
};