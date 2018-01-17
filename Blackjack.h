#include <iostream>
#include <vector>
#include <algorithm> 
#include <ctime>
#include <string>

using namespace std;
class Card
{
private:
	char m_card;         
	int m_value,         
		m_suite;             
	string m_nameS;
	bool m_given;        

	int assignValue();

public:
	Card(char, int);
	Card(const Card&);

	int getValue()        const;
	int getSuite()        const;
	string getName()      const;
	bool getIfGiven()     const;
	char getCard()        const;

	void setGiven(bool x);

	void nameCard();
};

int Card::assignValue()
{
	if (m_card == 'A')         return 11;
	else if (m_card == 'T' ||
		m_card == 'J' ||
		m_card == 'Q' || m_card == 'K')   return 10;
	else     return (m_card - '0');
}

Card::Card(char cardV, int suite)
{
	m_card = cardV;
	m_value = assignValue();
	m_suite = suite;
	m_given = false;
}

Card::Card(const Card& card)
{
	m_card = card.getCard();
	m_value = card.getValue();
	m_suite = card.getSuite();
	m_nameS = card.getName();
	m_given = card.getIfGiven();
}

int Card::getValue() const
{
	return m_value;
}

int Card::getSuite() const
{
	return m_suite;
}

string Card::getName() const
{
	return m_nameS;
}

bool Card::getIfGiven() const
{
	return m_given;
}

char Card::getCard() const
{
	return m_card;
}

void Card::setGiven(bool x)
{
	m_given = x;
}



void Card::nameCard()
{
	switch (m_suite)
	{
	case 0: m_nameS = "spades"; break;
	case 1: m_nameS = "clubs"; break;
	case 2: m_nameS = "hearts"; break;
	case 3: m_nameS = "diamonds";
	}
	if (m_card == 'A')       cout << "Ace";
	else if (m_card == 'J') cout << "Joker";
	else if (m_card == 'Q') cout << "Queen";
	else                    cout << m_value;

	cout << " of " << m_nameS << endl;
}

class Deck
{
private:
	vector<Card*> m_deck;

public:
	Deck();

	void fillDeck();
	void shuffle();
	Card giveCard();
};

Deck::Deck()
{ 
	fillDeck();
	shuffle();
}

void Deck::fillDeck()
{
	for (int i = 1; i <= 12; ++i)
	{
		char c;
		switch (i) {
		case 1:  c = 'A'; break;
		case 2:  c = '2'; break;
		case 3:  c = '3'; break;
		case 4:  c = '4'; break;
		case 5:  c = '5'; break;
		case 6:  c = '6'; break;
		case 7:  c = '7'; break;
		case 8:  c = '8'; break;
		case 9:  c = '9'; break;
		case 10:  c = 'T'; break;
		case 11:  c = 'J'; break;
		case 12:  c = 'Q'; break;
		case 13:  c = 'K'; break;
		}
		for (int n = 0; n <= 3; ++n)
		{
			m_deck.push_back(new Card(c, n));
		}
	}
}

void Deck::shuffle()
{
	random_shuffle(m_deck.begin(), m_deck.end());
}

Card Deck::giveCard()
{
	for (int i = 0; i < m_deck.size(); ++i)
	{
		if (!m_deck[i]->getIfGiven())
		{
			m_deck[i]->setGiven(1);
			return (*m_deck[i]);
		}
	}
}

class Hand
{

private:
	vector<Card> m_hand;

public:

	void init(Card, Card);
	void display();
	void displayAsDealer();
	void addCard(Card);

	int getNumOfCards();
	int getTotalVal();
};

void Hand::init(Card card1, Card card2)
{
	m_hand.push_back(card1);
	m_hand.push_back(card2);
}

void Hand::display()
{
	for (vector<Card>::iterator iter = m_hand.begin();
		iter != m_hand.end(); (++iter))
	{
		iter->nameCard();
	}
}

void Hand::displayAsDealer()
{
	m_hand[0].nameCard();
}

void Hand::addCard(Card card)
{
	cout << "\nTook out: ";
	card.nameCard();

	m_hand.push_back(card);
}

int Hand::getTotalVal()
{
	int sum = 0;
	for (vector<Card>::iterator iter = m_hand.begin();
		iter != m_hand.end(); (++iter))
	{
		sum += iter->getValue();
	}
	return sum;
}

int Hand::getNumOfCards()
{
	return m_hand.size();
}

class Player
{
protected:
	Deck m_deck;
	Hand m_hand;
	bool m_canGetCards;
	int score;

public:
	Player(Deck deck);
	void plant();
	void anotherCard();
	void seeCards();

	int getScore() const;

	bool lost();
	bool won();
};

Player::Player(Deck deck)
{
	m_canGetCards = 1;
	m_deck = deck;
	m_hand.init(deck.giveCard(), deck.giveCard());
}

void Player::plant()
{
	m_canGetCards = 0;
	score = m_hand.getTotalVal();
}

void Player::anotherCard()
{
	if (m_canGetCards) m_hand.addCard(m_deck.giveCard());
	else cout << "You cannot get more cards." <<endl;
}

bool Player::lost()
{
	if (m_hand.getTotalVal() > 21)
	{
		cout << "You lost." << endl;
		return true;
	}
	return false;
}

bool Player::won()
{
	return (m_hand.getTotalVal() == 21 && m_hand.getNumOfCards() == 2);
}

void Player::seeCards()
{
	cout << "Your cards: ";
	m_hand.display();
}

int Player::getScore() const
{
	return score;
}

class Dealer : public Player  
{
public:
	using Player::Player;

	void seeCard();
	void game(Player);
};

void Dealer::seeCard()
{
	cout << "Dealer's card: ";
	m_hand.displayAsDealer();
	cout << endl;
}

void Dealer::game(Player play)
{
	while (m_hand.getTotalVal() <= 21)
	{
		cout << "Cards: ";
		m_hand.display();
		cout<<endl;
		if (m_hand.getTotalVal() > play.getScore() && m_hand.getTotalVal() <= 21)
		{
			cout << "The dealer won because his score was greater than yours and it didn't exceed 21 in any form." << endl;
			return;
		}
		if (m_hand.getTotalVal() == play.getScore())
		{
			cout << "A tie! " << endl;
			return;
		}
		anotherCard();
	}
	if (m_hand.getTotalVal() > 21)
	{
		cout << "The delaler lost.";
		return;
	}
}

void introduct()
{
	cout << "Controls: 1 for take another card" << endl;
	cout << "2 for planting" << endl;
	cout << "\n\n";
	cout << "Have Fun!! \n\n" << endl;
}

