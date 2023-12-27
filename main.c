/*
	Programmer: Cole Clark
	Date: 12-1-2020

	Description: Poker game for PA7 with some code from Deitel & Deitel

*/

#include "poker.h"

int main(void)
{

	int quit_game = 0;
	int checked_option = 0;
	int again_or_menu = 0;

	int wins = 0;
	int losses = 0;
	int draws = 0;

	while (quit_game != 1)
	{

		int selected_option = 0;

		if (again_or_menu == 0 || again_or_menu == 2)
		{

			while (quit_game != 1 && checked_option != 2) // menu code from PA5
			{

				selected_option = game_menu(); // prints game menu and stores the user input as selected_option
				checked_option = check_menu_option(selected_option); // checks the selected option to make sure it is within the proper range and returns selected_option if it is

				if (checked_option == 3)
				{
					quit_game = 1;
				}
			}

		}

		checked_option = 0;

		if (quit_game != 1)
		{

			Hand player_hand;
			Hand player_hand2;
			Hand dealer_hand;
			Hand dealer_hand2;

			int redraw_or_not = 0;
			int num_cards_redraw = 0;
			int cards_to_redraw[5] = { 0 };

			char hidden_hand[6] = { 'O', 'O','O','O','O' };
			int dealer_faces[13] = { 0 };
			int dealer_cards[5] = { 0 };
			int dealer_pair = 0;
			int dealer_pair1 = 0;
			int dealer_pair2 = 0;
			int dealer_tok = 0;
			int dealer_tok_value = 0;
			int dealer_fok = 0;
			int dealer_fok_value = 0;
			int dealer_flush = 0;
			int dealer_almost_flush = 0;
			int dealer_card_to_redraw = 0;
			int dealer_straight = 0;
			int d_royal_flush_check = 0;
			int d_score = 0;
			int d_hand_type = 0;

			int player_pair = 0;
			int player_tok = 0;
			int player_fok = 0;
			int player_flush = 0;
			int player_straight = 0;
			int player_pair1 = 0;
			int player_pair2 = 0;
			int player_tok_value = 0;
			int player_fok_value = 0;
			int player_faces[13] = { 0 };
			int player_cards[5] = { 0 };
			int player_almost_flush = 0;
			int player_card_to_redraw = 0;
			int p_royal_flush_check = 0;
			int p_score = 0;
			int p_hand_type = 0;

			//code from Deitel & Deitel

			/* initialize suit array */
			const char* suit[4] = { "Hearts", "Diamonds", "Clubs", "Spades" };

			/* initialize face array */
			const char* face[13] = { "Ace", "Deuce", "Three", "Four", "Five", "Six", "Seven", "Eight",
				"Nine", "Ten", "Jack", "Queen", "King" };

			/* initalize deck array */
			int deck[4][13] = { 0 };

			srand((unsigned)time(NULL)); /* seed random-number generator */

			shuffle(deck);
			deal(deck, &player_hand, 5, 1);

			// end of code from Deitel & Deitel

			deal(deck, &player_hand2, 5, 10);
			deal(deck, &dealer_hand, 5, 20);
			deal(deck, &dealer_hand2, 5, 30);

			/*show_hand(player_hand, face, suit);
			printf("\n\n");
			show_hand(player_hand2, face, suit);
			printf("\n\n");
			show_hand(dealer_hand, face, suit);
			printf("\n\n");
			show_hand(dealer_hand2, face, suit);
			printf("\n\n");

			system("pause");*/

			find_matches(dealer_hand, dealer_faces, dealer_cards);
			dealer_pair = pair(dealer_hand, &dealer_pair1, &dealer_pair2, dealer_faces, dealer_cards);
			dealer_tok = three_of_kind(dealer_hand, &dealer_tok_value, dealer_faces, dealer_cards);
			dealer_fok = four_of_kind(dealer_hand, &dealer_fok_value, dealer_faces, dealer_cards);
			dealer_flush = flush(dealer_hand, &dealer_almost_flush, &dealer_card_to_redraw);
			dealer_straight = straight(dealer_hand, dealer_faces, &d_royal_flush_check);



			redraw_or_not = redraw_cards(player_hand, face, suit, hidden_hand, 1, wins, losses, draws);

			if (redraw_or_not == 1)
			{

				num_cards_redraw = redraw_how_many(player_hand, face, suit, hidden_hand, 1, wins, losses, draws);
				redraw_which_cards(player_hand, face, suit, num_cards_redraw, cards_to_redraw, hidden_hand, 1, wins, losses, draws);
				
				redraw_selected_cards(&player_hand, player_hand2, num_cards_redraw, cards_to_redraw);

			}

			system("cls");


			dealer_redraw(&dealer_hand, dealer_hand2, dealer_pair, dealer_tok, dealer_fok, dealer_flush, dealer_almost_flush, dealer_card_to_redraw, dealer_straight, dealer_cards, hidden_hand);

			for (int i = 0; i != 5; ++i)
			{
				dealer_cards[i] = 0;
			}
			for (int i = 0; i != 13; ++i)
			{
				dealer_faces[i] = 0;
			}

			find_matches(dealer_hand, dealer_faces, dealer_cards);
			dealer_pair = pair(dealer_hand, &dealer_pair1, &dealer_pair2, dealer_faces, dealer_cards);
			dealer_tok = three_of_kind(dealer_hand, &dealer_tok_value, dealer_faces, dealer_cards);
			dealer_fok = four_of_kind(dealer_hand, &dealer_fok_value, dealer_faces, dealer_cards);
			dealer_flush = flush(dealer_hand, &dealer_almost_flush, &dealer_card_to_redraw);
			dealer_straight = straight(dealer_hand, dealer_faces, &d_royal_flush_check);

			find_matches(player_hand, player_faces, player_cards);
			player_pair = pair(player_hand, &player_pair1, &player_pair2, player_faces, player_cards);
			player_tok = three_of_kind(player_hand, &player_tok_value, player_faces, player_cards);
			player_fok = four_of_kind(player_hand, &player_fok_value, player_faces, player_cards);
			player_flush = flush(player_hand, &player_almost_flush, &player_card_to_redraw);
			player_straight = straight(player_hand, player_faces, &p_royal_flush_check);

			p_score = compute_score(player_pair, player_tok, player_fok, player_flush, player_straight, player_pair1, player_tok_value, player_fok_value, p_royal_flush_check, &p_hand_type);
			d_score = compute_score(dealer_pair, dealer_tok, dealer_fok, dealer_flush, dealer_straight, dealer_pair1, dealer_tok_value, dealer_fok_value, d_royal_flush_check, &d_hand_type);

			show_hidden_hand(hidden_hand, wins, losses, draws);
			show_hand(player_hand, face, suit, 1);


			system("pause");
			system("cls");

			printf("Wins: %d\t\tLosses: %d\tDraws: %d\n\n", wins, losses, draws);
			show_hand(dealer_hand, face, suit, 2);
			printf("\n");
			show_hand(player_hand, face, suit, 1);

			/*printf("dealer's cards\n\n");
			for (int i = 0; i != 5; ++i)
			{
				printf("%d. %d\n", i + 1, dealer_cards[i]);
			}

			printf("player's cards\n\n");
			for (int i = 0; i != 5; ++i)
			{
				printf("%d. %d\n", i + 1, player_cards[i]);
			}

			printf("player score: %d\n", p_score);
			printf("dealer score: %d\n", d_score);*/

			declare_winner(d_score, p_score, dealer_faces, player_faces, dealer_pair2, player_pair2, &wins, &losses, &draws, p_hand_type, d_hand_type);

			/*printf("\n");
			printf("player score: %d\n", p_score);
			printf("dealer score: %d\n", d_score);

			printf("\n");
			printf("Player pair 1: %d\n", player_pair1);
			printf("Player pair 2: %d\n", player_pair2);
			printf("Player Three of a kind: %d\n", player_tok_value);
			printf("Player four of a kind: %d\n", player_fok_value);
			printf("\n");
			printf("dealer pair 1: %d\n", dealer_pair1);
			printf("dealer pair 2: %d\n", dealer_pair2);
			printf("dealer Three of a kind: %d\n", dealer_tok_value);
			printf("dealer four of a kind: %d\n", dealer_fok_value);*/

			system("pause");

			again_or_menu = play_again();


		}
	}


	return 0;
}