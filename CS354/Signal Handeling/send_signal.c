////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        send_signal.c
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
/* 
 * Send signal based on the first argument (-i for SIGINT or -u for SIGUSR1) and the PID.
 * 
 */
void printUsage(){
    printf("Usage: send_signal -u <pid> to send SIGUSR1\n");
    printf("       send_signal -i <pid> to send SIGINT\n");
}

int main(int argc, char *argv[]){
    // Usage Alert
    if (argc != 3){
        printUsage();
        exit(0);
    }

    pid_t pid = atoi(argv[2]);

    // Check if pid valid
    if (getpgid(pid) >= 0){
        // Check the second CLA is valid
        if (strcmp(argv[1], "-u") == 0){
            kill(pid, SIGUSR1);
        } else if (strcmp(argv[1],"-i") == 0){
            kill(pid, SIGINT);
        } else {
            printUsage();
            exit(0);
        }
    } else {
        printUsage();
        exit(0);
    }
}
