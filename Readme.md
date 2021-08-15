# Sudoku Solver

## Compiling
`cd` into where you pulled the repository and `make build`.

## Usage
Write the (9x9) sudoku you want to solve into a plaintext file, with zeros in place of empty cells (an example is provided in `test.sudoku`). Any non-numerical characters are ignored when reading the file.

Then, run the program with `./sudoku_solver (filename)`. If the program can solve the entered sudoku, it will output it to stdout, nicely formatted.
