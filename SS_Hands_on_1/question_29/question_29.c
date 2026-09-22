/* Program Number: 29
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to get the scheduling policy and modify it to SCHED_FIFO[cite: 34].
*/

#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>

// helper fn to translate the int policy to readable text[cite: 34]
void print_policy(int policy){
    switch(policy){
        case SCHED_OTHER:
            printf("SCHED_OTHER (std timesharing)\n"); 
            break;
        case SCHED_FIFO:
            printf("SCHED_FIFO\n"); 
            break;
        case SCHED_RR:
            printf("SCHED_RR\n"); 
            break;
        default:
            printf("Unknown Policy (%d)\n", policy);
    }
}

int main(){
    pid_t pid = getpid();
    int current_policy;
    struct sched_param param;

    /*
     * CONCEPT: Reading Scheduling Policies
     * sched_getscheduler() returns an integer representing the current active policy of the process[cite: 34].
     */
    current_policy = sched_getscheduler(pid);
    if (current_policy == -1){
        perror("sched_getscheduler failed");
        return 1;
    }

    printf("--- Scheduled Policy Modification ---\n");
    printf("Original policy: ");
    print_policy(current_policy);

    param.sched_priority = sched_get_priority_max(SCHED_FIFO);

    printf("Attempting to change policy to SCHED_FIFO (priority: %d)\n", param.sched_priority);

    /*
     * CONCEPT: Writing Scheduling Policies
     * Changing a process from a standard policy to a real-time policy like SCHED_FIFO 
     * requires superuser (root) privileges. If run normally, it throws a permission error.
     * When run with sudo, sched_setscheduler() successfully applies the change[cite: 34].
     */
    if(sched_setscheduler(pid, SCHED_FIFO, &param) == -1){
        perror("sched_setscheduler failed");
        printf("-> Hint: Run the program with sudo!\n");
        return 1;
    }

    current_policy = sched_getscheduler(pid);
    printf("New Policy: ");
    print_policy(current_policy);

    return 0;
}

/*
Output (Without sudo):
shrutis@ubuntu:~/SS_H01$ gcc question_29.c -o question_29
shrutis@ubuntu:~/SS_H01$ ./question_29
--- Scheduled Policy Modification ---
Original policy: SCHED_OTHER (std timesharing)
Attempting to change policy to SCHED_FIFO (priority: 99)
sched_setscheduler failed: Operation not permitted
-> Hint: Run the program with sudo!

Output (With sudo):
shrutis@ubuntu:~/SS_H01$ sudo ./question_29
[sudo] password for shrutis: 
--- Scheduled Policy Modification ---
Original policy: SCHED_OTHER (std timesharing)
Attempting to change policy to SCHED_FIFO (priority: 99)
New Policy: SCHED_FIFO
*/