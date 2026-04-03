build:
	gcc -o glife ./src/main.c -Wall -Wextra -static

run:
	./glife ./examples/switchengine.rle
