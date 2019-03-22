
run: make
	board.exe

make: board.c moveHistory.c minMax.c
	cl board.c moveHistory.c minMax.c
