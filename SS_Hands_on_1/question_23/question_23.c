/* Program Number: 23
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to deliberately create an orphan process[cite: 27].
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    pid_t pid = fork();

    if(pid < 0) {
        perror("fork failed");
        return 1;
    } else if(pid > 0) {
        printf("Parent: %d created child: %d\n", getpid(), pid);
        printf("Parent terminates immediately, leaving the child an orphan.\n");
        exit(0);
    } else {
        /*
         * CONCEPT: Orphan Process Creation
         * An orphan process is a child whose original parent has already died. 
         * The OS automatically adopts it and reassigns its parent ID (PPID), 
         * typically to the init process (PID 1) or a systemd subreaper[cite: 27].
         */
        printf("Child: %d is alive, original parent is %d\n", getpid(), getppid());
        printf("Child sleeps for 5 sec to wait for parent to die...\n");

        sleep(5);

        printf("\nChild woke up!\n");
        printf("Adoptive parent PPID is %d\n", getppid());
    }
    
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_23.c -o question_23
shrutis@ubuntu:~/SS_H01$ ./question_23
Parent: 3835 created child: 3836
Parent terminates immediately, leaving the child an orphan.
Child: 3836 is alive, original parent is 3835
Child sleeps for 5 sec to wait for parent to die...
shrutis@ubuntu:~/SS_H01$ 
Child woke up!
Adoptive parent PPID is 1
*/