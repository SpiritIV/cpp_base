#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <algorithm>
#include <iterator>

using namespace std;

# define bool uint16_t
# define true 1==1
# define false 1!=1

/*-------------Card-------------*/

class Card
{
public:
	//Emums of suits and types
	enum	suits
	{
		hearts,
		diamonds,
		spades,
		crosses
	};

	enum	types
	{
		ace = 1,
		two,
		three,
		four,
		five,
		six,
		seven,
		eight,
		nine,
		ten,
		jack,
		lady,
		king
	};
	
	//Basic contructors and destructor
	Card(suits s = diamonds, types t = ace, bool st = true) : suit(s), type(t), state(st) {};
	~Card() {};

	//Game methods
	void					Flip() { state == 0 ? state = 1 : state = 0; }; //Flip card
	uint16_t				GetValue(void);									//Card value
	friend std::ostream&	operator << (std::ostream &os, const Card &p);	//Override <<

protected:
	suits	suit;
	types	type;
	bool	state;
};

std::ostream&	operator<<(std::ostream &os, const Card &card)
{
    if (!card.state)
	{
		return (os << "XX\n");
	}
	else
	{
		return (os << "Rank of card is "/*"Suit and type of card are " << card.suit << " and "<<*/ << (uint32_t)(card.type) << std::endl);
	}
}

uint16_t		Card::GetValue(void)
{
	if (state)
		return (type > 10 ? 10 : type);
	return (0);
}

/*-------------Hand-------------*/

class Hand
{
protected:
	std::vector<Card *>	cards_in_hand;
public:
	Hand() { cards_in_hand.reserve(7); };
	virtual ~Hand() { cards_in_hand.clear(); };

	void		Add(Card *newCard);
	void		Clear(void);
	uint32_t	GetTotal(void) const;
};

void			Hand::Add(Card *newCard)
{
	cards_in_hand.push_back(newCard);
}

void			Hand::Clear(void)
{
	cards_in_hand.clear();
}

uint32_t		Hand::GetTotal(void) const
{
	uint32_t	result = 0;
	auto		it = cards_in_hand.begin();
	bool		flag_ace = false;

	while (it < cards_in_hand.end())
	{
		result += (*it)->GetValue();
		if ((*it)->GetValue() == Card::ace)
		{
			flag_ace = true;
		}
		++it;
	}

	if (flag_ace)
	{
		result += 10;
	}
	return (result);
}

/*---------GenericPlayer--------*/

class GenericPlayer : public Hand
{
protected:
	std::string				playerName;
public:
	GenericPlayer(const string name = "") : playerName(name) {};
	virtual uint16_t		IsHitting(void) = 0;
	bool					IsBoosted(void);
	void					Bust();
	friend std::ostream&	operator << (std::ostream &os, GenericPlayer &player);
	virtual	~GenericPlayer() {};
};

std::ostream&	operator << (std::ostream &os, GenericPlayer &player)
{
	os << player.playerName << " has: \n";

	auto it = player.cards_in_hand.begin();
	while (it != player.cards_in_hand.end())
	{
		os << (**it) << std::endl;
		++it;
	}
	return (os << "Sum of cards: " << player.GetTotal() << std::endl);
}

bool	GenericPlayer::IsBoosted()
{
	if (GetTotal() > 21)
	{
		return (true);
	}
	return (false);
}

void	GenericPlayer::Bust()
{
	std::cout << playerName << " has too much cards!\n";
}

/*-----------Player------------*/

class Player : public GenericPlayer
{
public:
	Player(const std::string& name = "") : GenericPlayer(name) {};
	~Player() {};

	virtual bool	IsHitting();
	void			Win(void) const;
	void			Lose(void) const;
	void			Push(void) const;
};

bool	Player::IsHitting(void)
{
	char	answer = '\0';

	std::cout << "One more card? Please, type Y or N - ";
	std::cin >> answer;

	return (answer == 'Y' ? true : false);
}

void	Player::Win(void) const
{
	std::cout << playerName << " won!" << std::endl;
}

void	Player::Lose(void) const
{
	std::cout << playerName << " lost!" << std::endl;
}

void	Player::Push(void) const
{
	std::cout << playerName << "! Draw!" << std::endl;
}

/*------------House------------*/

class House : public GenericPlayer
{
public:
	House(const string name="House") : GenericPlayer(name) {};
	virtual ~House() {};

	virtual bool	IsHitting();
	void			FlipFirstCard();
};

bool	House::IsHitting()
{
	return (GetTotal() <= 16);
}

void	House::FlipFirstCard()
{
	if (cards_in_hand.empty())
	{
		cout << "Deck is empty!" << endl;
	}
	else
	{
		cards_in_hand.front()->Flip();
	}
}

/*------------Deck-------------*/

class Deck : public Hand
{
public:
	Deck() { Populate(); };
	void	Populate(void);
	void	Shuffle(void);
	void	Deal(Hand& aHand);
	void	AdditionalCards(GenericPlayer& aGenerlcPlayer);
	~Deck() {};
};

void	Deck::Populate(void)
{
	cards_in_hand.clear();
	for (uint32_t i = Card::ace; i < Card::king; ++i)
	{
		for (uint32_t j = Card::hearts; j < Card::crosses; ++j)
		{
			Add(new Card(static_cast<Card::suits>(j), static_cast<Card::types>(i)));
		}
	}
}

void	Deck::Shuffle(void)
{
	std::random_device	rd;
    std::mt19937		g(rd());
 
    std::shuffle(cards_in_hand.begin(), cards_in_hand.end(), g);
}

void	Deck::Deal(Hand& aHand)
{
	if (cards_in_hand.empty())
	{
		cout << "Hand is empty!" << endl;
	}
	else
	{
		aHand.Add(cards_in_hand.back());
		cards_in_hand.pop_back();
	}
}

void	Deck::AdditionalCards(GenericPlayer& aGenerlcPlayer)
{
	while (aGenerlcPlayer.IsHitting() && !aGenerlcPlayer.IsBoosted())
	{
		Deal(aGenerlcPlayer);

		cout << aGenerlcPlayer;
		if (aGenerlcPlayer.IsBoosted())
		{
			aGenerlcPlayer.Bust();
		}
	}
}

/*------------Game-------------*/

class Game
{
private:
	Deck			gameDeck;
	House			gameHouse;
	vector<Player>	gamePlayers;
public:
	Game(const vector<string> &names);
	~Game() {};

	void	Play(void);
};

Game::Game(const vector<string> &names)
{
	if (names.empty())
	{
		cout << "No player was initiated!" << endl;
	}
	else
	{
		for (auto it = names.begin(); it != names.end(); ++it)
		{
			gamePlayers.push_back(Player(*it));
		}
		gameDeck.Populate();
		gameDeck.Shuffle();
	}
}

/*
	1. Раздаём по две карты игрокам
	2. Раздаём две карты диллеру
	3. Прячем первую карту диллера
	4. Открываем все карты игроков
	5. Раздаём по дополнительной карте игрокам
	6. Показываем первую карту диллера
	7. Раздаем диллеру еще карту
	8. Проверка диллера и переход к проверке игроков
*/
void	Game::Play(void)
{
	uint32_t	cards_on_start;

	cards_on_start = 2;
	for (uint32_t i = 0; i < cards_on_start; ++i)
	{
		for (auto it = gamePlayers.begin(); it != gamePlayers.end(); ++it)
		{
			gameDeck.Deal(*it);
		}
		gameDeck.Deal(gameHouse);
	}

	gameHouse.FlipFirstCard();

	for (auto it = gamePlayers.begin(); it != gamePlayers.end(); ++it)
	{
		cout << *it << endl;
	}
	cout << gameHouse << endl;

	for (auto it = gamePlayers.begin(); it != gamePlayers.end(); ++it)
	{
		gameDeck.AdditionalCards(*it);
	}

	gameHouse.FlipFirstCard();
	cout << gameHouse << endl;

	if (gameHouse.IsBoosted())
	{
		for (auto it = gamePlayers.begin(); it != gamePlayers.end(); ++it)
		{
			if (!(*it).IsBoosted())
			{
				(*it).Win();
			}
		}
	}
	else
	{
		for (auto it = gamePlayers.begin(); it != gamePlayers.end(); ++it)
		{
			if (!(it->IsBoosted()))
			{
				if (it->GetTotal() < gameHouse.GetTotal())
				{
					it->Lose();
				}
				else if (it->GetTotal() > gameHouse.GetTotal())
				{
					it->Win();
				}
				else
				{
					it->Push();
				}
			}
		}
	}
	for (auto it = gamePlayers.begin(); it != gamePlayers.end(); ++it)
	{
		it->Clear();
	}
	gameHouse.Clear();
}

int		main(void)
{
	uint16_t			number_of_players;
	vector<string>		players;
	string				name;

	number_of_players = 0;
	cout << "\n\nWelcome to Blackjack game\n\n";

	do
	{
		cout << "Enter the number of players (min 1; max 7): ";
		cin >> number_of_players;

		if (number_of_players < 1 || number_of_players > 7)
		{
			cout << "Wrong number of players!" << endl;
		}
	} while (number_of_players < 1 || number_of_players > 7);
	
	for (uint16_t i = 0; i < number_of_players; ++i)
	{
		cout << "Enter the name of player " << i << ": ";
		cin >> name;
		players.push_back(name);
	}

	cout << endl;

	Game	newGame(players);
	uint8_t	continue_game; 

	continue_game = 'y';
	while (continue_game == 'Y' || continue_game == 'y')
	{
		newGame.Play();
		cout << "Do you want to continue (Y or N)? ";
		cin >> continue_game;
	}
	players.clear();
	return (0);
}