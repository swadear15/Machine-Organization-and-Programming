////////////////////////////////////////////////////////////////////////////////
// Main File:        my_magic_square.c
// This File:        my_magic_square.c
// Other Files:      N/A
// Semester:         CS 354 Lecture 003 SP25
// Instructor:       Yiyin Shen
// 
// Author:           Arsalan Ahmad
// Email:            ahmad34@wisc.edu
// CS Login:         arsalan
/////////////////////////////// OPTIONAL WORK LOG ///////////////////////////////
// Document your work sessions here or on your copy of https://bit.ly/cs354-work-log
// Keep track of commands, structures, code that you have learned.
// This will help you focus your review on this from each program that are new to you.  
/////////////////////// REQUIRED -- OTHER SOURCES OF HELP ///////////////////////
// Persons:         N/A
//
// Online sources:  https://en.wikipedia.org/wiki/Siamese_method
// 
// AI tools:        N/A
////////////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny & Deb Deppeler
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS 354 Spring 2025, Yiyin Shen
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
        int size;           // dimension of the square
        int **magic_square; // ptr to 2D heap array that stores magic square values
} MagicSquare;

/* TODO:
 * Prompts the user for the magic square's size, read size,
 * check if it's an odd number >= 3
 * (if not valid size, display the required error message and exit)
 *
 * return the valid number
 */
int getSize() {
        // prompt the user as shown in assignment
        int size = 0;
        printf("Enter magic square's size (odd integer >=3)\n");

        // read the user input, save to a local variable, and check for valid size
        if (scanf(" %d", &size) != 1) {
                printf("Error reading user input.\n");
                exit(1);
        }
        if (size % 2 == 0){
                printf("Magic square size must be odd.\n");
                exit(1);
        }
        if (size < 3){
                printf("Magic square size must be >=3.\n");
                exit(1);
        }
        return size;
        
        

        return 0;
}

/* TODO:
 * Create a magic square of size n on the heap.
 *
 * May use the Siamese magic square algorithm or alternate
 * valid algorithm that produces a magic square.
 *
 * n - the number of rows and columns, 3 <= n
 *
 * returns a pointer to the completed MagicSquare struct.
 */
MagicSquare *generateMagicSquare(int n) {
        // Initialize necessary variables
        int current_num = 1;
        int row = 0;
        int col = 0;
        
        // Allocate memory for the MagicSquare struct and 2d array
        MagicSquare *my_magic_square = malloc(sizeof(MagicSquare));
        my_magic_square->size = n;

        int **magic_array = malloc(n * (sizeof(int*)));
        if (magic_array == NULL){
                printf("Failed to allocate memory for magic square:\n\r");
                exit(1);
        }
        for (int i = 0; i < n; i++){ 
                *((magic_array)+i) = malloc(n * sizeof(int));
                if(*((magic_array)+i) == NULL) {
                        printf("failed to created 2d array\n\r");
                        exit(1);
                }
        }
        
        // Initialize the 2d array
        for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                        *(*(magic_array+i)+j) = 0;
                }
        }

        // Start from middle far right
        row = n/2;
        col = n-1;
        int prow = 0;
        int pcol = 0;
        
        while (current_num <= n*n) {
                *(*(magic_array+row)+col) = current_num;
                prow = row;
                pcol = col;
                
                // Move down-right or wrap
                row++;
                col++;
                
                if (row >= n){
                        row = 0;
                }
                if (col >= n){
                        col = 0;
                }
                
                // Move left if position filled
                if (*(*(magic_array+row)+col) != 0) {
                        row = prow;
                        col = pcol - 1;
                        if (col < 0) col = n-1;
                }
                
                current_num++;
        }
        
        my_magic_square->magic_square = magic_array;
        return my_magic_square;
}

/* TODO:
 * Open a new file (overwrites the existing file)
 * and write the magic square values to the file
 * in the format specified by assignment.
 *
 * See assigntment for required file format.
 *
 * magic_square - the magic square to write to a file
 * filename - the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
        // Open the file
        FILE *fp = fopen(filename, "w");
        if (fp == NULL){
                printf("Failed to open the file.\n\r");
        }

        int size = magic_square->size;
        int **square = magic_square->magic_square;
        fprintf(fp, "%i\n", magic_square->size);
        for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                        if (j == size - 1){
                                fprintf(fp, "%i\n", *(*(square+i)+j));
                        }
                        else{
                                fprintf(fp, "%i,", *(*(square+i)+j));
                        }
                }
        }
        fclose(fp);
}


/* TODO:
 * Call other functions to generate a magic square
 * of the user specified size and outputs
 * the created square to the output filename.
 *
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
        // TODO: Check input arguments to get output filename
        if (argc != 2){
                printf("Usage: ./my_magic_square <output_filename>\n");
                exit(1);
        }
        // TODO: Get magic square's size from user
        int size = getSize();
        // TODO: Generate the magic square by correctly interpreting
        //       the algorithm(s) in the write-up or by writing or your own.
        //       You must confirm that your program produces a
        //       Magic Square. See description in the linked Wikipedia page.
        MagicSquare *my_magic_square = generateMagicSquare(size);
        int **magic_array = my_magic_square->magic_square; 

        // TODO: Output the magic square
        char *magic_square_file = *(argv + 1);
        fileOutputMagicSquare(my_magic_square, magic_square_file);

        // Free memory, he did not do anything wrong
        for (int i = (size - 1); i >= 0; i--){
                free(*((magic_array) + i));
        }
        free(magic_array);
        magic_array = NULL;	
        free(my_magic_square);
        my_magic_square = NULL;

        return 0;

}
