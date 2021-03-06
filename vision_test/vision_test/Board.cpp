#include "Board.h"
#include "UshirisUtl.h"
#include "Card.h"

using namespace std;

Board::Board()
{
	deck=vector<int>();
	deckList=vector<int>();
	_cardData = vector<void*>(DECK_LIMIT + SIDE_LIMIT);
	side=vector<int>();
	hands=vector<int>();
	node=vector<int>();
	nether=vector<int>();
	cast=vector<int>();
	field=vector<int>();

	deck = vector<int>(DECK_LIMIT);
	for (int i = 0;i < DECK_LIMIT;++i) {
		deck[i] = i;
	}
	deckList = vector<int>(DECK_LIMIT+SIDE_LIMIT, 0);

	shuffle(deck);
}

Board::Board(vector<int> &newDeckList)
{

	deck = vector<int>();
	deckList = newDeckList;
	_cardData = vector<void*>(DECK_LIMIT + SIDE_LIMIT);
	for (int i=0;i<newDeckList.size();i++)
	{
		_cardData[i] = new Card(deckList[i]);
	}
	
	side = vector<int>();
	hands = vector<int>();
	node = vector<int>();
	nether = vector<int>();
	cast = vector<int>();
	field = vector<int>();

	deck = vector<int>(DECK_LIMIT);
	for (int i = 0; i < DECK_LIMIT; ++i) {
		deck[i] = i;
	}
	deckList = vector<int>(DECK_LIMIT + SIDE_LIMIT, 0);

	shuffle(deck);
}

Board::~Board()
{
}

Board * Board::getEnemy()
{
	return enemy;
}

vector<int>& Board::getDeck()
{
	return deck;
}

vector<int>& Board::getDeckList()
{
	return deckList;
}

vector<int>& Board::getSide()
{
	return side;
}

vector<int>& Board::getHands()
{
	return hands;
}

vector<int>& Board::getNode()
{
	return node;
}

vector<int>& Board::getNether()
{
	if (isHell()) return dummy;
	return nether;
}

vector<int>& Board::getCast()
{
	return cast;
}

vector<int>& Board::getField()
{
	return field;
}

vector<int>& Board::getPlayLimitCard()
{
	return playLimitCard;
}

void * Board::getCardData(int deck_list_id)
{
	return _cardData[deck_list_id];
}

bool Board::checkPlayable(void *playCard)
{
	Card *card = (Card*)playCard;

	if (node.size() < card->getNode())return false;

	return true;
}

bool Board::checkPlayable(int hand_idx)
{
	Card* card = (Card*)(_cardData[hands[hand_idx]]);

	return card->getNode() > node.size();
}

void Board::setDeckList(vector<int> list)
{
	for (size_t i = 0;i < list.size();++i)
	{
		deckList[i] = list[i];
	}
}

void Board::draw(int amount)
{
	for (int i = 0;i < amount;++i)
	{
		//if(deck.size==0)

		hands.push_back(deck[0]);
		deck.erase(deck.begin());
	}
}

bool Board::inHand(vector<int> deck_idx)
{
	for (auto &card : hands)
	{
		for (auto &target : deck_idx)
		{
			if (card == target)return true;
		}
	}

	return false;
}

bool Board::inHand(int id)
{
	for (size_t i = 0; i < hands.size(); i++)
	{
		Card* card = (Card*)getCardData(deckList[hands[i]]);
		if (card->getId() == id)return true;
	}
	return false;
}

bool Board::inOnePairOver(int id)
{
	if (hands.size() < 2)return false;
	bool isFind = false;
	for (size_t i = 0; i < hands.size(); i++)
	{
		if (deckList[hands[i]] == id)
		{
			if (!isFind)
			{
				isFind = true;
			}
			else
			{
				return true;
			}
		}
	}

	return false;
}

bool Board::inDeck(vector<int> deck_idx)
{
	for (auto &card : deck)
	{
		for (auto &idx : deck_idx)
		{
			if (card == idx)return true;
		}
	}

	return false;
}

bool Board::inDeck(int id)
{
	for (size_t i = 0; i < deck.size(); i++)
	{
		Card* card = (Card*)getCardData(deckList[deck[i]]);
		if (card->getId() == id)return true;
	}
	return false;
}

bool Board::isHell()
{
	return _isHell;
}

void Board::addDeck(vector<int> & add_list_idx)
{
	for (auto card : add_list_idx)
	{
		deck.push_back(card);
	}
	add_list_idx.clear();
}

void Board::resetDeck()
{
	addDeck(node);
	addDeck(hands);
	addDeck(node);
	addDeck(nether);
	addDeck(cast);
	addDeck(field);

	shuffle(deck);
}

void Board::sendNode(vector<int> &cards, int idx)
{
	node.push_back(cards[idx]);
	cards.erase(cards.begin() + idx);
}

void Board::discard(vector<int>& cards, int idx)
{
	nether.push_back(cards[idx]);
	cards.erase(cards.begin() + idx);
}

bool Board::sarch(int id)
{
	vector<int> target;
	for (size_t i = 0; i < deckList.size(); i++)
	{
		if (deckList[i] == id)
		{
			target.push_back(i);
		}
	}

	for (size_t i=0;i<deck.size();i++)
	{
		for (auto& target_x : target)
		{
			if (deck[i] == target_x)
			{
				hands.push_back(deck[i]);
				deck.erase(deck.begin() + i);

				return true;
			}
		}
	}
	return false;
}

void Board::nodeSet(int hand_idx)
{
	if (hand_idx >= hands.size())return;
	sendNode(hands, hand_idx);
	_isSetNode = true;
}

void Board::nodeSet(vector<int> ignore_id)
{
	for (size_t i = 0; i < hands.size(); i++)
	{
		bool isIgnore = false;
		for (auto id : ignore_id)
		{
			isIgnore = (id == deckList[hands[i]]);
		}
		if (isIgnore)continue;

		nodeSet(i);
		return;
	}
}

void Board::addLimit(int id)
{
	playLimitCard.push_back(id);
}

bool Board::playCard(vector<int> &cards, int idx)
{
	//move to cast area.
	cast.push_back(cards[idx]);
	cards.erase(cards.begin() + idx);

	Card* card = (Card*)getCardData(cards[idx]);

	card->play(this);
}

bool Board::playRequest(vector<int> &cards, int idx)
{
	if (!checkPlayable(getCardData(cards[idx])))return false;
	return playCard(cards, idx);
}

bool Board::playRequest(int id)
{
	int hand_idx = -1;
	for (size_t i=0;i<hands.size();i++)
	{
		if (deckList[hands[i]] == id)
		{
			hand_idx = i;
			break;
		}
	}
	if (hand_idx == -1)return false;

	if (!checkPlayable(getCardData(hands[hand_idx])))return false;

	return playCard(hands, hand_idx);
}

void Board::addEnemy(Board * newEnemy)
{
	enemy = newEnemy;
}

