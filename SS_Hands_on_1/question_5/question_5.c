/* Program Number: 5
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Create a program that generates five new files in an infinite loop. Execute the program in the background and inspect the file descriptor table at /proc/pid/fd[cite: 3].
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    /*
     * CONCEPT: Process File Tables
     * A process maintains a table of open files. Creating multiple files 
     * assigns them sequential file descriptors. By keeping the process alive 
     * in a loop, we can inspect the virtual `/proc/<PID>/fd` directory 
     * to see exactly which files are open and linked to descriptors 3 through 7.
     */
    creat("test_file1.txt", 0644);
    creat("test_file2.txt", 0644);
    creat("test_file3.txt", 0644);
    creat("test_file4.txt", 0644);
    creat("test_file5.txt", 0644);

    printf("Process ID: %d\n", getpid());
    printf("Five files created, entering infinite loop.\n");

    while(1) {
        // Process stays alive here
    }

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_5.c -o question_5
shrutis@ubuntu:~/SS_H01$ ./question_5 &
[1] 3500
Process ID: 3500
Five files created, entering infinite loop.

shrutis@ubuntu:~/SS_H01$ ls -l /proc/3500/fd
total 0
lrwx------ 1 shrutis shrutis 64 Sep 22 19:40 0 -> /dev/pts/0
lrwx------ 1 shrutis shrutis 64 Sep 22 19:40 1 -> /dev/pts/0
lrwx------ 1 shrutis shrutis 64 Sep 22 19:40 2 -> /dev/pts/0
l-wx------ 1 shrutis shrutis 64 Sep 22 19:40 3 -> /home/shrutis/SS_H01/test_file1.txt
l-wx------ 1 shrutis shrutis 64 Sep 22 19:40 4 -> /home/shrutis/SS_H01/test_file2.txt
l-wx------ 1 shrutis shrutis 64 Sep 22 19:40 5 -> /home/shrutis/SS_H01/test_file3.txt
l-wx------ 1 shrutis shrutis 64 Sep 22 19:40 6 -> /home/shrutis/SS_H01/test_file4.txt
l-wx------ 1 shrutis shrutis 64 Sep 22 19:40 7 -> /home/shrutis/SS_H01/test_file5.txt
shrutis@ubuntu:~/SS_H01$ kill -9 3500
[1]+  Killed                  ./question_5
*/