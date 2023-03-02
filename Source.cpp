#include <iostream>
/*
*		indexing	|	user input
*		0 1 2		|	1 2 3
*		3 4 5		|	4 5 6
*		6 7 8		|	7 8 9
*/
class Board {
public:
	bool isPlayer1 = true;
	int squareInfo[9] ={0, 0, 0,	// 0 if noone is on square 1:X 2:O
						0, 0, 0,
						0, 0, 0};
	
	void startMessage() {
		std::cout << "Tic Tac Toe" << std::endl << std::endl;

		std::cout << "1  2  3" << std::endl
				  << "4  5  6" << std::endl
				  << "7  8  9" << std::endl << std::endl << std::endl;
	}

	void drawBoard() {
		system("CLS");
		int counter = 1;
		char currentSquareTranslated;
		std::cout << std::endl;
		for (int square : squareInfo) {
			if (square == 1) 
				currentSquareTranslated = 'X';
			else if (square == 2)
				currentSquareTranslated = 'O';
			else 
				currentSquareTranslated = ' ';
				
			if (counter % 3 == 0) {
				std::cout << currentSquareTranslated << "  " << std::endl;
			}
			else
				std::cout << currentSquareTranslated << "  ";
			counter++;
		}
		std::cout << std::endl;
	}

	void roundControl() {
		int roundCounter = 1;
		while(checkWinner() == 0 && roundCounter < 10) {
			if (isPlayer1) {
				player1Move(player1ChooseSquare());
				isPlayer1 = false;
			}
			else {
				player2Move(player2ChooseSquare());
				isPlayer1 = true;
			}
			roundCounter++;
			drawBoard();
		}
		if (checkWinner() == 1) {
			std::cout << std::endl << "X wins." << std::endl;
		}
		else if (checkWinner() == 2) {
			std::cout << std::endl << "O wins." << std::endl;
		}
		else {
			std::cout << std::endl << "The match ends in a draw." << std::endl;
		}
	}

	int player1ChooseSquare() {
		int choice = -1;
		std::cout << "X)  Choose a square: ";
		while (choice > 9 || choice < 0 || squareInfo[choice-1] != 0 || isLegalMove(choice) == false) {
			std::cin >> choice;
		}
		return choice;
	}
	int player2ChooseSquare() {
		int choice = -1;
		std::cout << "O)  Choose a square: ";
		while (choice > 9 || choice < 0 || squareInfo[choice-1] != 0 || isLegalMove(choice) == false) {
			std::cin >> choice;
		}
		return choice;
	}

	void player1Move(int move) {
		squareInfo[move-1] = 1;
	}
	void player2Move(int move) {
		squareInfo[move-1] = 2;
	}

	bool isLegalMove(int move) {
		if (squareInfo[move-1] == 0)
			return true;
		else
			return false;
	}
	int checkWinner() {
		for (int i = 0; i < 3; i++) {	// Row cycling
			int counter = 1;
			int checkedSquares[3] = {};
			for (int j = 0; j < 3; j++) {
				checkedSquares[j] = squareInfo[i * 3 + j];	// Currently checked squares' data into an int list
			}
			for (int j = 0; j < 3; j++) {
				if (j != 0) {
					if ((checkedSquares[j-1] == checkedSquares[j]) && checkedSquares[j] != 0) {
						counter++;
					}
				}
				if (counter == 3) {
					return checkedSquares[1];
				}
			}
		}
		for (int i = 0; i < 3; i++) {	// Column cycling
			int counter = 1;
			int checkedSquares[3] = {};
			for (int j = 0; j < 3; j++) {
				checkedSquares[j] = squareInfo[i + 3 * j];	// Currently checked squares' data into an int list
			}
			for (int j = 0; j < 3; j++) {
				if (j != 0) {
					if ((checkedSquares[j-1] == checkedSquares[j]) && checkedSquares[j] != 0) {
						counter++;
					}
				}
				if (counter == 3) {
					return checkedSquares[1];
				}
			}
		}
		for (int i = 0; i < 2; i++) { // Diagonal cycling
			int counter = 1;
			int checkedSquares[3] = {};
			for (int j = 0; j < 3; j++) {
				if (i == 0) {								// Currently checked squares' data into an int list
					checkedSquares[j] = squareInfo[i * 2 + j * 4];
				}
				else {
					checkedSquares[j] = squareInfo[i * 2 + j * 2];
				}
					
			}
			for (int j = 0; j < 3; j++) {
				if (j != 0) {
					if ((checkedSquares[j-1] == checkedSquares[j]) && checkedSquares[j] != 0) {
						counter++;
					}
				}
				if (counter == 3) {
					return checkedSquares[1];
				}
			}
		}
		return false;
	}
};

int main() {
	Board board;
	board.startMessage();
	board.roundControl();
	return 0;
}