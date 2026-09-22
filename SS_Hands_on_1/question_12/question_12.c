/* Program Number: 12
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to find out the opening mode of a file using fcntl system call[cite: 15].
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    int fd = open(argv[1], O_RDWR | O_CREAT | O_APPEND, 0644);
    if(fd == -1) {
        perror("Error opening file");
        return 1;
    }

    /*
     * CONCEPT: Retrieving File Status Flags
     * fcntl() with F_GETFL retrieves the flags a file was opened with. 
     * Because access modes (O_RDONLY, O_WRONLY, O_RDWR) overlap in their binary representation, 
     * we must apply the O_ACCMODE bitmask to safely extract the specific access mode[cite: 15].
     */
    int flags = fcntl(fd, F_GETFL);
    if(flags == -1) {
        perror("Error getting flags from fcntl");
        close(fd);
        return 1;
    }

    // Apply mask to isolate the access mode bits
    int access_mode = flags & O_ACCMODE;

    printf("--- File Mode Analysis ---\n");

    if (access_mode == O_RDONLY) {
        printf("Read-only mode detected.\n");
    } else if(access_mode == O_WRONLY) {
        printf("Write-only mode detected.\n");
    } else if(access_mode == O_RDWR) {
        printf("Read/Write mode detected.\n");
    } else {
        printf("Unknown access mode.\n");
    }

    if(flags & O_APPEND) {
        printf("Extra flags detected -> Append mode is active.\n");
    }

    close(fd);
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_12.c -o question_12
shrutis@ubuntu:~/SS_H01$ ./question_12 test.txt
--- File Mode Analysis ---
Read/Write mode detected.
Extra flags detected -> Append mode is active.
*/