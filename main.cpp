#include <iostream>
#include <vector>
#include <windows.h>
#include <chrono>
#include <random>

using namespace std;

//to improve speed go from random y only to random x and y, this randomises the order of the tuples
//and then use a better random number generation, because the max number of rand is very low in this case 32767 (impl defined) which means if you modulo with a
// n greather than mx you will get the same number over and over in getNum() which will result in alot of queens being placed on same diagonal
// if n >>> than max and max is often returned, rand produces for size of 500000 diagonals with conflicts of 32, while mtengine only 9

namespace withoutqobject {

#define boardSize 500000
#define attempts 64

	int highestDiagonalConflict = 0;
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

	int getNum1(vector<int>& v)
	{
		int num = v[v.size() - 1];
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

	long long int getSeed() {
		static int seedOffset = 0;
		long long int seed = std::chrono::high_resolution_clock::now().time_since_epoch().count() + seedOffset++;
		return seed;
	}



	int conflicts(int x, int y, vector<int>& diagonal) {
		int queenCount = diagonal[negDiagonalIndexOf(x, y)] + diagonal[posDiagonalIndexOf(x, y)] - 2;
		if (queenCount < 0) throw std::runtime_error("diagonal update error");
		else return queenCount;
	}

	void generateRandom1(int n, vector<int>& queens, vector<int>& diagonals)
	{
		vector<int> v(n);
		vector<int> v2(n);
		for (int i = 0; i < n; i++) {
			v[i] = i;
			v2[i] = i;
		}
		std::default_random_engine engine(getSeed());
		std::shuffle(v.begin(), v.end(), engine);
		std::shuffle(v2.begin(), v2.end(), engine);

		int y = 0;
		while (v.size()) {
			queens[y] = getNum1(v);
			addToDiagonal(y, queens[y], diagonals);
			if (conflicts(y, queens[y], diagonals) > highestDiagonalConflict)
				highestDiagonalConflict = conflicts(y, queens[y], diagonals);
			y++;
		}
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
			if (conflicts(y, queens[y], diagonals) > highestDiagonalConflict)
				highestDiagonalConflict = conflicts(y, queens[y], diagonals);
			y++;
		}
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
}

int main() {
	using namespace withoutqobject;
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
		cout << highestDiagonalConflict << endl;
		highestDiagonalConflict = 0;


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
