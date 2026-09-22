/* Program Number: 26
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to execute the `ls -Rl` command using execl, execlp, execle, execv, and execvp[cite: 31].
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int choice;

    char *args[] = {"ls", "-Rl", NULL};
    char *custom_env[] = {"MY_CUSTOM_VAR=HelloWorld", NULL};
    
    printf("--- Executing 'ls -Rl' ---\n");
    printf("1. execl  (List, Absolute path)\n");
    printf("2. execlp (List, Auto-PATH search)\n");
    printf("3. execle (List, Absolute path, Custom environment)\n");
    printf("4. execv  (Vector/Array, Absolute path)\n");
    printf("5. execvp (Vector/Array, Auto-PATH search)\n");
    printf("Select the exec variant to test (1-5): ");
    scanf("%d", &choice);

    pid_t pid = fork();

    if(pid < 0) {
        perror("fork failed\n");
        return 1;
    } else if(pid == 0) {
        printf("\nExecuting command...\n\n");
        
        /*
         * CONCEPT: Exec Family Variants
         * 'l' requires listing arguments one by one.
         * 'v' requires passing arguments grouped in an array (vector).
         * 'p' tells the OS to search the system PATH environment variable automatically.
         * 'e' allows passing a custom array of environment variables to the new program[cite: 31].
         */
        switch(choice) {
            case 1:
                execl("/bin/ls", "ls", "-Rl", NULL);
                break;
            case 2:
                execlp("ls", "ls", "-Rl", NULL);
                break;
            case 3:
                execle("/bin/ls", "ls", "-Rl", NULL, custom_env);
                break;
            case 4:
                execv("/bin/ls", args);
                break;
            case 5:
                execvp("ls", args);
                break;
            default:
                printf("Invalid choice.\n");
                exit(1);
        }

        perror("exec failed\n");
        exit(1);

    } else {
        wait(NULL);
        printf("\nChild process completed the exec call.\n");
    }
    
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_26.c -o question_26
shrutis@ubuntu:~/SS_H01$ ./question_26
--- Executing 'ls -Rl' ---
1. execl  (List, Absolute path)
2. execlp (List, Auto-PATH search)
3. execle (List, Absolute path, Custom environment)
4. execv  (Vector/Array, Absolute path)
5. execvp (Vector/Array, Auto-PATH search)
Select the exec variant to test (1-5): 2

Executing command...

.:
total 160
-rwxrwxr-x 1 shrutis shrutis 16120 Sep 22 19:45 question_20
-rw-rw-r-- 1 shrutis shrutis  1420 Sep 22 19:45 question_20.c
... (output truncated for brevity due to recursive list)

Child process completed the exec call.
*/