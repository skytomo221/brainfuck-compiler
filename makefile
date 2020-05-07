CC     := gcc

main: ./src/main.o
	gcc -std=gnu11 -O2 -DONLINE_JUDGE -o ./brainfuck-compiler.out ./src/main.c -lm
