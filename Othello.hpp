/*
 * Othello.hpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Tim Stumper & Jason Haynberg
 */

#ifndef OTHELLO_HPP_
#define OTHELLO_HPP_
#include <iostream>
#include "Player.hpp"
using namespace std;

class Othello{

	char board[8][8];
	int boardSize;
	Player p1;
	Player p2;
	int numplayers;

public:

	Othello();

	Othello(string, char);

	Othello(string, char, string, char);

	void makemat();

	void printmat();

	void placepiece(Player, char);

	int countandflippieces(int, int, Player, bool);

	int flip(int, int, int, int, Player, bool, char);

	void ckwin();

	void compplacepiece(Player);

	bool isValidPiece(int, int);

	void playGame();


};
#endif /* OTHELLO_HPP_ */
