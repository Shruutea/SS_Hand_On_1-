/* Program Number: 25 (Target Executable)
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: A dummy target program to be executed by the exec system call[cite: 30].
*/

#include <stdio.h>

int main(int argc, char *argv[]) {
    printf("Target program running...\n");
    printf("I received %d arguments from the main program:\n", argc);

    for(int i = 0; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }

    return 0;
}