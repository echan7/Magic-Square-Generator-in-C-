////////////////////////////////////////////////////////////////////////////////
// Main File:        verify_magic.c
// This File:        verify_magic.c
// Other Files:      generate_magic.c
// Semester:         CS 354 Fall 2016
//
// Author:           Eric Chan
// Email:            echan7@wisc.edu
// CS Login:         echan
//
////////////////////////////// 80 columns wide /////////////////////////////////

/*This class file is used to check whether the magic square text file that 
  passes through is indeed a magic square or not. It sums up the first row
  of the magic square and compared to every other sum of a row, column and 
  diagonals.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure representing Square
// size: dimension(number of rows/columns) of the square
// array: 2D array of integers
typedef struct _Square {
	int size;
	int **array;
} Square;

Square * construct_square(char *filename);
int verify_magic(Square * square);

int main(int argc, char *argv[])
{
	// Check input arguments to get filename
 	if(argc!=2){
		printf("Usage: ./verify_magic <filename>\n");
		exit(1);
	}else{
	// Construct square
		Square *newSquare = construct_square(argv[1]);

	// Verify if it's a magic square and print true or false
		int flag = verify_magic(newSquare);
		if(flag == 1){
			printf("true\n");
		}else{
			printf("false\n");
		}
	//free dynamically allocated array in reverse to avoid 
	//memory leaks,from the 2D array in the struct all the
	//the way up to the pointer to the struct
	for(int i = 0; i < newSquare->size; i++){
		free(*(newSquare->array+i));
	}
	free(newSquare->array);
	free(newSquare);
	}	
	return 0;
}

// construct_square reads the input file to initialize a square struct
// from the contents of the file and returns the square.
// The format of the file is defined in the assignment specifications
Square * construct_square(char *filename)
{

	// Open and read the file
	FILE * pFile = fopen (filename , "r");
	if(pFile == NULL){
		printf("Cannot open file for reading.\n");
		exit(1);
	}	
    // Read the first line to get the square size
	char str[60];
	fgets(str, 60, pFile);
 	// Initialize a new Square struct of that size
    	Square *cSquare=malloc(sizeof(Square));
	int num = atoi(str);
	cSquare->size = num;
	cSquare->array = malloc(sizeof(int*) * num);
	for(int i = 0 ; i < num; i++){
		*(cSquare->array+i) = malloc(sizeof(int*) * num);
	}
 	// Read the rest of the file to fill up the square
	for(int j = 0; j< num ; j++){
		for(int k = 0; k<num; k++){
			//rather than using strtok(), specifies the 
			//format specifier to delimeter the comma 
			fscanf(pFile, "%d,", (*(cSquare->array+j)+k));
		}
	} 
	fclose(pFile);
	return cSquare;
}

// verify_magic verifies if the square is a magic square
// returns 1(true) or 0(false)
int verify_magic(Square * square)
{
	int sum, sum1, sum2;
	int i,j = 0;
	int flag = 0 ;
	
	//sum of first row of the array
	sum = 0;
	for(i=0;i<1;i++){
		for(j = 0; j < square->size ; j++){
			sum = sum + *(*(square->array +i)+j);
		}
	}
	
	// Check all rows sum to same number
	for(i=0; i < square->size ; i++){
		sum1 = 0;
		for(j=0; j < square->size; j++){
			sum1 = sum1 + *(*(square->array +i)+j);
		}
		if(sum == sum1){
			flag = 1;
		}else{
			return flag = 0;
		}
	}	
	// Check all cols sum to same number
	for(i=0; i < square->size; i++){
		sum2=0;
		for(j = 0; j < square->size; j++){
			sum2 = sum2 + *(*(square->array +j)+i);
		}
		if(sum == sum2){
			flag = 1;
		}else{
			return flag = 0;
		}
	}
	// Check main diagonal
	sum1=0;
	for(i=0; i < square->size; i++){
		for(j=0; j < square->size; j++){
			if(i==j){
				sum1 = sum1 + *(*(square->array+i)+j);
			}
		}
	}
	if(sum == sum1){
		flag = 1;
	}else{
		return flag = 0;
	}
	// Check secondary diagonal
	sum2=0;
	for(i=0; i < square->size; i++){
		for(j=0; j < square->size; j++){
			if((i+j) == (square->size -1)){
				sum2 = sum2 + *(*(square->array+i)+j);
			}
		}
	}
	if(sum == sum2){
		flag = 1;
	}else{
		return flag = 0;
	}
	return flag;
}
