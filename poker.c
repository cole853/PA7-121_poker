/*
	Programmer: Cole Clark
	Date: 12-1-2020

	Description: Poker game for PA7 with some code from Deitel & Deitel

*/

#include "poker.h"

//code from Deitel & Deitel

/* shuffle cards in deck */

void shuffle(int wDeck[][13])
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */

	/* for each of the 52 cards, choose slot of deck randomly */
	for (card = 1; card <= 52; card++)
	{
		/* choose new random location until unoccupied slot found */
		do
		{
			row = rand() % 4;
			column = rand() % 13;
		} while (wDeck[row][column] != 0);

		/* place card number in chosen slot of deck */
		wDeck[row][column] = card;
	}
}

/* deal cards in deck */
void deal(const int wDeck[][13], Hand *h, int number_of_cards, int start) //modified to select 5 cards and enter them in a hand
{
	int row = 0;    /* row number */
	int column = 0; /*column number */
	int card = 0;   /* card counter */
	int counter = 0;

	/* deal each of the 52 cards */
	for (card = start; card <= start + number_of_cards; card++) // changed 52 to 5
	{
		/* loop through rows of wDeck */
		for (row = 0; row <= 3; row++)
		{
			/* loop through columns of wDeck for current row */
			for (column = 0; column <= 12; column++)
			{

				/* if slot contains current card, display card */
				if (wDeck[row][column] == card)
				{
					
					h->hand_array[counter].suit = row; //put the values into hand rather than printing them
					h->hand_array[counter].face = column; //put the values into hand rather than printing them

					counter++;

						//printf("%5s of %-8s%c", wFace[column], wSuit[row], card % 2 == 0 ? '\n' : '\t');
				}
			}
		}
	}
}


// end of code from Deitel & Deitel

//prints the hand thats entered
void show_hand(Hand h, const char* wFace[], const char* wSuit[], int player)
{

	if (player == 1)
	{
		printf("Your hand:\n\n");
	}
	else if (player == 2)
	{
		printf("Dealer's hand:\n\n");
	}

	for (int i = 0; i != 5; i++)
	{
		printf("%d.  %s of %s\n", i + 1, wFace[h.hand_array[i].face], wSuit[h.hand_array[i].suit]);
	}

	printf("\n");
}

//prints the game menu and gets an input from the user then returns the input from the user
int game_menu(void) // menu code from PA5
{
	int selected_option = 0;
	printf("Enter 1 for game rules...\nEnter 2 to start a game of Poker!\nEnter 3 to Exit.\n");
	scanf("%d", &selected_option);

	return selected_option;
}

//checks to see if the value entered by the user is an option then performs the propper action
int check_menu_option(int selected_option) // menu code from PA5
{
	if (selected_option <= 0 || selected_option > 3)
	{
		//printf("\nplease choose one of the menu options.\n\n");
		//system("pause");
		system("cls");
		return 1;
	}
	else if (selected_option == 1)
	{
		print_rules();
	}
	else if (selected_option == 3)
	{
		system("cls");
		printf("\nGoodbye\n\n");

		return 3;
	}
	else
	{
		system("cls");
		return 2;
	}
}

//prints out the game rules
void print_rules(void)
{

	system("cls");

	printf("\n\t\tRules for Poker\n\n");
	printf("1. Each player will be dealt a 5 card hand.\n");
	printf("2. Each player will be able to choose cards to discard.\n");
	printf("3. New cards will be chosen to fill the spots of the discarded cards.\n");
	printf("4. The player with the highest scoring hand is the winner.\n");
	printf("5. Hand score in order from best to worst:\n\n");
	printf("\t1. Royal Flush:\t\tace, king, queen, jack, ten of the same suit.\n");
	printf("\t2. straight Flush:\tall cards have the same suit and are consecutive values.\n");
	printf("\t3. Four Of A Kind:\tfour cards with the same value.\n");
	printf("\t4. Full House:\t\tthree cards of one value and two cards of another.\n");
	printf("\t5. Flush:\t\tall cards are the same suit.\n");
	printf("\t6. Straight:\t\t5 cards of consecutive value.\n");
	printf("\t7. Three Of A Kind:\tthree cards with the same value.\n");
	printf("\t8. Two Pair:\t\ttwo cards with the same value and another two cards with the same value.\n");
	printf("\t9. Pair:\t\ttwo cards with the same value.\n\n");
	printf("6. If both players have the same type of hand above the winner will be the player with the highest card values\n   in their combination.\n");
	printf("7. card values 2 - K have their normal card values with duces being the lowest and kings being the highest.\n   Aces are the only cards higher than kings.\n");
	printf("8. If both players do not have one of the above hands the winner will be the player with the highest card value.\n\n");


	system("pause");
	system("cls");

}

//asks the player if they would like to play again and returns their response
int play_again(void)
{
	int selected_option = 0;

	do
	{
		system("cls");
		printf("Would you like to play again or return to the menu?\nEnter 1 to play again or 2 to return to the menu.\n");
		scanf("%d", &selected_option);

	} while (selected_option != 1 && selected_option != 2);

	system("cls");
	return selected_option;

}

//reprints both hands and asks the user if they would like to redraw any of their cards then returns their answer
int redraw_cards(Hand h, const char* wFace[], const char* wSuit[], char hand[], int player, int wins, int losses, int draws)
{
	int answer = 0;

	do
	{
		system("cls");
		show_hidden_hand(hand, wins, losses, draws);
		show_hand(h, wFace, wSuit, player);
		printf("\n\nWould you like to redraw some of your cards?\nEnter 1 for yes or 2 for no.\n");
		scanf("%d", &answer);

	} while (answer != 1 && answer != 2);

	return answer;
}

//asks the user how many cards they would like to redraw then returns the answer
int redraw_how_many(Hand h, const char* wFace[], const char* wSuit[], char hand[], int player, int wins, int losses, int draws)
{
	int answer = 0;

	do
	{
		system("cls");
		show_hidden_hand(hand, wins, losses, draws);
		show_hand(h, wFace, wSuit, player);
		printf("\n\nHow many cards would you like to redraw?\n");
		scanf("%d", &answer);

	} while (answer < 1 || answer > 5);

	return answer;
}

// asks the user which cards they would like to redraw then stores the answers in an integer array
void redraw_which_cards(Hand h, const char* wFace[], const char* wSuit[], int number_of_cards, int cards_to_redraw[], char hand[], int player, int wins, int losses, int draws)
{
	system("cls");
	show_hidden_hand(hand, wins, losses, draws);
	show_hand(h, wFace, wSuit, player);
	printf("\n\nWhich cards would you like to redraw?\n");

	int answer = 0;

	for (int i = 0; i < number_of_cards; ++i)
	{
		scanf("%d", &answer);
		cards_to_redraw[i] = answer;

		if (answer < 1 || answer > 5)
		{
			//cards_to_redraw = 0, 0, 0, 0, 0;
			redraw_which_cards(h, wFace, wSuit, number_of_cards, cards_to_redraw, hand, player, wins, losses, draws);


		}


	}


}

//redraws the cards selected by the user
void redraw_selected_cards(Hand *h, Hand h2, int number_of_cards, int cards_to_redraw[])
{

	for (int i = 0; i < number_of_cards; ++i)
	{
		int suit = h2.hand_array[cards_to_redraw[i] - 1].suit;
		int face = h2.hand_array[cards_to_redraw[i] - 1].face;



		h->hand_array[cards_to_redraw[i] - 1].suit = suit;
		h->hand_array[cards_to_redraw[i] - 1].face = face;

	}


}

//determines if their is one pair or two pairs in a hand and returns the number of pairs then returns the value of the one pair or two pairs through pointers
int pair(Hand h, int* pair_value1, int* pair_value2, int faces[], int cards[])
{
	int num_of_pairs = 0;
	int first_pair_value = 0;
	int second_pair_value = 0;
	

	for (int j = 0; j != 5; ++j)
	{
		if (cards[j] == 2)
		{

			++num_of_pairs;

		}
	}

	num_of_pairs = num_of_pairs / 2;

	if (faces[0] == 2)
	{
		first_pair_value = 20;
	}

	for (int n = 1; n != 13; ++n)
	{

		if (faces[n] == 2 && first_pair_value == 0)
		{
			first_pair_value = n + 1;
		}
		else if (faces[n] == 2 && first_pair_value != 0)
		{
			second_pair_value = n + 1;
		}

	}

	if (num_of_pairs == 1)
	{
		if (first_pair_value > second_pair_value)
		{
			*pair_value1 = first_pair_value;
		}
		else if (second_pair_value > first_pair_value)
		{
			*pair_value1 = second_pair_value;
		}
	}
	else if (num_of_pairs == 2)
	{
		if (first_pair_value > second_pair_value)
		{
			*pair_value1 = first_pair_value;
			*pair_value2 = second_pair_value;
		}
		else if (second_pair_value > first_pair_value)
		{
			*pair_value1 = second_pair_value;
			*pair_value2 = first_pair_value;
		}

	}

	return num_of_pairs;
}

//determines if their is a three of a kind returns one if there is and 0 if there isnt then returns the value of the three of a kind through a pointer
int three_of_kind(Hand h, int* tok_value, int faces[], int cards[])
{
	int num_of_tok = 0;


	for (int j = 0; j != 5; ++j)
	{
		if (cards[j] == 3)
		{

			++num_of_tok;

		}
	}

	num_of_tok = num_of_tok / 3;

	if (faces[0] == 3)
	{
		*tok_value = 20;
	}

	for (int n = 1; n != 13; ++n)
	{

		if (faces[n] == 3 && *tok_value == 0)
		{
			*tok_value = n + 1;
		}

	}

	return num_of_tok;
}

//determines if there is a four of a kind returns one if there is and returns the value of the four of a kind through a pointer
int four_of_kind(Hand h, int* fok_value, int faces[], int cards[])
{
	
	int num_of_fok = 0;


	for (int j = 0; j != 5; ++j)
	{
		if (cards[j] == 4)
		{

			++num_of_fok;

		}
	}

	num_of_fok = num_of_fok / 4;

	if (faces[0] == 4)
	{
		*fok_value = 20;
	}

	for (int n = 1; n != 13; ++n)
	{

		if (faces[n] == 4 && *fok_value == 0)
		{
			*fok_value = n + 1;
		}

	}

	return num_of_fok;

}

//creates an array that shows how many cards values match each card in the hand and creates an array that adds one for each card in the spot corresponding to the cards value
void find_matches(Hand h, int faces[], int cards[])
{
	for (int i = 0; i != 5; ++i)
	{
		++faces[h.hand_array[i].face];

		if (h.hand_array[i].face == h.hand_array[0].face)
		{
			++cards[0];
		}
		if (h.hand_array[i].face == h.hand_array[1].face)
		{
			++cards[1];
		}
		if (h.hand_array[i].face == h.hand_array[2].face)
		{
			++cards[2];
		}
		if (h.hand_array[i].face == h.hand_array[3].face)
		{
			++cards[3];
		}
		if (h.hand_array[i].face == h.hand_array[4].face)
		{
			++cards[4];
		}


	}

}

//determines if the hand has a flush or if its close to havind a flush returns one if the hand contains a flush and returns 1 through a pointer if the hand has 4 cards with the same suit
int flush(Hand h, int *almost_flush, int *card_to_redraw)
{
	int suit[4] = { 0 };
	int num_of_flush = 0;

	for (int i = 0; i != 5; ++i)
	{
		++suit[h.hand_array[i].suit];
	}
	for (int j = 0; j != 4; ++j)
	{
		if (suit[j] == 5)
		{
			num_of_flush = 1;
		}
		if (suit[j] == 4)
		{
			*almost_flush = 1;
		}
	}

	if (*almost_flush == 1)
	{
		for (int n = 0; n != 4; ++n)
		{
			if (suit[n] == 1)
			{
				for (int k = 0; k != 5; ++k)
				{
					if (h.hand_array[k].suit == n)
					{
						*card_to_redraw = k;
					}
				}
				
			}
		}
	}

	return num_of_flush;

}

//determines if the hand has a straight and returns one if it does also returns one through a pointer if the straight is ace, king, queen, jack, ten to check for royal flush later
int straight(Hand h, int faces[], int *check_royal_flush)
{
	int num_of_straight = 0;

	for (int i = 0; i != 9; ++i)
	{
		if (faces[i] == 1 && faces[i + 1] == 1 && faces[i + 2] == 1 && faces[i + 3] == 1 && faces[i + 4] == 1)
		{
			num_of_straight = 1;
		}
		
	}

	if (faces[0] == 1 && faces[9] == 1 && faces[10] == 1 && faces[11] == 1 && faces[12] == 1)
	{
		num_of_straight = 1;
		*check_royal_flush = 1;
	}

	return num_of_straight;

}

//prints a character array to hide the dealers hand
void show_hidden_hand(char hand[], int wins, int losses, int draws)
{
	printf("Wins: %d\t\tLosses: %d\tDraws: %d\n\n", wins, losses, draws);
	printf("Dealer's hand: \t (O is original cards and R is redrawn cards)\n\n");

	for (int i = 0; i != 5; i++)
	{
		printf("%d.  %c\n", i + 1, hand[i]);
	}
	printf("\n\n");
}

//redraws for the dealer
void dealer_redraw(Hand *h, Hand h2, int pair, int tok, int fok, int flush, int almost_flush, int redraw, int straight, int cards[], char hidden_hand[])
{
	if (flush != 1 && fok != 1 && straight != 1)
	{

		if (almost_flush == 1)
		{

			hidden_hand[redraw] = 'R';
			
			h->hand_array[redraw].face = h2.hand_array[redraw].face;
			h->hand_array[redraw].suit = h2.hand_array[redraw].suit;

		}
		else if (pair == 1 || pair == 2 || tok == 1)
		{
			for (int i = 0; i != 5; ++i)
			{

				if (cards[i] == 1)
				{

					hidden_hand[i] = 'R';

					h->hand_array[i].face = h2.hand_array[i].face;
					h->hand_array[i].suit = h2.hand_array[i].suit;
				}

			}



		}
		else
		{
			int redraw1 = 0;
			int redraw2 = 0;
			int redraw3 = 0;

			do
			{

				redraw1 = rand() % 5 + 1;
				redraw2 = rand() % 5 + 1;
				redraw3 = rand() % 5 + 1;

			} while (redraw1 == redraw2 || redraw1 == redraw3 || redraw2 == redraw3);

			hidden_hand[redraw1] = 'R';
			hidden_hand[redraw2] = 'R';
			hidden_hand[redraw3] = 'R';


			h->hand_array[redraw1].face = h2.hand_array[redraw1].face;
			h->hand_array[redraw1].suit = h2.hand_array[redraw1].suit;

			h->hand_array[redraw2].face = h2.hand_array[redraw2].face;
			h->hand_array[redraw2].suit = h2.hand_array[redraw2].suit;

			h->hand_array[redraw3].face = h2.hand_array[redraw3].face;
			h->hand_array[redraw3].suit = h2.hand_array[redraw3].suit;


		}
	}
}

// determines the hand score and returns the score (score is hand combination value + value of cards in combination)
int compute_score(int pair, int tok, int fok, int flush, int straight, int pair_value1, int tok_value, int fok_value, int check_royal_flush, int* hand)
{
	int score = 0;
	
	if (tok == 1 && pair == 1)
	{
		score = 600 + tok_value;
		*hand = 6;
	}
	else if (pair == 1)
	{
		score = 100 + pair_value1;
		*hand = 1;
	}
	else if (pair == 2)
	{
		score = 200 + pair_value1;
		*hand = 2;
	}
	else if (tok == 1)
	{
		score = 300 + tok_value;
		*hand = 3;
	}
	else if (fok == 1)
	{
		score = 700 + fok_value;
		*hand = 7;
	}
	else if (flush == 1 && check_royal_flush == 1)
	{
		score = 900;
		*hand = 9;
	}
	else if (flush == 1 && straight == 1)
	{
		score = 800;
		*hand = 8;
	}
	else if (flush == 1)
	{
		score = 500;
		*hand = 5;
	}
	else if (straight == 1)
	{
		score = 400;
		*hand = 4;
	}

	return score;

}

//adds 1 to the players score with the highest card if both scores are 0 and adds 1 to players score if they have the highest second pair after both players have two pairs and the first pair is equal
//Then prints out which player won and what each player had
void declare_winner(int d_score, int p_score, int d_faces[], int p_faces[], int d_pair_value2, int p_pair_value2, int* wins, int* losses, int* draws, int p_hand_type, int d_hand_type)
{
	if (p_score == d_score)
	{
		if (p_score == 0 && d_score == 0)
		{
			if (p_faces[0] != d_faces[0])
			{
				if (p_faces[0] > d_faces[0])
				{
					++p_score;
				}
				if (p_faces[0] < d_faces[0])
				{
					++d_score;
				}

			}
			else
			{
				for (int i = 12; i >= 0; --i)
				{
					if (p_faces[i] > d_faces[i])
					{
						++p_score;
						i = -1;
					}
					if (d_faces[i] > p_faces[i])
					{
						++d_score;
						i = -1;
					}
				}
			}
		}
		else if (p_score > 200 && p_score < 300 && d_score > 200 && d_score < 300)
		{
			if (d_pair_value2 > p_pair_value2)
			{
				++d_score;
			}
			else if (p_pair_value2 > d_pair_value2)
			{
				++p_score;
			}
		}
	}

	if (p_score > d_score)
	{
		printf("YOU WON! :)\n\n");
		++*wins;
	}
	else if (p_score < d_score)
	{
		printf("You lost :(\n\n");
		++*losses;
	}
	else if (d_score == p_score)
	{
		printf("It's a draw :|\n\n");
		++*draws;
	}

	if (p_hand_type == 0)
	{
		printf("You had Junk (highest card wins if both hands are junk)\n");
	}
	else if (p_hand_type == 1)
	{
		printf("You had a pair\n");
	}
	else if (p_hand_type == 2)
	{
		printf("You had two pairs\n");
	}
	else if (p_hand_type == 3)
	{
		printf("You had a three of a kind\n");
	}
	else if (p_hand_type == 4)
	{
		printf("You had a straight\n");
	}
	else if (p_hand_type == 5)
	{
		printf("You had a flush\n");
	}
	else if (p_hand_type == 6)
	{
		printf("You had a full house\n");
	}
	else if (p_hand_type == 7)
	{
		printf("You had a four of a kind\n");
	}
	else if (p_hand_type == 8)
	{
		printf("You had a straight flush\n");
	}
	else if (p_hand_type == 9)
	{
		printf("You had a royal flush\n");
	}


	if (d_hand_type == 0)
	{
		printf("The dealer had Junk (highest card wins if both hands are junk)\n\n");
	}
	else if (d_hand_type == 1)
	{
		printf("The dealer had a pair\n\n");
	}
	else if (d_hand_type == 2)
	{
		printf("The dealer had two pairs\n\n");
	}
	else if (d_hand_type == 3)
	{
		printf("The dealer had a three of a kind\n\n");
	}
	else if (d_hand_type == 4)
	{
		printf("The dealer had a straight\n\n");
	}
	else if (d_hand_type == 5)
	{
		printf("The dealer had a flush\n\n");
	}
	else if (d_hand_type == 6)
	{
		printf("The dealer had a full house\n\n");
	}
	else if (d_hand_type == 7)
	{
		printf("The dealer had a four of a kind\n\n");
	}
	else if (d_hand_type == 8)
	{
		printf("The dealer had a straight flush\n\n");
	}
	else if (d_hand_type == 9)
	{
		printf("The dealer had a royal flush\n\n");
	}
}