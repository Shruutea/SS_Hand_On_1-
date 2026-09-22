/* Program Number: 10
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to open a file in read-write mode, write 10 bytes, move the file pointer by 10 bytes using lseek, and write another 10 bytes[cite: 13].
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *filename = "q10_testfile.txt";

    int fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1) {
        perror("Error opening the file");
        return 1;
    }

    /*
     * CONCEPT: File Offsets and Sparse Files
     * Every open file has a current offset pointer. Writing 10 bytes advances it by 10.
     * By using lseek() with SEEK_CUR, we jump the pointer an additional 10 bytes forward
     * without writing anything. The OS fills this gap with null bytes ('\0'), creating a file hole[cite: 13].
     */
    char first_10_bytes[] = "1234567890";
    write(fd, first_10_bytes, 10);

    // SEEK_CUR moves the pointer relative to its current position by an offset of 10
    off_t seek_return = lseek(fd, 10, SEEK_CUR);

    if (seek_return == -1) {
        perror("Error using lseek");
        close(fd);
        return 1;
    }

    printf("lseek successful! The return value (current offset) is: %ld\n", (long)seek_return);

    char second_10_bytes[] = "ABCDEFGHIJ";
    write(fd, second_10_bytes, 10);

    close(fd);
    printf("File created and modified successfully.\n");

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_10.c -o question_10
shrutis@ubuntu:~/SS_H01$ ./question_10
lseek successful! The return value (current offset) is: 20
File created and modified successfully.
shrutis@ubuntu:~/SS_H01$ cat q10_testfile.txt
1234567890ABCDEFGHIJ
*/