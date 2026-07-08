//////////////////////////////////////////////////////////////////////////////
// Author: Arsalan Ahmad
// Date: 2025-02-14
// Course: CS 354 Spring 2025
// CS Login: arsalan
// Email: ahmad34@wisc.edu
///////////////////////////////////////////////////////////////////////////////

// Fix compiler errors and warnings
// Implement remaining functionality


///////////////////////////////////////////////////////////////////////////////
// Copyright 2021-25 Deb Deppeler & Yiyin Shen
// Posting or sharing this file is prohibited, including any changes/additions.
//
// We have provided comments and structure for this program to help you get
// started.  Later programs will not provide the same level of commenting,
// rather you will be expected to add same level of comments to your work.
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *DELIM = ",";  // commas ',' are a common delimiter character for data strings

/* TODO: implement this function
 * Returns 1 if and only if the 2D array of ints in board
 * is in a valid Sudoku board state.  Otherwise returns 0.
 *
 * DOES NOT PRODUCES ANY PRINTED OUTPUT
 *
 * A valid row or column contains only blanks or the digits 1-size,
 * with no duplicate digits, where size is the value 1 to 9.
 *
 * Note: This function requires only that each row and each column are valid.
 *
 * board: heap allocated 2D array of integers
 * size:  number of rows and columns in the board
 */
int valid_sudoku_board(int **board, int size) {
        // If the size is out of range, it is invalid so return 0
        if (size <= 0 || size >= 10) {
                return 0;
        }
        // Check for validugh each elemement in the board
        for (int i = 0; i < size; i++){
                for (int j = 0; j < size; j++){
                        if ((*(board+i)+j) != NULL){
                                if ( *(*(board + i) + j) <= size){
                                        if ( *(*(board + i) + j) != 0) {
                                                // Now check for duplicates in column
                                                for (int last = 0; last < i; last++){
                                                        if (*(*(board + i) + j) == *(*(board + last) + j)){
                                                                //printf("Column error 1\n");
                                                                return 0;
                                                        }
                                                }
                                                // Column check 2
                                                for (int last = i + 1; last < size; last++){
                                                        if (*(*(board + i) + j) == *(*(board + last) + j)){
                                                                //printf("Column error 2\n");
                                                                return 0;
                                                        }
                                                }

                                                // Now we do the same as above but to check for rows
                                                for (int last = j+1; last < size; last++){
                                                        if (*(*(board + i) + j) == *(*(board + i) + last)){
                                                                //printf("Row error 1\n");
                                                                return 0;
                                                        }
                                                }
                                        
                                                for (int last = 0; last < j; last++){
                                                        if (*(*(board + i) + j) == *(*(board + i) + last)){
                                                                //printf("Row error 2\n");
                                                                return 0;
                                                        }
                                                }
                                        }

                                }
                                else{
                                        //printf("Invalid number\n");
                                        return 0;
                                }
                        }
                        else{
                                //printf("Null value\n");
                                return 0;
                        }
                }
        }

        return 1;
}


/* COMPLETED (DO NOT EDIT)
 * Read the first line of file to get the size of that board.
 *
 * PRE-CONDITION #1: file exists
 * PRE-CONDITION #2: first line of file contains valid non-zero integer value
 *
 * fptr: file pointer for the board's input file
 * size: a pointer to an int to store the size
 *
 * POST-CONDITION: the integer whos address is passed in as size (int *)
 * will now have the size (number of rows and cols) of the board being checked.
 */
void get_board_size(FILE *fptr, int *size) {
        char *line = NULL;
        size_t len = 0;

        // 'man getline' to learn about <stdio.h> getline
        if ( getline(&line, &len, fptr) == -1 ) {
                printf("Error reading the input file.\n");
                free(line);
                exit(1);
        }

        char *size_chars = NULL;
        size_chars = strtok(line, DELIM); // 'man strtok' string tokenizer
        *size = atoi(size_chars);         // 'man atoi' alpha to integer
        free(line);                       // free memory allocated for line
}


/* TODO: COMPLETE THE MAIN FUNCTION
 * This program prints "valid" (without quotes) if the input file contains
 * a valid state of a Sudoku puzzle board wrt to rows and columns only.
 * It prints "invalid" (without quotes) if the input file is not valid.
 *
 * Usage: A single CLA that is the name of a file that contains data.
 *
 * argc: the number of command line args (CLAs)
 * argv: the CLA strings, includes the program name
 *
 * Returns 0 if file exists and is readable.
 * Exit with any non-zero result if unable to open and read the file given.
 */
int main( int argc, char **argv ) {

        // TODO: Check if number of command-line arguments is correct.
        if (argc != 2){
                printf("Usage: ./check_sudoku_board <input_filename>\n");
                exit(1);
        }

        // Open the file
        FILE *fp = fopen(*(argv + 1), "r");
        if (fp == NULL) {
                printf("Can't open file for reading.\n");
                exit(1);
        }

        // will store the board's size, number of rows and columns
        int size;

        // TODO: Call get_board_size to read first line of file as the board size.
        get_board_size(fp, &size);

        // TODO: Dynamically allocate a 2D array for given board size.
        int **board = malloc(size * sizeof(int));
        
        // You must dyamically create a array of pointers to other arrays of ints
        if (board == NULL) {
                printf("2D array failed to create\n\r");
                exit(1);
        }
        for (int i = 0; i < size; i++){ 
                *(board+i) = malloc(size * sizeof(int));
                if(*(board+i) == NULL) {
                        printf("2D array failed to create\n\r");
                        exit(1);
                }
        }

        // Read the remaining lines of the board data file.
        // Tokenize each line and store the values in your 2D array.
        char *line = NULL;
        size_t len = 0;
        char *token = NULL;
        for (int i = 0; i < size; i++) {

                // read the line
                if (getline(&line, &len, fp) == -1) {
                        printf("Error while reading line %i of the file.\n", i+2);
                        exit(1);
                }

                token = strtok(line, DELIM);
                for (int j = 0; j < size; j++) {
                        // TODO: Complete the line of code below
                        // to initialize elements of your 2D array.
                        *(*(board+i)+j) = atoi(token);
                        token = strtok(NULL, DELIM);
                }
        }

        // TODO: Call valid_sudoku_board and print the appropriate
        //       output depending on the function's return value.
        if (!valid_sudoku_board(board, size)){
                printf("invalid\n\r");
        } else {
                printf("valid\n\r");
        }
        // TODO: Free dynamically allocated memory.

        for (int i = (size - 1); i >= 0; i--){
                free(*(board + i));
        }

        free(board);
        board = NULL;

        //Close the file.
        if (fclose(fp) != 0) {
                printf("Error while closing the file.\n");
                exit(1);
        }

        return 0;
}
