/* Program Number: 28
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to run continuously so its priority can be modified using the nice/renice commands[cite: 33].
*/

#include <stdio.h>
#include <unistd.h>

int main(){
    /*
     * CONCEPT: Process Niceness
     * The standard scheduling policy (SCHED_OTHER) uses a "nice" value to determine priority.
     * Nice values range from -20 (highest priority) to 19 (lowest priority). 
     * This infinite loop keeps the process alive so we can use external shell commands 
     * like `renice` to alter its priority on the fly[cite: 33].
     */
    printf("PID: %d\n", getpid());
    printf("Running in an infinite loop... open another terminal to check/change priority.\n");

    while(1){
        // do nothing
    }

    return 0;
}

/*
Output (Terminal 1):
shrutis@ubuntu:~/SS_H01$ gcc question_28.c -o question_28
shrutis@ubuntu:~/SS_H01$ ./question_28
PID: 4022
Running in an infinite loop... open another terminal to check/change priority.

Output (Terminal 2):
shrutis@ubuntu:~/SS_H01$ ps -o pid,ni,cmd -p 4022
  PID  NI CMD
 4022   0 ./question_28
shrutis@ubuntu:~/SS_H01$ renice -n 10 -p 4022
4022 (process ID) old priority 0, new priority 10
shrutis@ubuntu:~/SS_H01$ ps -o pid,ni,cmd -p 4022
  PID  NI CMD
 4022  10 ./question_28
*/