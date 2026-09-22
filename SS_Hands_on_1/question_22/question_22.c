/* Program Number: 22
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to deliberately create a zombie process[cite: 26].
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork(); // Create child

    if(pid < 0) {
        perror("fork failed");
        return 1;
    } else if (pid == 0) {
        /*
         * CONCEPT: Zombie Process Creation
         * A zombie process is created when a child finishes execution (terminates), 
         * but its parent is still running and has not called wait() to collect its 
         * exit status. The OS keeps the child's shell in the process table[cite: 26].
         */
        printf("Child PID: %d - terminating to become a zombie.\n", getpid());
        exit(0);
    } else {
        printf("Parent ID: %d ; created child ID: %d\n", getpid(), pid);
        printf("Parent is now sleeping for 20 sec without calling wait().\n\n");
        printf("Open Terminal 2 and run: ps -o pid,ppid,stat,cmd -p %d\n\n", pid);

        sleep(20);

        printf("Parent woke up and is exiting. OS will now clean up the zombie.\n");
    }

    return 0;
}

/*
Output (Terminal 1):
shrutis@ubuntu:~/SS_H01$ gcc question_22.c -o question_22
shrutis@ubuntu:~/SS_H01$ ./question_22
Parent ID: 3820 ; created child ID: 3821
Parent is now sleeping for 20 sec without calling wait().
Child PID: 3821 - terminating to become a zombie.
Open Terminal 2 and run: ps -o pid,ppid,stat,cmd -p 3821

Output (Terminal 2 during sleep):
shrutis@ubuntu:~/SS_H01$ ps -o pid,ppid,stat,cmd -p 3821
  PID  PPID STAT CMD
 3821  3820 Z+   [question_22] <defunct>
*/