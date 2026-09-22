/* Program Number: 24
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to create three child processes and use waitpid() to wait for a specific child[cite: 28].
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    pid_t pids[3];
    int status;

    printf("Parent (PID: %d) is creating 3 child processes...\n\n", getpid());

    for(int i = 0; i < 3; i++) {
        pids[i] = fork();

        if(pids[i] < 0) {
            perror("fork failed");
            return 1;
        } else if(pids[i] == 0) {
            int sleep_time = (i + 1) * 2; // Child 1: 2s, Child 2: 4s, Child 3: 6s
            printf("Child %d (ID %d) started. Sleeping for %d sec.\n", i + 1, getpid(), sleep_time);
            
            sleep(sleep_time);
            
            printf("Child %d (ID %d) done. Slept for %d sec.\n", i + 1, getpid(), sleep_time);
            exit(0);
        }
    }

    /*
     * CONCEPT: Targeted Waiting with waitpid()
     * Unlike wait(), which catches the first child to terminate, waitpid() allows 
     * the parent to block execution until one SPECIFIC process ID finishes.
     * Here, the parent explicitly targets pids[1] (the second child)[cite: 28].
     */
    printf("Parent is bypassing Child 1 and waiting for Child 2 (PID: %d)\n", pids[1]);

    // waitpid(specific_pid, pointer_to_store_exit_status, options: 0 -> default)
    pid_t waited_pid = waitpid(pids[1], &status, 0);

    if(waited_pid == pids[1]) {
        printf("Parent acknowledges Child 2 (PID %d) has finished!\n", waited_pid);
    }

    printf("Parent exits, Child 3 might still be running in background.\n");
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_24.c -o question_24
shrutis@ubuntu:~/SS_H01$ ./question_24
Parent (PID: 3845) is creating 3 child processes...

Child 1 (ID 3846) started. Sleeping for 2 sec.
Child 2 (ID 3847) started. Sleeping for 4 sec.
Child 3 (ID 3848) started. Sleeping for 6 sec.
Parent is bypassing Child 1 and waiting for Child 2 (PID: 3847)
Child 1 (ID 3846) done. Slept for 2 sec.
Child 2 (ID 3847) done. Slept for 4 sec.
Parent acknowledges Child 2 (PID 3847) has finished!
Parent exits, Child 3 might still be running in background.
shrutis@ubuntu:~/SS_H01$ Child 3 (ID 3848) done. Slept for 6 sec.
*/