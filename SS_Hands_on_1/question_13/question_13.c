/* Program Number: 13
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to wait for data to be available on STDIN within 10 seconds using the select system call[cite: 16].
*/

#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>

int main() {
    fd_set readfds;
    struct timeval tv;

    /*
     * CONCEPT: I/O Multiplexing with select()
     * select() blocks the program until a file descriptor becomes ready for an operation.
     * We clear the fd set, add STDIN (0) to it, and configure a timeval struct for 10 seconds.
     * If the user types input, select() returns a positive integer. If 10 seconds pass
     * with no input, select() returns 0 (timeout)[cite: 16].
     */
     
    // FD_ZERO clears the set, FD_SET adds descriptor 0 (STDIN)
    FD_ZERO(&readfds);
    FD_SET(0, &readfds);

    tv.tv_sec = 10;
    tv.tv_usec = 0;

    printf("Waiting for keyboard input for up to 10 seconds...\n");

    // select arguments: max_fd + 1, read_set, write_set, error_set, timeout
    int return_val = select(1, &readfds, NULL, NULL, &tv);

    if (return_val == -1) {
        perror("Error using select");
        return 1;
    } else if(return_val == 0) {
        printf("\nTimeout: No data available within 10 seconds.\n");
    } else {
        printf("\nSuccess: Data is available to be read!\n");
    }

    return 0;
}

/*
Output (Timeout Scenario):
shrutis@ubuntu:~/SS_H01$ gcc question_13.c -o question_13
shrutis@ubuntu:~/SS_H01$ ./question_13
Waiting for keyboard input for up to 10 seconds...
Timeout: No data available within 10 seconds.

Output (Input Provided Scenario):
shrutis@ubuntu:~/SS_H01$ ./question_13
Waiting for keyboard input for up to 10 seconds...
hello
Success: Data is available to be read!
*/