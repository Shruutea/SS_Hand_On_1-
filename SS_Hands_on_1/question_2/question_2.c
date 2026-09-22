/* Program Number: 2
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Develop a simple program to execute indefinitely in the background. Traverse the /proc directory and extract relevant process information from the corresponding proc directories[cite: 3].
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    /*
     * CONCEPT: Background Execution & /proc filesystem
     * A process running in an infinite loop will stay alive in memory. 
     * The OS automatically creates a directory inside `/proc` named after 
     * the process ID (PID). This directory contains virtual files that 
     * expose kernel information about the running process (status, memory, etc.).
     */
    printf("--- Background Process Exploration ---\n");
    printf("My Process ID (PID) is: %d\n", getpid());
    printf("I am now running indefinitely. Go check my /proc directory!\n");

    // Infinite loop to keep the process alive
    while(1) {
        // A 1-second sleep prevents this loop from maxing out your VM's CPU
        sleep(1); 
    }

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_2.c -o question_2
shrutis@ubuntu:~/SS_H01$ ./question_2 &
[1] 3456
--- Background Process Exploration ---
My Process ID (PID) is: 3456
I am now running indefinitely. Go check my /proc directory!

shrutis@ubuntu:~/SS_H01$ cat /proc/3456/status | grep State
State:	S (sleeping)
shrutis@ubuntu:~/SS_H01$ cat /proc/3456/cmdline
./question_2
shrutis@ubuntu:~/SS_H01$ kill -9 3456
[1]+  Killed                  ./question_2
*/