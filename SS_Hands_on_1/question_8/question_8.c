/* Program Number: 8
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to open a file in read-only mode, read line by line, and display each line as it is read[cite: 11].
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDONLY);
    if(fd == -1) {
        printf("Error opening the file\n");
        return 1;
    }

    /*
     * CONCEPT: Character-by-Character Reading
     * Since low-level read() doesn't understand "lines", we read 1 byte at a time.
     * We append each character to a buffer. When we encounter a newline character ('\n'),
     * we flush the buffer to STDOUT (file descriptor 1) and reset the index[cite: 11].
     */
    char c;
    char line_buffer[1024];
    int idx = 0;

    // Read one char at a time
    while(read(fd, &c, 1) > 0) {
        line_buffer[idx++] = c;

        // Write to terminal when the line ends
        if(c == '\n') {
            write(1, line_buffer, idx);
            idx = 0;
        }
    }

    // If the file doesn't end with an explicit \n, print the remaining buffer
    if(idx > 0) {
        write(1, line_buffer, idx);
        write(1, "\n", 1);
    }

    close(fd);
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ echo -e "Line 1\nLine 2\nLine 3" > test.txt
shrutis@ubuntu:~/SS_H01$ gcc question_8.c -o question_8
shrutis@ubuntu:~/SS_H01$ ./question_8 test.txt
Line 1
Line 2
Line 3
*/