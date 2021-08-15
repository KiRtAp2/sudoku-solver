#include "sudoku.hpp"

#include <iostream>
#include <fstream>
#include <time.h>


std::pair<std::string, bool> read_data(char* filename) {
	// Read sudoku from file.
	// Returns a pair<string, bool> where pair.first is the 81-character description,
	// and pair.second is a status code -- false if something went wrong

	std::ifstream ifs(filename, std::ifstream::in);

	std::string data;
	char next;

	while (ifs >> next) {
		if (next < '0' || next > '9') {
			continue;
		}
		data += next;
		if (data.length() == 81) {
			break;
		}
	}

	ifs.close();
	return {data, data.length() == 81};
}


int main(int argc, char* argv[]) {
	if (argc < 2) {
		std::cout << "Please provide a filename." << std::endl;
		return 1;
	}

	std::pair<std::string, bool> data_status = read_data(argv[1]);
	if (!data_status.second) {
		std::cout << "Error when reading file." << std::endl;
		return 2;
	}

	Sudoku s(data_status.first);
	if (!s.is_valid()) {
		std::cout << "Error when reading file." << std::endl;
		return 3;
	}

	std::cout << "Initial sudoku:" << std::endl;
	std::cout << s.pformat() << std::endl;

	bool success = s.solve();

	if (!success) {
		std::cout << "Could not solve sudoku." << std::endl;
		return 4;
	}

	std::cout << "Solved sudoku:" << std::endl;
	std::cout << s.pformat() << std::endl;

	return 0;
}
