#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define COLS 20
#define ROWS 20
#define LEFTMRG 2 
#define TOPMRG 1
int buff[ROWS][COLS] = {0};
int cp_buff[ROWS][COLS] = {0};
char *title;
void cls(void)
{
	printf("\033[2J");
	printf("\033[H");
}

int lf(const char *path)
{
	// Check if directory -- TODO

	char fbuf[10000];
	int fd = open(path, O_RDONLY); // File descriptor
	if (fd == -1) { puts("\nError reading file!"); return -1; }

	int returnval = read(fd, fbuf, sizeof(buff));
	char *data = malloc(returnval);
	memcpy(data, fbuf, (size_t)returnval);

	int ignl = 0; // Ignore line
	int pln = 0;  // Line position
	int xwrt = LEFTMRG; // X Cell to write
	int ywrt = TOPMRG; // Y Cell to write
	
	int ncs_x = 0; // Necesary x colums
	int ncs_y = 0; // Necesary y columns


	
	for (int i = 0; i < returnval; ++i)
	{
		char val = data[i];
		
		if (val == '#') { ignl = 1; --pln; } 
		if (ignl == 0 && val != '\n')
		{
			if (pln == 0) { // TODO Compare map size with required size	
				
				switch (val) {
				case 'x': ncs_x = data[i+4]; break;
				case 'y': ncs_y = data[i+4]; break;
				} 
			} else if (pln >= 1) {
				
				int l;
				
				if (isdigit(data[i-1])) { l = data[i-1] - '0';} else { l = 1; }
				
				for (int g = 0; g < l; ++g)
				{
					switch (val)
					{
						case 'b': puts("b"); buff[xwrt][ywrt]=0; ++xwrt; break;
						case 'o': puts("o");buff[xwrt][ywrt]=1; ++xwrt; break;
						case '$': puts("$"); xwrt = LEFTMRG; ++ywrt; break;
						case '!': puts("!"); i = returnval; break; // End loop
						default: printf("TODO: %c\n", data[i]);
					}
				}
			} else {
				puts("Error parsing file: incorrect line number!"); exit(1);
			}
		}
		if (val == '\n') {ignl = 0; ++pln; } 

	}

	if (ncs_x <= 0 || ncs_y <= 0) { puts("No X or Y could be parsed, please check if the input file is correct!"); exit(1); } 
	printf("X: %c, Y: %c\n", ncs_x, ncs_y); 
	free(data);
	return 1;
}	

void display(void)
{
	for (int y = 0; y < COLS; ++y)
	{
		for (int x = 0; x < ROWS; ++x)
		{
			int curr_pnt = buff[x][y];
			if (curr_pnt == 0)
			{
				printf(".");
			} else {
				printf("#");
			}	
		}
		printf("\n");	
	}
}

int count(int arr[ROWS][COLS], int x, int y) // fy/fx -> finalx/y 
{
	int cells = 0;
	for (int dx = -1; dx <= 1; ++dx)
	{
		for (int dy = -1; dy <= 1; ++dy)
		{
			if (dy != 0 || dx != 0)
			{
				int fx = x + dx, fy = y + dy;

				if ( (fy >= 0 && fy <= COLS) && (fx >= 0 && fx <= ROWS) && (arr[fx][fy]) )
				{
					++cells;
				}
			}
		}
	}
	
	return cells;	
} 

void usage(void)
{
	puts("Incorrect argument count!\nUsage:\n./glife 'path'");
}

int main(int argc, char **argv)
{
	switch (argc) {
		case 1:
			puts("Using default map");
			sleep(1);	
			// Staring map
	
			buff[1][5] = 1;	// Blinker
			buff[2][5] = 1;
			buff[3][5] = 1;
			break;
		case 2:
			lf(argv[1]);
			display();
			break;
		default:
			usage();
			return 1;
			break;
	}	
	for (;;)
	{
		sleep(1);
		cls();	
		display();	
		memcpy(cp_buff, buff, sizeof(buff));
		
		for (int nx = 0; nx < ROWS; ++nx)
		{
		       for (int ny = 0; ny < COLS; ++ny)
		       {
			       int neighbors = count(cp_buff, nx, ny);
			       if (cp_buff[nx][ny]) // If cell alive -> 2 or more nightbours 
			       {
				       buff[nx][ny] = (neighbors == 2 || neighbors == 3) ? 1 : 0;
			       } else { // Give it some life
				       buff[nx][ny] = (neighbors == 3) ? 1 : 0;
			       }
		       }
		}	
	}
	return 0;
}
