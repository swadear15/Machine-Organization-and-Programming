////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_div0_handler.c
// Other Files:      my_c_signal_handler.c, my_div0_handler.c
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
// Online sources:  N/A
// 
// AI tools:        N/A 
////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////
// Copyright 2019-2025
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission for Spring 2025
////////////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
int Counter = 0;

/* 
 * Handles SIGFPE signal by outputing an error message and total operations completed
 */
void handler_SIGFPE(){
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: %d\n", Counter);
    printf("The program will be terminated.\n");
    exit(0);
}

/* 
 * Handles SIGINT signal by outputting how many operations were completed and exits.
 */
void handler_SIGINT(){
    printf("Total number of operations completed successfully: %d\n", Counter);
    printf("The program will be terminated.\n");
    exit(0);
}

int main(int argc, char *argv[]){
    struct sigaction sa;

    // Registers SIGFPE
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGFPE;
    if (sigaction(SIGFPE, &sa, NULL) != 0){
        printf("Error binding SIGFPE handler.\n");
        exit(1);
    }

    // Registers SIGINT
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &sa, NULL) != 0){
        printf("Error binding SIGINT handler.\n");
        exit(1);
    }

    while(1){
        int buffer_size = 100;
        char buffer[buffer_size];
        int int1;
        int int2;
        int result;
        int remainder;

        printf("Enter first integer: ");
        if ( fgets(buffer, buffer_size, stdin) == NULL ) {      
             fprintf(stderr, "Error reading %i characters of user input.\n", buffer_size);
    }	
        int1 = atoi(buffer);

        printf("Enter second integer: ");
        if ( fgets(buffer, buffer_size, stdin) == NULL ) {      
            fprintf(stderr, "Error reading %i characters of user input.\n", buffer_size);
        }
        int2 = atoi(buffer);

        result = int1 / int2;
        remainder = int1 % int2;

        printf("%d / %d is %d with a remainder of %d\n", int1, int2, result, remainder);

        Counter++;
    } 
}
