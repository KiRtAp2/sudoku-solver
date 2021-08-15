#include "sudoku.hpp"

#include <string>
#include <string.h>

Sudoku::Sudoku() {
	// set initial table status to empty
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			table[i][j] = 0;
		}
	}
	memset(row_available, true, 90);
	memset(column_available, true, 90);
	memset(square_available, true, 90);
}

Sudoku::Sudoku(std::string data) {
	int i = 0, j = 0;
	for (char ch: data) {
		if (ch < '0' || ch > '9') {
			// illegal character
			invalid = true;
		}
		table[i][j++] = ch - '0';
		if (j == 9) {
			j = 0;
			i++;
		}
	}
	memset(row_available, true, 90);
	memset(column_available, true, 90);
	memset(square_available, true, 90);
	for (i = 0; i < 9; i++) {
		for (j = 0; j < 9; j++) {
			row_available[i][table[i][j]] = false;
			column_available[j][table[i][j]] = false;
			square_available[(i/3)*3 + j/3][table[i][j]] = false;
		}
	}
}

bool Sudoku::is_valid() {
	return !invalid;
}

std::string Sudoku::pformat() {
	// Pretty format, for output purposes
	std::string out;
	for (int i = 0; i < 9; i++) {

		if (i % 3 == 0) {
			out += "+-------+-------+-------+\n";
		}

		for (int j = 0; j < 9; j++) {

			if (j % 3 == 0) {
				if (j != 0) out += ' ';
				out += '|';
			}

			out += ' ';

			if (table[i][j] == 0) {
				out += ' ';
			} else {
				out += '0' + table[i][j];
			}

		}
		out += " |\n";
	}
	out += "+-------+-------+-------+";
	return out;
}

bool Sudoku::check() {
	if (!check_filled()) return false;

	for (int square = 0; square < 9; square++) {
		if (!check_square(square)) return false;
	}

	for (int row = 0; row < 9; row++) {
		if (!check_row(row)) return false;
	}

	for (int column = 0; column < 9; column++) {
		if (!check_column(column)) return false;
	}

	return true;
}

bool Sudoku::check_filled() {
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 9; j++) {
			if (table[i][j] == 0) return false;
		}
	}
	return true;
}

bool Sudoku::check_square(int square) {
	// squares:
	// 0 1 2
	// 3 4 5
	// 6 7 8
	// this function assumes Sudoku::check_filled() returned true
	// it will NOT work correctly if that's not the case

	int istart = (square / 3) * 3;
	int jstart = (square % 3) * 3;

	bool seen[10];
	memset(seen, false, 10);
	for (int i = istart; i < istart+3; i++) {
		for (int j = jstart; j < jstart+3; j++) {
			if (seen[table[i][j]]) return false;
			seen[table[i][j]] = true;
		}
	}
	return true;
}

bool Sudoku::check_row(int row) {
	// this function assumes Sudoku::check_filled() returned true
	// it will NOT work correctly if that's not the case
	bool seen[10];
	memset(seen, false, 10);
	for (int j = 0; j < 9; j++) {
		if (seen[table[row][j]]) return false;
		seen[table[row][j]] = true;
	}
	return true;
}

bool Sudoku::check_column(int column) {
	// this function assumes Sudoku::check_filled() returned true
	// it will NOT work correctly if that's not the case
	bool seen[10];
	memset(seen, false, 10);
	for (int i = 0; i < 9; i++) {
		if (seen[table[i][column]]) return false;
		seen[table[i][column]] = true;
	}
	return true;
}

int Sudoku::next_row(int row, int column) {
	return row + (column+1) / 9;
}

int Sudoku::next_column(int row, int column) {
	return (column+1) % 9;
}

bool Sudoku::solve() {
	// returns true on success, solved sudoku is stored
	return recursive_solve(0, 0) && check();
}

bool Sudoku::recursive_solve(int row, int column) {
	if (row >= 9) return true;
	if (table[row][column] != 0) {
		return recursive_solve(next_row(row, column), next_column(row, column));
	}

	for (int num = 1; num < 10; num++) {
		if (row_available[row][num]
			&& column_available[column][num]
			&& square_available[row/3 * 3 + column/3][num]) {

			table[row][column] = num;
			row_available[row][num] = false;
			column_available[column][num] = false;
			square_available[row/3 * 3 + column/3][num] = false;

			if (recursive_solve(next_row(row, column), next_column(row, column))) {
				return true;
			}

			table[row][column] = 0;
			row_available[row][num] = true;
			column_available[column][num] = true;
			square_available[row/3 * 3 + column/3][num] = true;
		}
	}
	return false;
}
