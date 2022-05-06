#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

using namespace std;

int boardX = 20;
int boardY = 40;

vector<vector<int> > board(boardX, vector<int>(boardY));

int headX = 10;
int headY = 10;
int tailX = 9;
int tailY = 10;
int appleX = 8;
int appleY = 10;
int score = 1;
int gameOver = 0;


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
	cout << "\033[2J\033[0;0H"; //no idea how, but clears the screen
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
			
		}
		cout << "\n";
	}
}

void logic() {
	/**
	performs all logic
	*/

	
	int dir = 1; //0=up, 1=right, 2=down, 3=left
	//(getdirection)
	switch (dir) {
		case 0:
			headY++;
		case 1:
			headX++;
		case 2:
			headY--;
		case 3:
			headX--;
	}
	if ((headX == appleX) && (headY == appleY)) {
		score++;
		board[appleX][appleY] = 0;
		appleX = rand() % (boardX - 2) + 1;
		appleY = rand() % (boardY - 2) + 1;
	}
	//(tail logic)
	
	board[headX][headY] = 2;
	board[tailX][tailY] = 0;
	board[appleX][appleY] = 3;
}

int main() {
  setup();
	draw();
	for (int i = 0; i < 10; i++) {
		logic();
		draw();
		this_thread::sleep_for(chrono::milliseconds(1000));
	}
}
