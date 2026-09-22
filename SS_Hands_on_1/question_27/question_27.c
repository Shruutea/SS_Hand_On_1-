/* Program Number: 27
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to get maximum and minimum real-time priority limits[cite: 32].
*/

#include <stdio.h>
#include <sched.h>

int main(){
    int max_fifo, min_fifo;
    int max_rr, min_rr;

    /*
     * CONCEPT: Real-Time Scheduling Priorities
     * Linux provides real-time scheduling policies like SCHED_FIFO (First In, First Out) 
     * and SCHED_RR (Round Robin). The sched_get_priority_max() and sched_get_priority_min() 
     * system calls retrieve the valid priority ranges for these policies (usually 1 to 99)[cite: 32].
     */
    max_fifo = sched_get_priority_max(SCHED_FIFO);
    min_fifo = sched_get_priority_min(SCHED_FIFO);

    max_rr = sched_get_priority_max(SCHED_RR);
    min_rr = sched_get_priority_min(SCHED_RR);

    printf("--- Real Time Priority Limits ---\n\n");

    printf("SCHED_FIFO:\n");
    printf("  Max priority: %d\n", max_fifo);
    printf("  Min Priority: %d\n", min_fifo);

    printf("SCHED_RR:\n");
    printf("  Max Priority: %d\n", max_rr);
    printf("  Min Priority: %d\n", min_rr);

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_27.c -o question_27
shrutis@ubuntu:~/SS_H01$ ./question_27
--- Real Time Priority Limits ---

SCHED_FIFO:
  Max priority: 99
  Min Priority: 1
SCHED_RR:
  Max Priority: 99
  Min Priority: 1
*/