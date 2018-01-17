#include "Card.h"


int main()
{
	srand(time(0));

	introduct();

	Deck deck;
	Player player(deck);
	Dealer casino(deck);
	char x;
	bool bbreak = 0;

	player.seeCards();
	casino.seeCard();

	if (player.won())
	{
		cout << "You won! " << endl;
	}
	else if (casino.won())
	{
		cout << "The dealer won!" << endl;
	}
	else
	{
		while (!player.lost())
		{
			cout << "What do you want to do: ";
			cin >> x;
			if (x == '1')
			{
				player.anotherCard();
			}
			else if (x == '2')
			{
				player.plant();
				casino.game(player);
				break;
			}
			player.seeCards();
			casino.seeCard();
		}
	}
	cin.clear();
	cin.ignore();
	cin.get();
	return 0;
}