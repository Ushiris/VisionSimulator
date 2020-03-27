#pragma once
#include <string>
#include <vector>
#include <functional>


/* ID規則：カードIDは（int [ナンバー][0(No,)/1(PR)]）というフォーマットにする。 */

enum class CardType
{
	charactor,
	spell,
	command
};

enum class Race
{
	human,
	monster,
	faily,
	withch,
	cappa,
	vanpire,
	makaijin,
	ghost,
	tengu,
	reaper,
	enma,
	god,
	beast,
	demon,
	tennin,
	dragon,
	hermit,
	dwarf
};

enum class Range
{
	terget,
	all,
	player,
	malti,
	other
};

enum class Period
{
	instant,
	continuation,
	equipment,
	enchant,
	environment
};

class Card
{
private:
	int id;
	CardType type;
	std::string name;
	int node;
	int cost;
	std::string user;
	Race race;
	std::vector<Race> solidarity;
	int graze;
	Range renge;
	Period period;
	int atack;
	int life;
	int atack_enchant;
	int life_enchant;
	std::string text;
	std::function<bool(void*)> effect;

	std::vector<Card> setCards;

public:
	Card();
	Card(int newId);
	~Card();

	static const int NORMAL_NUMBER_CARD = 2000;
	static const int PR_NUMBER_CARD = 300;
	static std::function<bool(void*)> effects[NORMAL_NUMBER_CARD + PR_NUMBER_CARD];

	static void InitDataBase();

	int getId();
	bool isPlayable();
	bool (*play)(void*);
};

std::function<bool(void*)> getPlayEffect(int id);