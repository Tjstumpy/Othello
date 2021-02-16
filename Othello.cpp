
/*
 * Othello.cpp
 *
 *  Created on: Sep 15, 2020
 *      Author: Tim Stumper & Jason Haynberg
 */
#include "Othello.hpp"
#include <iostream>
using namespace std;

	Othello::Othello(){
		boardSize = 8;
		numplayers = 0;
		p1 = Player();
		p2 = Player("CPU2", 'B');
		}

	Othello::Othello(string st1, char c){
		boardSize = 8;
		numplayers = 1;
		p1 = Player(st1, c);
		if (c == 'O')
			p2 = Player("CPU", 'B');
		else if(c == 'B')
			p2 = Player("CPU", 'O');
	}

	Othello::Othello(string st1, char c, string st2, char c2){
		boardSize = 8;
		numplayers = 2;
		p1 = Player(st1, c);
		p2 = Player(st2, c2);
	}

	void Othello::makemat(){
		// fill board with '_'
		for(int i = 0; i < boardSize; i++){
			for(int j = 0; j < boardSize; j++){
				board[i][j] = '_';
			}
			//print B's in center [3][3] and [4][4]
			board[(boardSize/2)-1][(boardSize/2)-1] = 'B';
			board[(boardSize/2)][(boardSize/2)] = 'B';

			//print O's in center [3][4] and [4][3]
			board[(boardSize/2)-1][(boardSize/2)] = 'O';
			board[(boardSize/2)][(boardSize/2)-1] = 'O';
		}
	}

	void Othello::printmat(){
		for(int i = 0; i <= boardSize; i++){
			for(int j = 0; j <= boardSize; j++){
				if(j == 0 && i == 0)
					cout << ' ' << "\t";
				else if(j == 0)
					cout << i-1 << "\t";
				else if(i == 0)
					cout << j-1 << "\t";
				else
					cout << board[i-1][j-1] << "\t";

			}
			cout << endl;
		}
	}

	void Othello::placepiece(Player p, char color){
		int x, y;

		    do{
		        cout << "Enter the x coordinate: " << endl;
		        cin >> y;
		        cout << "Enter the y coordinate: "<< endl;
		        cin >> x;
		    }while(x < 0 || x > 7 || y < 0 || y > 7 || board[x][y] != '_');

		    board[x][y] = p.color;


		    if(countandflippieces(x, y, p, true) == 0){
		        cout << "Player forfeits turn" << endl;
		        board[x][y] = '_';
		    }
	}

//
//I'M AWARE THIS IS SPHAGETTI CODE BUT I COULD NOT FIND A BETTER SOLUTION BEFORE DEADLINE I'M SORRY
//vvvvvvvvvvvvvvvvvvvvvvv
	int Othello::countandflippieces(int x, int y, Player p, bool canFlip){
		int count = 0;
		//going from chosen point and outward
		//HORIZONTAL
		for(int i = y; i < boardSize; i++){
			//checking right
			if(board[x][i] == '_')
				break;
			if(board[x][y] == board[x][i])
				count += flip(y ,i, x, 0, p, canFlip, 'h');
		}
	//cout << p.color << "right: " << count << endl;
		for(int j = y; j >= 0; j--){
			if(board[x][j] == '_')
				break;
			if(board[x][y] == board[x][j])
				count += flip(y, j, x, 0, p, canFlip, 'h');
		}
	//cout << p.color << "left: " << count << endl;
		//VERTICAL
		for(int i = x; i < boardSize; i++){
			//checking down
			if(board[i][y] == '_')
				break;
			if(board[x][y] == board[i][y])
				count += flip(x ,i, y, 0, p, canFlip, 'v');
		}
	//cout << p.color << "down: " << count << endl;
		for(int j = x; j >= 0; j--){
			//checking up
			if(board[j][y] == '_')
				break;
			if(board[x][y] == board[j][y])
				count += flip(x, j, y, 0, p, canFlip, 'v');
		}
	//cout << p.color << "up: " << count << endl;
		//DIAGONAL
		//upRight
		for(int i = x, j = y; i >= 0 && j < boardSize; i--, j++){
			if(board[i][j] == '_')
				break;
			if(board[x][y] == board[i][j]){
				count += flip(x, i, y, j, p, canFlip, '1');
			}
		}
	//cout << p.color << "upRight: " << count << endl;
		//upLeft
		for(int i = x, j = y; i >= 0 && j >= 0; i--, j--){
			if(board[i][j] == '_')
				break;
			if(board[x][y] == board[i][j])
				count += flip(x, i, y, j, p, canFlip, '2');
		}
	//cout << p.color << "upLeft: " << count << endl;
		//downLeft
		for(int i = x, j = y; i < boardSize && j >= 0; i++, j--){
			if(board[i][j] == '_')
				break;
			if(board[x][y] == board[i][j])
				count += flip(x, i, y, j, p, canFlip, '3');
		}
	//cout << p.color << "downLeft: " << count << endl;
		//downRight
		for(int i = x+1, j = y+1; i < boardSize && j < boardSize; i++, j++){
			if(board[i][j] == '_')
				break;
			if(board[x][y] == board[i][j])
				count += flip(x, i, y, j, p, canFlip, '4');
		}
	//cout << p.color << "downRight: " << count << endl;
		//cout << p.color << ": " << count << endl;
		return count;
	}

	int Othello::flip(int x, int x2, int y, int y2, Player p, bool canFlip, char dir){
		int count = 0;
		char notColor;
		if(p.color == 'B')
			notColor = 'O';
		else
			notColor = 'B';
		//cout << "in the flip method" << endl;
		switch(dir){
			case('h'): //horizontal
				if(x < x2){
					for(int i = x+1; i < x2 && board[y][i] == notColor; i++){
						if(canFlip)
							board[y][i] = p.color;
						count++;
					}
				}
				else if(x > x2){
					for(int i = x-1; i > x2 && board[y][i] == notColor; i--){
						if(canFlip)
							board[y][i] = p.color;
						count++;
					}
				}
				break;
			case('v'): //vertical
				if(x < x2){
					for(int i = x+1; i < x2 && board[i][y] == notColor; i++){
						if(canFlip)
							board[i][y] = p.color;
						count++;
					}
				}
				else if(x > x2){
					for(int i = x-1; i > x2 && board[i][y] == notColor; i--){
						if(canFlip)
							board[i][y] = p.color;
						count++;
				}
				break;
			case('1'): //diagonal
				for(int i = x-1, j = y+1; j < y2 && board[i][j] == notColor; i--, j++){
					if(canFlip)
						board[i][j] = p.color;
					count++;
				}
				break;
			case('2'):
				for(int i = x-1, j = y-1; i > x2 && board[i][j] == notColor; i--, j--){
					if(canFlip)
						board[i][j] = p.color;
					count++;
				}
				break;
			case('3'):
				for(int i = x+1, j = y-1; i < x2 && board[i][j] == notColor; i++, j--){
					if(canFlip)
						board[i][j] = p.color;
					count++;
				}
				break;
			case('4'):
				for(int i = x+1, j = y+1; i < x2 && board[i][j] == notColor; i++, j++){
					if(canFlip)
						board[i][j] = p.color;
					count++;
				}
				break;
				}
		}
		return count;
	}

	void Othello::ckwin(){
		int countB = 0, countO = 0;
		for(int i = 0; i < boardSize; i ++){
			for(int j = 0; j < boardSize; j++){
				if(board[i][j] == 'B')
					countB++;
				else if(board[i][j] == 'O')
					countO++;
			}


		}
		if(countB > countO && p1.color == 'B')
			cout << p1.name << " won with: " << countB << " versus " << countO << endl;
		else if(countO > countB && p1.color == 'O')
			cout << p1.name << " won with: " << countO << " versus " << countB << endl;

		if(countB > countO && p2.color == 'B')
			cout << p2.name << " won with: " << countB << " versus " << countO << endl;
		else if(countO > countB && p2.color == 'O')
			cout << p2.name << " won with: " << countO << " versus " << countB << endl;

	}

	void Othello::compplacepiece(Player p){
		//find every playable space
		int maxFlips = 0, maxX = 0, maxY = 0, currentFlip = 0;
		for(int i = 0; i < boardSize; i++){
			for(int j = 0; j < boardSize; j++){
				if(board[i][j] == '_'){
					board[i][j] = p.color;
					currentFlip = countandflippieces(i, j, p, false);
					//cout << "currentflip: " << currentFlip << i << j << endl;
					if(maxFlips < currentFlip){
						maxFlips = currentFlip;
						maxX = i;
						maxY = j;
						//cout<<"New maxFlips, "<<maxFlips<<" with index: "<<maxX<<maxY << endl;
					}
					board[i][j] = '_';
				}
			}
		}
		//cout << maxX << " " << maxY << endl;
	//get index of highest count and call countandflippieces (AS TRUE) with those coords
		board[maxX][maxY] = p.color;
		countandflippieces(maxX, maxY, p, true);
}

	void Othello::playGame(){
	    makemat();
	    printmat();
	    bool play = true;
	    int fullsqrs = 0;
	    Player p = p1;
	    bool whichp = true;
	    bool turn = true;

	    if (rand()%2 == 0) {  // p1 plays first
	    	p = p2;
	    	turn = false;
	    	whichp = false;
	    }

	    while ((play) && (fullsqrs < 60)){
	    	cout << endl << p.name <<" ("<<p.color<<") choose your square: "<< endl;
	        if ((numplayers == 2) || ((numplayers == 1) && turn)){
	            placepiece(p, p.color);
	        }
	        else if ((numplayers == 0) || ((numplayers == 1) && (turn == false))){
	            compplacepiece(p);
	        }

	        turn = !turn;
	        printmat();
	        if (whichp) {
	        	p = p2;
	        	whichp = false;
	        }
	        else {
	            p=p1;
	            whichp = true;
	        }
	        fullsqrs+=1;
	    }
	    ckwin();
	}


