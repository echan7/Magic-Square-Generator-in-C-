////////////////////////////////////////////////////////////////////////////////
// Main File:        generate_magic.c
// This File:        generate_magic.c
// Other Files:      verify_magic.c
// Semester:         CS 354 Fall 2016
//
// Author:           Eric Chan
// Email:            echan7@wisc.edu
// CS Login:         echan
//
//////////////////////////// 80 columns wide ///////////////////////////////////

/* This class generate a magic square based on the siamese method,
   the size of the square generated is determine by the user, an
   algorithm will execute the user wishes to make the square.
 */

#include <stdio.h>
#include <stdlib.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
	int size;
	int **array;
} Square;

int get_square_size();
Square * generate_magic(int size);
void write_to_file(Square * square, char *filename);

int main(int argc, char *argv[])
{
	// Check input arguments to get filename
	if(argc!=2){
		printf("Usage: ./generate_magic <filename>\n");
		exit(1);
	}
	// Get size from user
	int userInput = get_square_size();
	// Generate the magic square
	Square *magicSquare = generate_magic(userInput);
	// Write the square to the output file
	write_to_file(magicSquare, argv[1]);
	//remember to free every dynamically allocated data 
	//in reverse of how it is created to avoid 
	//memory leaks, from the 2d array to the pointer 
	//to the struct
	for(int i = 0; i < magicSquare->size; i++){
		free(*(magicSquare->array+i));
	}
	free(magicSquare->array);
	free(magicSquare);
	return 0;
}

// get_square_size prompts the user for the magic square size
// checks if it is an odd number >= 3 and returns the number
int get_square_size()
{
	int sizeInput = 0;
	printf("Enter size of magic square, must be odd\n");
	scanf("%d", &sizeInput);
	if((sizeInput < 3) | (sizeInput%2 == 0)){
		printf("Size must be an odd number >=3\n");
		exit(1);
	}
	return sizeInput;
}

// generate_magic constructs a magic square of size n
// using the Siamese algorithm and returns the Square struct
Square * generate_magic(int n)
{
	int start = n/2;
	int max = n*n;
	int nextRow;
	int nextCol;
	Square *cSquare = malloc(sizeof(Square));
	cSquare-> size = n;
	cSquare-> array = malloc(sizeof(int*)*n);
	for(int i =0; i < n; i++){
	 	*(cSquare->array + i)= malloc(sizeof(int*) *n);
	}
	*(*(cSquare->array)+start) = 1;
	
	int row = 0;
	int col = start;
	for(int j = 2 ; j < max+1 ; j++){
		if((row - 1) < 0){
			nextRow = n-1;
		}else{
			nextRow = row -1;
		}
		if((col+1)>(n-1)){
			nextCol =0;
		}else{
			nextCol = col +1;
		}
		if(*(*(cSquare->array + nextRow)+nextCol) > 0){
			if(row > (n-1)){
				nextRow =0;
			}else{
				nextRow = row + 1;
				nextCol = col;
			}
		}
		row = nextRow;
		col = nextCol;
		*(*(cSquare->array + row)+col) = j;
	}
	return cSquare;
}

// write_to_file opens up a new file(or overwrites the existing file)
// and writes out the square in the format expected by verify_magic.c
void write_to_file(Square * square, char *filename)
{
	FILE *newFile = fopen(filename, "w+");
	fprintf(newFile, "%d\n",square->size); 
	for(int i =0; i < (square->size);i++){
		for(int j=0; j< (square->size);j++){
			//check whether if the sentence is at the end
			//if it is, don't have to put comma and move
			//to the next line
			if((j == (square->size -1))){	
				fprintf(newFile, "%d", *(*(square->array+i)+j));
			}else{
				fprintf(newFile, "%d,", *(*(square->array+i)+j));
			}
		}
		fprintf(newFile, "\n");
	}
	fclose(newFile); 
}	
