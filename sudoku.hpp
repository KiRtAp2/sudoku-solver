#ifndef SUDOKU_HPP
#define SUDOKU_HPP

#include <string>

class Sudoku {
private:
	int table[9][9];
	bool invalid = false;

	// sth_available[x][y]: whether number y has not yet been taken
	// in row/column/square numbered x
	bool row_available[9][10];
	bool column_available[9][10];
	bool square_available[9][10];

	bool check();
	bool check_filled();
	bool check_square(int square);
	bool check_row(int row);
	bool check_column(int column);

	bool recursive_solve(int row, int column);

	static int next_row(int row, int column);
	static int next_column(int row, int column);

public:
	Sudoku();
	Sudoku(std::string data);

	bool is_valid();
	std::string pformat();
	bool solve();
};

#endif // SUDOKU_HPP
