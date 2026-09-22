/* Program Number: 19
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to initiate a process in different states: running, sleeping, and stopped[cite: 23].
*/

#include <stdio.h>
#include <unistd.h> 
#include <signal.h> // For raise() and SIGSTOP

int main(){
    pid_t pid = getpid();

    /*
     * CONCEPT: Sleeping State
     * The process voluntarily yields the CPU and waits for a specific time.
     * In the /proc/<PID>/status file, this state is shown as "S (sleeping)"[cite: 23].
     */
    printf("1. Entering SLEEP for 15 seconds...\n");
    printf("   (Check process status in Terminal 2 using 'cat /proc/%d/status')\n", pid);
    sleep(15);

    /*
     * CONCEPT: Stopped State
     * The raise() function sends a signal to the current process. SIGSTOP instructs 
     * the OS scheduler to freeze the process entirely. It will remain in a "T (stopped)" 
     * state until it receives a SIGCONT signal from the terminal[cite: 23].
     */
    printf("\n2. Entering STOPPED state...\n");
    printf("   (The program will freeze here. Check status in Terminal 2.)\n");
    printf("   -> Type 'kill -CONT %d' in Terminal 2 to wake it up.\n", pid);
    raise(SIGSTOP); 

    /*
     * CONCEPT: Running State
     * Once resumed, the process enters an infinite loop. Since it is actively executing 
     * instructions on the CPU, its state is "R (running)"[cite: 23].
     */
    printf("\n3. Entering RUNNING state (infinite loop)...\n");
    printf("   (Check state in Terminal 2; Press Ctrl+C in this terminal to quit.)\n");
    while(1){
        // CPU spins here endlessly
    }

    return 0;
}

/*
Output (Terminal 1):
shrutis@ubuntu:~/SS_H01$ gcc question_19.c -o question_19
shrutis@ubuntu:~/SS_H01$ ./question_19
1. Entering SLEEP for 15 seconds...
   (Check process status in Terminal 2 using 'cat /proc/3712/status')

2. Entering STOPPED state...
   (The program will freeze here. Check status in Terminal 2.)
   -> Type 'kill -CONT 3712' in Terminal 2 to wake it up.

[1]+  Stopped                 ./question_19

(After typing kill -CONT 3712 in Terminal 2)
3. Entering RUNNING state (infinite loop)...
   (Check state in Terminal 2; Press Ctrl+C in this terminal to quit.)
^C
*/