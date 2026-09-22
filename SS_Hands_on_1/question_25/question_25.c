/* Program Number: 25 (Main Program)
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to execute an executable program using the execl system call[cite: 29].
*/

#include <stdio.h>
#include <unistd.h>

int main() {
    printf("--- Main Program Q25 ---\n");
    printf("Replacing current process with target executable...\n\n");

    /*
     * CONCEPT: The exec() System Call Family
     * Unlike fork(), exec() does not create a new process. It completely takes over 
     * the current process memory space and replaces it with a brand new executable program.
     * Arguments for execl(): Path to executable, Argument 0 (program name convention), 
     * followed by any extra inputs, explicitly terminated with NULL[cite: 29].
     */
    execl("./target", "target", "Hello", "OS_Class", "Shruti", NULL);

    // If execl() is successful, it completely overwrites this process.
    // Anything below this line will ONLY run if execl() fails!
    perror("exec failed! Compile target.c first.\n");

    return 1;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc target.c -o target
shrutis@ubuntu:~/SS_H01$ gcc question_25.c -o question_25
shrutis@ubuntu:~/SS_H01$ ./question_25
--- Main Program Q25 ---
Replacing current process with target executable...

Target program running...
I received 4 arguments from the main program:
Argument 0: target
Argument 1: Hello
Argument 2: OS_Class
Argument 3: Shruti
*/