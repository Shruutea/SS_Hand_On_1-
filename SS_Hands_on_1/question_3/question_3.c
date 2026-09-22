/* Program Number: 3
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program that creates a file and prints its file descriptor value using the creat() system call[cite: 3].
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    /*
     * CONCEPT: File Descriptors
     * When a file is opened or created, the OS returns a non-negative integer
     * called a file descriptor. By default, 0, 1, and 2 are reserved for 
     * STDIN, STDOUT, and STDERR respectively. Therefore, the first new file 
     * opened by a process is typically assigned descriptor 3.
     */
    int fd = creat("test_file.txt", 0644); // 0644 gives r/w permission to owner and r to others 
    
    if(fd == -1) {
        perror("Error creating the file");
        return 1;
    }
    
    printf("File created successfully.\n");
    printf("File descriptor value is: %d\n", fd);

    close(fd);
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_3.c -o question_3
shrutis@ubuntu:~/SS_H01$ ./question_3
File created successfully.
File descriptor value is: 3
*/