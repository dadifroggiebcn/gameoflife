# Simple game of life with RLE parsing support

A very simple and minimal C game of life with basic RLE file parsing.
The grid size is configured at compile time using the definitions placed inside 'settings.h'.
This file manages the number of rows and columns avaliable and the starting margins for the program to place cells.
Other values such as .rle files and time between iterations are passed through arguments to the program.

#Usage
For usage run ./glife -h

The executable accepts a file path argument where the file contains the alive and dead cell data in the RLE (Run Lenght encoded) file format.

For more information about the file format check 'https://conwaylife.com/wiki/Run_Length_Encoded'.
