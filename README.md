# Simple game of life with file reading support

A very simple minimal C dependency game of life.
The grid size is configured at compile time using the 'ROWS' and 'COLS' definitions on the 'main.c' code.

The executable accepts a file path argument where the file contains the alive and dead cell data in the RLE (Run Lenght encoded) file format.

For more information about the file format check 'https://conwaylife.com/wiki/Run_Length_Encoded'.