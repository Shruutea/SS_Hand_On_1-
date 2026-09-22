/* Program Number: 21
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program that opens a file, calls fork(), and has both the parent and child write to the file[cite: 25].
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/wait.h>

int main() {
    /*
     * CONCEPT: File Descriptor Duplication Across fork()
     * When a file is opened BEFORE fork() is called, the child inherits an exact copy 
     * of the parent's file descriptors. Importantly, they share the SAME file table entry, 
     * meaning they share the exact same file offset pointer. Writing to the file will 
     * append data sequentially without the processes overwriting each other[cite: 25].
     */
    int fd = open("shared_output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if(fd == -1) {
        perror("error opening the file");
        return 1;
    }

    int pid = fork(); // Call fork to create child

    if(pid < 0) {
        perror("fork failed");
        return 1;
    } else if(pid == 0) {
        const char *child_msg = "Child Process\n";
        write(fd, child_msg, strlen(child_msg));
        printf("Child finished writing to the file.\n");
    } else {
        const char *parent_msg = "Parent process\n";
        write(fd, parent_msg, strlen(parent_msg));
        printf("Parent finished writing to the file.\n");
        wait(NULL); // Wait for the child to finish to avoid terminal glitch[cite: 25]
    }

    // Executed by both parent and child processes
    close(fd);

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_21.c -o question_21
shrutis@ubuntu:~/SS_H01$ ./question_21
Parent finished writing to the file.
Child finished writing to the file.
shrutis@ubuntu:~/SS_H01$ cat shared_output.txt
Parent process
Child Process
*/