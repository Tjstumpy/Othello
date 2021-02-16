/*
 * Player..cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Tim Stumper & Jason Haynberg
 */
#include "Player.hpp"
#include <iostream>
using namespace std;

	Player::Player(){
		name = "CPU1";
		color = 'O';
	}

	Player::Player(string n, char c){
		name = n;
		color = c;
	}
