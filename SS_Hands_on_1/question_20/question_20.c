/* Program Number: 20
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to call fork and print the parent and child process IDs[cite: 24].
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Starting the program, about to call fork()\n\n");
    
    /*
     * CONCEPT: Process Creation with fork()
     * The fork() system call creates a new child process by duplicating the calling parent.
     * It returns 0 to the newly created child process, and returns the child's PID 
     * to the parent process. If it fails, it returns a negative value[cite: 24].
     */
    int return_value = fork();

    if (return_value < 0) {
        perror("fork failed");
        return 1;
    } else if (return_value == 0) {
        // This block executes ONLY in the child process
        printf("--- Child Process ---\n");
        printf("Process ID: %d\nParent's ID: %d\n\n", getpid(), getppid());
    } else {
        // This block executes ONLY in the parent process
        printf("--- Parent Process ---\n");
        printf("Process ID: %d\nChild Process ID: %d\n", getpid(), return_value);
        sleep(1); // Sleep ensures the parent doesn't exit before the child prints
    }

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_20.c -o question_20
shrutis@ubuntu:~/SS_H01$ ./question_20
Starting the program, about to call fork()

--- Parent Process ---
Process ID: 3810
Child Process ID: 3811
--- Child Process ---
Process ID: 3811
Parent's ID: 3810
*/