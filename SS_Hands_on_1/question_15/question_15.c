/* Program Number: 15
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to display the environmental variables of the user[cite: 18].
*/

#include <stdio.h>

/*
 * CONCEPT: The environ Pointer
 * The operating system passes environment variables to a program via the global 
 * `environ` variable. It is a double pointer (an array of string pointers) where 
 * each string represents a "KEY=VALUE" pair. The array is terminated by a NULL pointer[cite: 18].
 */
extern char **environ;

int main(){
    char **env_ptr = environ;

    printf("--- User Environment Variables ---\n");

    // Loop through the array of string pointers until we hit the NULL terminator[cite: 18]
    while(*env_ptr != NULL){
        printf("%s\n", *env_ptr);
        env_ptr++;
    }

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_15.c -o question_15
shrutis@ubuntu:~/SS_H01$ ./question_15
--- User Environment Variables ---
SHELL=/bin/bash
PWD=/home/shrutis/SS_H01
LOGNAME=shrutis
HOME=/home/shrutis
LANG=en_US.UTF-8
USER=shrutis
... (output truncated for brevity)
*/