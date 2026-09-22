/* Program Number: 7
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to copy the contents of one file to another using read and write system calls[cite: 10].
*/

#include <stdio.h>
#include <fcntl.h>   // open(), O_RDONLY, O_WRONLY, O_CREAT, O_TRUNC
#include <unistd.h>  // read(), write(), close()

#define BUFFER_SIZE 1024

// argc counts arguments from CLI (1 = program name, 2 & 3 = file names)
// argv is the array of string pointers to those arguments
int main(int argc, char *argv[]) {
    /*
     * CONCEPT: File Copying via Buffer
     * We open the source file in Read-Only mode and the destination file in 
     * Write-Only mode (creating it if it doesn't exist, and truncating it if it does).
     * Data is read into a buffer in chunks of BUFFER_SIZE, then written 
     * from the buffer to the destination until read() returns 0 (EOF)[cite: 10].
     */
     
    if (argc != 3) {
        printf("Usage: %s <source_file> <destination_file>\n", argv[0]);
        return 1;
    }

    int fd_src = open(argv[1], O_RDONLY);
    if(fd_src == -1) {
        printf("Error opening the source file\n");
        return 1;
    }

    // 0644 sets standard read/write permissions for the newly created file
    int fd_dest = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd_dest == -1) {
        printf("Error opening/creating destination file\n");
        close(fd_src);
        return 1;
    }

    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, bytes_written;

    // Loop until there is nothing left to read
    while((bytes_read = read(fd_src, buffer, BUFFER_SIZE)) > 0) {
        bytes_written = write(fd_dest, buffer, bytes_read);

        if(bytes_read != bytes_written) {
            printf("Error copying file data\n");
            close(fd_src);
            close(fd_dest);
            return 1;
        }
    }

    close(fd_src);
    close(fd_dest);

    printf("Successfully copied %s to %s\n", argv[1], argv[2]);
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ echo "Hello System Software!" > src.txt
shrutis@ubuntu:~/SS_H01$ gcc question_7.c -o question_7
shrutis@ubuntu:~/SS_H01$ ./question_7 src.txt dest.txt
Successfully copied src.txt to dest.txt
shrutis@ubuntu:~/SS_H01$ cat dest.txt
Hello System Software!
*/