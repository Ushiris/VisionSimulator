#include "Card.h"
#include "Board.h"
#include "UshirisUtl.h"

using namespace std;

#define EFFECT(x) effects[ID2INDEX(x)] = [](void* board)
#define MAKE_BOARD Board *you = ((Board*)board)
#define CARD_SELF you->getCast(), you->getCast().size() - 1
#define DISCARD_SELF you->discard(CARD_SELF)

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



int Card::getId()
{
	return id;
}

CardType Card::getType()
{
	return type;
}

std::vector<std::string> Card::getName()
{
	return name;
}

std::string Card::getTrueName()
{
	return name[0];
}

int Card::getNode()
{
	return node + node_buff;
}

int Card::getCost()
{
	return cost;
}

std::string Card::getUser()
{
	return user;
}

std::vector<Race> Card::getRace()
{
	return race;
}

std::vector<Race> Card::getSolidarity()
{
	return solidarity;
}

int Card::getGraze()
{
	return graze;
}

Range Card::getRenge()
{
	return range;
}

Period Card::getPeriod()
{
	return period;
}

int Card::getAttack()
{
	return attack+attack_enchant;
}

int Card::getTrueAttack()
{
	return attack;
}

int Card::getLife()
{
	return life + life_enchant;
}

int Card::getTrueLife()
{
	return life;
}

int Card::getAttackEnchant()
{
	return attack_enchant;
}

int Card::getLifeEnchant()
{
	return life_enchant;
}

std::string Card::getText()
{
	return text;
}

std::function<bool(void*)>& Card::getEffect()
{
	return effect;
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
