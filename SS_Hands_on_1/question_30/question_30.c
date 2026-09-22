/* Program Number: 30
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to run a script at a specific time using a Daemon process[cite: 35].
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>

int main(){
    pid_t pid = fork();
    if (pid < 0){
        exit(EXIT_FAILURE);
    }

    if(pid > 0){
        printf("Daemon proc created ; pid: %d\n", pid);
        printf("Parent exiting. Daemon proc runs silently in the background.\n");
        exit(EXIT_SUCCESS); // Parent dies, leaving child orphaned in the background[cite: 35]
    }

    /*
     * CONCEPT: Creating a Daemon
     * 1. setsid(): Creates a new session, fully detaching the process from the controlling terminal.
     * 2. umask(0): Resets file creation masks so the daemon has full permission control.
     * 3. close(): We close standard input, output, and error because a daemon has no terminal to print to[cite: 35].
     */
    setsid();
    umask(0);

    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);

    /*
     * CONCEPT: The Daemon Payload
     * The daemon runs an infinite loop, constantly checking the system time. 
     * Once the target hour and minute match, it executes the payload script via system()[cite: 35].
     */
    while(1){
        time_t now = time(NULL);
        struct tm *tm_info = localtime(&now);

        // Make sure to edit this time to a few minutes ahead of current time before running!
        int target_hour = 14;
        int target_minute = 30;

        if(tm_info->tm_hour == target_hour && tm_info->tm_min == target_minute){
            system("sh /home/shrutis/SS_H01/script.sh");
            
            // Sleep 60 seconds to avoid triggering the script multiple times within the same minute[cite: 35]
            sleep(60);
        }
        
        // Wake up every 10 seconds to check the clock again[cite: 35]
        sleep(10);
    }
    return 0;
}

/*
Output (Terminal execution):
shrutis@ubuntu:~/SS_H01$ echo 'echo "Daemon ran this script!" > /home/shrutis/SS_H01/daemon_out.txt' > script.sh
shrutis@ubuntu:~/SS_H01$ gcc question_30.c -o question_30
shrutis@ubuntu:~/SS_H01$ ./question_30
Daemon proc created ; pid: 4055
Parent exiting. Daemon proc runs silently in the background.
shrutis@ubuntu:~/SS_H01$

Output (Verifying the daemon execution later):
shrutis@ubuntu:~/SS_H01$ cat daemon_out.txt
Daemon ran this script!
shrutis@ubuntu:~/SS_H01$ kill -9 4055
*/