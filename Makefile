
run: make
	board.exe

make: board.c moveHistory.c
	cl board.c moveHistory.c
