build:
	gcc -o glife ./src/main.c -Wall -Wextra -static -std=c99

run:
	./glife ./examples/switchengine.rle
runex:
	./glife
