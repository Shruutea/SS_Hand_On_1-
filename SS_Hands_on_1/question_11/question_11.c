/* Program Number: 11
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to open a file, duplicate the file descriptor using dup, dup2, and fcntl, and verify they share the same file offset[cite: 14].
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    const char *filename = "q11_testfile.txt";
    int fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if(fd == -1) {
        perror("Error opening file");
        return 1;
    }

    /*
     * CONCEPT: Duplicating File Descriptors
     * dup(), dup2(), and fcntl() all create new file descriptors that point to the 
     * EXACT same system file table entry as the original. Because they share the table entry, 
     * they share the same offset pointer. Writing to one automatically advances the offset 
     * for all of them, preventing data overlap[cite: 14].
     */
     
    // dup() automatically assigns the lowest available descriptor
    int fd_dup = dup(fd);

    // dup2() forces the assignment to the specific descriptor (10)
    int fd_dup2 = dup2(fd, 10);

    // fcntl() with F_DUPFD assigns the lowest available fd that is >= 15
    int fd_fcntl = fcntl(fd, F_DUPFD, 15);

    write(fd, "1. Written by original fd\n", 26);
    write(fd_dup, "2. Written by dup() fd\n", 23);
    write(fd_dup2, "3. Written by dup2() fd\n", 24);
    write(fd_fcntl, "4. Written by fcntl() fd\n", 25);

    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);

    printf("Data appended using all 4 file descriptors.\n");
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_11.c -o question_11
shrutis@ubuntu:~/SS_H01$ ./question_11
Data appended using all 4 file descriptors.
shrutis@ubuntu:~/SS_H01$ cat q11_testfile.txt
1. Written by original fd
2. Written by dup() fd
3. Written by dup2() fd
4. Written by fcntl() fd
*/