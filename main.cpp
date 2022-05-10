#include <iostream>
#include <string>
#include <vector>
#include <thread>
#include <chrono>

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
	cout << "\033[2J\033[0;0H"; //no idea how, but this clears the screen
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
	tailboard[headX][headY] = dir;
	
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

	if ((board[headX][headY] == 1) || ((board[headX][headY] == 2) && (board[headX][headY] != 1))) {
		gameOver++;
	}
	
	if ((headX == appleX) && (headY == appleY)) {
		score++;
		board[appleX][appleY] = 0;
		appleX = rand() % (boardX - 2) + 1;
		appleY = rand() % (boardY - 2) + 1;
	}
	board[tailX][tailY] = 0;
	taildir = (tailboard[tailX][tailY] + 1);
	tailboard[tailX][tailY] = 0;
		
	switch (taildir) {
		case 1:
			tailY++;
		case 2:
			tailX++;
		case 3:
			tailY--;
		case 4:
			tailX--;
	}
	
	board[headX][headY] = 2;
	
	board[appleX][appleY] = 3;
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
