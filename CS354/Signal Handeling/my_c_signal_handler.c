////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_c_signal_handler.c
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
int AlarmSec = 3;
int Counter = 0;

/* 
 * Handles SIGINT signal by outputting how many SIGUSR1 was recieved and exits.
 */
void handler_SIGINT(){
    printf("\nSIGINT handled.\n");
    printf("SIGUSR1 was received %d times. Exiting now.\n", Counter);
    exit(0);
}

/* 
 * Handless SIGUSR1 signal by outputting a message and incrementing a counter 
 */
void handler_SIGUSR1(){
    printf("Received SIGUSR1, user signal 1 counted.\n");
    Counter++;
}

/* 
 * Handles SIGALRM signal by outputing the PID and current time every 3 seconds.
 */
void handler_SIGALRM(){
    time_t currentTime;
    time(&currentTime);
    printf("PID: %d CURRENT TIME: %s", getpid(), ctime(&currentTime));
    alarm(AlarmSec);
}

int main(){
    alarm(AlarmSec);

    // Register SIGALRM handler
    struct sigaction sa;
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGALRM;
    if (sigaction(SIGALRM, &sa, NULL) != 0){
        printf("Error binding SIGALRM handler.\n");
        exit(1);
    }

    printf("PID and time print every 3 seconds.\n\r");
    printf("Type Ctrl-C to end the program.\n\r");

    //SIGUSR1
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGUSR1;
    if (sigaction(SIGUSR1, &sa, NULL) != 0){
        printf("Error binding SIGUSR1 handler.\n");
        exit(1);
    }

    //SIGINT
    memset(&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &sa, NULL) != 0){
        printf("Error binding SIGINT handler.\n");
        exit(1);
    }
    
    while(1){
    }
}
