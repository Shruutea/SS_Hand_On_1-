/* Program Number: 4
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to open an existing file in read-write mode. Experiment with the O_EXCL flag[cite: 3].
*/

#include <stdio.h>
#include <unistd.h>  // for close()
#include <fcntl.h>   // to open() and for flags like O_RDWR, O_EXCL
#include <errno.h>   // printing error messages

int main() {
    const char *filename = "question_4.txt";

    // Ensure the file exists before testing
    int temp_f = creat(filename, 0644);
    if (temp_f != -1) close(temp_f);
    
    /*
     * CONCEPT: File Opening Modes
     * Normal O_RDWR simply opens an existing file. 
     */
    printf("--- Read/Write - Normal ---\n");
    int fd1 = open(filename, O_RDWR);

    if (fd1 == -1) {
        perror("Error opening file");
    } else {
        printf("Opened %s in r-w mode.\n", filename);
        printf("File descriptor: %d\n", fd1);
        close(fd1);
    }

    /*
     * CONCEPT: O_EXCL Flag
     * When O_EXCL is used alongside O_CREAT, the open() call will STRICTLY fail 
     * if the file already exists. This is useful for preventing accidental overwrites.
     */
    printf("\n--- Using O_EXCL ---\n");
    int fd2 = open(filename, O_RDWR | O_CREAT | O_EXCL, 0644);

    if (fd2 == -1) {
        printf("Failed as expected!\n");
        perror("The error was");
    } else {
        printf("Opened file with O_EXCL, file descriptor: %d\n", fd2);
        close(fd2);
    }
    
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_4.c -o question_4
shrutis@ubuntu:~/SS_H01$ ./question_4
--- Read/Write - Normal ---
Opened question_4.txt in r-w mode.
File descriptor: 3

--- Using O_EXCL ---
Failed as expected!
The error was: File exists
*/