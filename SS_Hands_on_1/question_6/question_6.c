/* Program Number: 6
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Craft a program to take input from STDIN and display it on STDOUT using only read/write system calls.
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    char buffer[128];
    ssize_t bytes_read;

    /*
     * CONCEPT: Low-level I/O System Calls
     * File descriptor 0 corresponds to Standard Input (Keyboard).
     * File descriptor 1 corresponds to Standard Output (Screen/Terminal).
     * The read() function reads data into a buffer, and write() pushes it out.
     * The loop continues until read() returns 0 (EOF triggered by Ctrl+D).
     */
     
    // read(file_descriptor, buffer, max_bytes_to_read); 0 -> STDIN
    while((bytes_read = read(0, buffer, sizeof(buffer))) > 0) {
        // write(file_descriptor, buffer, bytes_to_write); 1 -> STDOUT
        write(1, buffer, bytes_read); 
    }

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_6.c -o question_6
shrutis@ubuntu:~/SS_H01$ ./question_6
Hello System Software!
Hello System Software!
Testing low-level IO.
Testing low-level IO.
(Pressed Ctrl+D to exit)
shrutis@ubuntu:~/SS_H01$
*/
