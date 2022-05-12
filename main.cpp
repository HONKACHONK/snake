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
int tailX = 10;
int tailY = 11;
int appleX = 8;
int appleY = 10;
int score = 1;
int gameOver = 0;
int dir = 1; //0=up, 1=right, 2=down, 3=left
int taildir = 1;
int init = 0;


int keypress() {
  system ("/bin/stty raw");
  int c;
  system ("/bin/stty -echo");
  c = getc(stdin);
  system ("/bin/stty echo");
  system ("/bin/stty cooked");
	int d;
	switch(c) {
		case 119:
			d = 0;
			break;
		case 97:
			d = 3;
			break;
		case 115:
			d = 2;
			break;
		case 100:
			d = 1;
			break;
	}
  return d;
}

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
			
	tailboard[headX][headY] = d97ir;

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
			headY++;
			break;
		case 1:
			headX++;
			break;
		case 2:
			headY--;
			break;
		case 3:
			headX--;
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
			tailY++;
			break;
		case 2:
			tailX++;
			break;
		case 3:
			tailY--;
			break;
		case 4:
			tailX--;
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
