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
	void draw(int amount = 1);							//�J�[�h���h���[����
	void addDeck(vector<int> &add_list_idx);						//add���̃J�[�h�S�Ă��f�b�L�ɑ���
	void resetDeck();									//�S�ẴJ�[�h���f�b�L�ɖ߂��ăV���b�t������
	bool playCard(vector<int> &cards, int idx);			//�v���C�����𖳎����ăJ�[�h�̃v���C���s��
	bool playRequest(vector<int> &cards, int idx);		//�����ɃJ�[�h�̃v���C�����悤�Ƃ��܂�
	bool playRequest(int id);								//��D��[ID]��I�т܂�
	void addEnemy(Board *newEnemy);						//�ΐ푊��̔Ֆʂ��K�肷��
	void sendNode(vector<int> &cards, int idx = 0);		//�m�[�h�ɃJ�[�h���ړ�������
	void discard(vector<int> &cards, int idx);			//�J�[�h��j������
	bool sarch(int id);									//�f�b�L����J�[�h����D�ɉ�����
	void nodeSet(int hand_idx);							//���C���t�F�C�Y����̃m�[�h�Z�b�g���s��
	void nodeSet(vector<int> ignore_id);					//ignore_id�ȊO�̃J�[�h���Z�b�g���܂��B�Ȃ��ꍇ�̓Z�b�g���܂���B
	void addLimit(int id);								//�v���C���ꂽ�^�[����񐧌��̃J�[�h��ID���L�^���܂�
	
	
	bool inHand(vector<int> deck_idx);					//��D�Ƀf�b�L���X�g��N�Ԗڂ̃J�[�h�����݂��邩���ׂ�
	bool inHand(int id);									//��D��[ID]�����邩�ǂ������ׂ܂�
	bool inOnePairOver(int id);							//��D��[ID]���񖇈ȏ゠�邩�ǂ������ׂ�
	bool inDeck(vector<int> deck_idx);					//�f�b�L�Ƀf�b�L���X�g��N�Ԗڂ̃J�[�h�����݂��邩���ׂ�
	bool inDeck(int id);									//�f�b�L��[ID]�����邩�ǂ������ׂ܂�

	bool checkPlayable(void* playCard);
	bool checkPlayable(int hand_idx);
};
