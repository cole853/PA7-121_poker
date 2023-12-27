/*
	Programmer: Cole Clark
	Date: 12-1-2020

	Description: Poker game for PA7 with some code from Deitel & Deitel

*/

#ifndef POKER_H
#define POKER_H

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct card
{

	int face;
	int suit;

} Card;

typedef struct hand
{

	Card hand_array[6];

} Hand;

//code from Deitel & Deitel

void shuffle(int wDeck[][13]);
void deal(const int wDeck[][13], Hand *h, int number_of_cards, int start); // modified to deal 5 hands and place them in Hand struct

// end of code from Deitel & Deitel


//prints the hand thats entered
void show_hand(Hand player_hand, const char* wFace[], const char* wSuit[], int player);

//prints the game menu and gets an input from the user then returns the input from the user
int game_menu(void);

//checks to see if the value entered by the user is an option then performs the propper action
int check_menu_option(int selected_option);

//prints out the game rules
void print_rules(void);

//asks the player if they would like to play again and returns their response
int play_again(void);

//reprints both hands and asks the user if they would like to redraw any of their cards then returns their answer
int redraw_cards(Hand h, const char* wFace[], const char* wSuit[], char hand[], int player, int wins, int losses, int draws);

//asks the user how many cards they would like to redraw then returns the answer
int redraw_how_many(Hand h, const char* wFace[], const char* wSuit[], char hand[], int player, int wins, int losses, int draws);

// asks the user which cards they would like to redraw then stores the answers in an integer array
void redraw_which_cards(Hand h, const char* wFace[], const char* wSuit[], int number_of_cards, int cards_to_redraw[], char hand[], int player, int wins, int losses, int draws);

//redraws the cards selected by the user
void redraw_selected_cards(Hand* h, Hand h2, int number_of_cards, int cards_to_redraw[]);

//determines if their is one pair or two pairs in a hand and returns the number of pairs then returns the value of the one pair or two pairs through pointers
int pair(Hand h, int* pair_value1, int* pair_value2, int faces[], int cards[]);

//determines if their is a three of a kind returns one if there is and 0 if there isnt then returns the value of the three of a kind through a pointer
int three_of_kind(Hand h, int* tok_value, int faces[], int cards[]);

//determines if there is a four of a kind returns one if there is and returns the value of the four of a kind through a pointer
int four_of_kind(Hand h, int* fok_value, int faces[], int cards[]);

//creates an array that shows how many cards values match each card in the hand and creates an array that adds one for each card in the spot corresponding to the cards value
void find_matches(Hand h, int faces[], int cards[]);

//determines if the hand has a flush or if its close to havind a flush returns one if the hand contains a flush and returns 1 through a pointer if the hand has 4 cards with the same suit
int flush(Hand h, int* almost_flush, int *card_to_redraw);

//determines if the hand has a straight and returns one if it does also returns one through a pointer if the straight is ace, king, queen, jack, ten to check for royal flush later
int straight(Hand h, int faces[], int* check_royal_flush);

//prints a character array to hide the dealers hand
void show_hidden_hand(char hand[], int wins, int losses, int draws);

//redraws for the dealer
void dealer_redraw(Hand *h, Hand h2, int pair, int tok, int fok, int flush, int almost_flush, int redraw, int straight, int cards[], char hidden_hand[]);

// determines the hand score and returns the score (score is hand combination value + value of cards in combination)
int compute_score(int pair, int tok, int fok, int flush, int straight, int pair_value1, int tok_value, int fok_value, int check_royal_flush, int* hand);

//adds 1 to the players score with the highest card if both scores are 0 and adds 1 to players score if they have the highest second pair after both players have two pairs and the first pair is equal
//Then prints out which player won and what each player had
void declare_winner(int d_score, int p_score, int d_faces[], int p_faces[], int d_pair_value2, int p_pair_value2, int* wins, int* losses, int* draws, int p_hand_type, int d_hand_type);

#endif 