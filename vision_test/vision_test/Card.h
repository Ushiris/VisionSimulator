#pragma once
#include <string>
#include <vector>
#include <functional>

/* ID規則：カードIDは（int [ナンバー][0(No,)/1(PR)]）というフォーマットにする。 */
#define ID2INDEX(id) (((id)%10==0)?(id/10):(id/10+Card::NORMAL_NUMBER_CARD))
#define INDEX2ID(idx) (((idx)<=Card::NORMAL_NUMBER_CARD)?(idx0):(idx1))


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
	dwarf,
	none,
	solidarity_void
};

enum class Range
{
	terget,
	all,
	player,
	malti,
	other,
	none
};

enum class Period
{
	instant,
	continuation,
	equipment,
	enchant,
	environment,
	none
};

class Card
{
private:
	//card text
	int id = 0;
	CardType type = CardType::command;
	std::vector<std::string> name = { "void" };
	int node = 0;
	int cost = 0;
	std::string user = "none";
	std::vector<Race> race = { Race::none };
	std::vector<Race> solidarity = { Race::solidarity_void };
	int graze = 0;
	Range range = Range::none;
	Period period = Period::none;
	int attack = 0;
	int life = 0;
	std::string text = "";

	//in game effects
	int attack_enchant = 0;
	int life_enchant = 0;
	int node_buff = 0;
	int cost_buff = 0;
	std::function<bool(void*)> effect = std::function<bool(void*)>([](void*) { return false; });
	std::vector<std::function<bool(void*)>> actions = std::vector<std::function<bool(void*)>>();
	bool isCharactor = false;
	bool isEquipment = false;
	bool isReverse = false;

	std::vector<Card> setCards;

public:
	Card();
	Card(int newId);
	~Card();

	int getId();
	CardType getType();
	std::vector<std::string> getName();
	std::string getTrueName();
	int getNode();
	int getCost();
	std::string getUser();
	std::vector<Race> getRace();
	std::vector<Race> getSolidarity();
	int getGraze();
	Range getRenge();
	Period getPeriod();
	int getAttack();
	int getTrueAttack();
	int getLife();
	int getTrueLife();
	int getAttackEnchant();
	int getLifeEnchant();
	std::string getText();
	std::function<bool(void*)>& getEffect();

	static const int NORMAL_NUMBER_CARD = 2000;
	static const int PR_NUMBER_CARD = 300;
	static std::function<bool(void*)> effects[NORMAL_NUMBER_CARD + PR_NUMBER_CARD];

	static void InitDataBase();

	bool isPlayable();
	std::function<bool(void*)> play = std::function<bool(void*)>([](void*) {return true; });
};

std::function<bool(void*)> getPlayEffect(int id);