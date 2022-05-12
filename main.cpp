#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>

using namespace std;

int boardX = 20;
int boardY = 40;

vector<vector<int> > board(boardX, vector<int>(boardY));
vector<vector<int> > tailboard(boardX, vector<int>(boardY));

int headX = 10;
int headY = 10;
int tailX = 11;
int tailY = 10;
int appleX = 8;
int appleY = 10;
int score = 1;
int gameOver = 0;
int dir = 1; //0=up, 1=right, 2=down, 3=left
int taildir = 1; //dir but +1 where 0 = none
int init = 0;

void setup() {
	/**
	initializes everything
	*/

	for (int i = 0; i < boardX; i++) {
		board[i][0] = 1;
		board[i][(boardY - 1)] = 1;
	}
	for (int i = 1; i < (boardY - 1); i++) {
		board[0][i] = 1;
		board[(boardX - 1)][i] = 1;
	}
	
	board[headX][headY] = 2;
	board[appleX][appleY] = 3;
}

void draw() {
	/**
	draws the board
	*/
	system('cls');
	cout << "score: " << score << "\n";
	for (int i = 0; i < boardX; i++) {
		for (int j = 0; j < boardY; j++) {
			if (board[i][j] == 1)
				cout << "#";
			else if (board[i][j] == 0)
				cout << " ";
			else if (board[i][j] == 2)
				cout << "0";
			else if (board[i][j] == 3)
				cout << "*";
			else if (board[i][j] == 4)
				cout << "0";
		}
		cout << "\n";
	}
}

void logic() {
	/**
	performs all logic
	*/
	if (init == 0)
		tailboard[tailX][tailY] = 1;
			
	tailboard[headX][headY] = dir;

	if (_kbhit()) {
		switch(_getch()) {
			case 119:
				dir = 0;
				break;
			case 100:
				dir = 1;
				break;
			case 115:
				dir = 2;
				break;
			case 97:
				dir = 3;
				break;
		}
	}
	
	switch (dir) {
		case 0:
			headX--;
			break;
		case 1:
			headY++;
			break;
		case 2:
			headX++;
			break;
		case 3:
			headY--;
			break;
	}

	if ((board[headX][headY] == 1) || ((board[headX][headY] == 2) && (board[headX][headY] != 1))) {
		gameOver++;
	}
	
	if ((headX == appleX) && (headY == appleY)) {
		score++;
		board[appleX][appleY] = 0;
		appleX = rand() % (boardX - 2) + 1;
		appleY = rand() % (boardY - 2) + 1;
	}
	else
		board[tailX][tailY] = 0;
	taildir = (tailboard[tailX][tailY] + 1);
	tailboard[tailX][tailY] = 0;
		
	switch (taildir) {
		case 1:
			tailX--;
			break;
		case 2:
			tailY++;
			break;
		case 3:
			tailX++;
			break;
		case 4:
			tailY--;
			break;
	}
	
	board[headX][headY] = 2;
	
	board[appleX][appleY] = 3;
	init = 1;
}

int main() {
  setup();
	draw();
	while (gameOver == 0) {
		this_thread::sleep_for(chrono::milliseconds(100));
		logic();
		draw();
	}
}
