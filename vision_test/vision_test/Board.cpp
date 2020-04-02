#include "Board.h"
#include "UshirisUtl.h"
#include "Card.h"

using namespace std;

Board::Board()
{
	deck=vector<int>();
	deckList=vector<int>();
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

void * Board::getCardData(int idx)
{
	return _cardData[idx];
}

bool Board::checkPlayable(void *playCard)
{
	Card *card = (Card*)playCard;

	if (node.size() < card->getNode())
	{
		return false;
	}

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

bool Board::inHand(vector<int> targets)
{
	for (auto &card : hands)
	{
		for (auto &target : targets)
		{
			if (card == target)return true;
		}
	}

	return false;
}

bool Board::inDeck(vector<int> targets)
{
	for (auto &card : deck)
	{
		for (auto &target : targets)
		{
			if (card == target)return true;
		}
	}

	return false;
}

bool Board::isHell()
{
	return _isHell;
}

void Board::addDeck(vector<int> &add)
{
	for (auto card : add)
	{
		deck.push_back(card);
	}
	add.clear();
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

void Board::playCard(vector<int> &cards, int idx)
{
	//move to cast area.
	cast.push_back(cards[idx]);
	cards.erase(cards.begin() + idx);

	Card* card = (Card*)getCardData(cards[idx]);

	card->play(this);
}

void Board::playReqest(vector<int> &cards, int idx)
{
	if (checkPlayable(getCardData(cards[idx])))
	{
		playCard(cards, idx);
	}
}

void Board::addEnemy(Board * newEnemy)
{
	enemy = newEnemy;
}

