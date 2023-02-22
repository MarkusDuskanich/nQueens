#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>

using namespace std;

namespace withoutqobject {


#define boardSize 100000
#define attempts 64


	int validDiagonals = 0;

	int getNum(vector<int>& v)
	{
		int n = v.size();
		int index = rand() % n;
		int num = v[index];
		swap(v[index], v[n - 1]);
		v.pop_back();
		return num;
	}

	void setCursor(int x, int y) {
		HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD Position;
		Position.X = x;
		Position.Y = y;
		SetConsoleCursorPosition(hOut, Position);
	}

	void printQueensOnBoard(vector<int>& queens) {
		for (int i = 0; i < queens.size(); i++) {
			auto queen = queens.at(i);
			setCursor(i * 2, queens.at(i));
			std::cout << "Q";
		}
		setCursor(0, boardSize);
	}

	void printBoardTiles(vector<int>& queens) {
		for (int i = 0; i < queens.size(); i++) {
			for (int j = 0; j < queens.size(); ++j) {
				std::cout << "# ";
			}
			std::cout << std::endl;
		}
	}

	void removeQueenAndUpdateValidDiagonals(int index, vector<int>& diagonals) {
		if (--diagonals[index] == 1)
			validDiagonals++;
	}

	void addQueenAndUpdateValidDiagonals(int index, vector<int>& diagonals) {
		if (++diagonals[index] == 2)
			validDiagonals--;
	}

	int negDiagonalIndexOf(int x, int y) {
		return boardSize - 1 + x - y;
	}

	int posDiagonalIndexOf(int x, int y) {
		return 2 * boardSize - 1 + x + y;
	}

	void addToDiagonal(int x, int y, vector<int>& diagonals) {
		addQueenAndUpdateValidDiagonals(negDiagonalIndexOf(x, y), diagonals);
		addQueenAndUpdateValidDiagonals(posDiagonalIndexOf(x, y), diagonals);
	}

	void removeFromDiagonal(int x, int y, vector<int>& diagonals) {
		removeQueenAndUpdateValidDiagonals(negDiagonalIndexOf(x, y), diagonals);
		removeQueenAndUpdateValidDiagonals(posDiagonalIndexOf(x, y), diagonals);
	}


	void generateRandom(int n, vector<int>& queens, vector<int>& diagonals)
	{
		vector<int> v(n);
		vector<int> res(n);
		for (int i = 0; i < n; i++) {
			v[i] = i;
		}

		int y = 0;
		while (v.size()) {
			queens[y] = getNum(v);
			addToDiagonal(y, queens[y], diagonals);
			y++;
		}
	}



	int conflicts(int x, int y, vector<int>& diagonal) {
		int queenCount = diagonal[negDiagonalIndexOf(x, y)] + diagonal[posDiagonalIndexOf(x, y)] - 2;
		if (queenCount < 0) throw std::runtime_error("diagonal update error");
		else return queenCount;
	}

	void swapQueens(vector<int>& diagonal, vector<int>& queens, int q1, int q2) {
		removeFromDiagonal(q1, queens[q1], diagonal);
		removeFromDiagonal(q2, queens[q2], diagonal);
		auto temp = queens[q1];
		queens[q1] = queens[q2];
		queens[q2] = temp;
		addToDiagonal(q1, queens[q1], diagonal);
		addToDiagonal(q2, queens[q2], diagonal);
	}

	bool solved(vector<int>& diagonals) {
		return validDiagonals == diagonals.size();
	}

	int main2() {
		srand(time(NULL));

		auto tp1 = chrono::steady_clock::now();

		vector<int> queens;
		vector<int> diagonals;
		int currentAttempt = 1;
		long iterations = 0;

		while (currentAttempt++ <= attempts) {
			queens = vector<int>(boardSize);
			diagonals = vector<int>(4 * boardSize - 2);
			validDiagonals = 4 * boardSize - 2;

			generateRandom(boardSize, queens, diagonals);

			for (size_t i = 0; i < boardSize - 1; i++)
			{
				for (size_t j = i + 1; j < boardSize; j++)
				{
					iterations++;

					auto conflictsBeforeSwap = conflicts(i, queens[i], diagonals) + conflicts(j, queens[j], diagonals);
					swapQueens(diagonals, queens, i, j);
					auto conflictsafterSwap = conflicts(i, queens[i], diagonals) + conflicts(j, queens[j], diagonals);
					if (conflictsafterSwap > conflictsBeforeSwap) {
						swapQueens(diagonals, queens, i, j);
					}

					if (conflicts(i, queens[i], diagonals) == 0) {
						break;
					}
				}

				if (solved(diagonals)) {
					goto end;
				}
			}
		}

	end:

		auto tp2 = chrono::steady_clock::now();
		if (boardSize < 24) {
			printBoardTiles(queens);
			printQueensOnBoard(queens);
		}

		if (validDiagonals == diagonals.size()) cout << "Solved on " << currentAttempt << " attempts" << endl;
		else cout << "Could not solve in less than specified attempts" << endl;
		cout << iterations << " iterations" << endl;

		cout << chrono::duration_cast<chrono::microseconds>(tp2 - tp1).count() << " microseconds, or about ";
		cout << chrono::duration_cast<chrono::milliseconds>(tp2 - tp1).count() << " milliseconds" << endl;

		system("Pause");
		return 0;
	}

}