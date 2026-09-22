/* Program Number: 16
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to perform mandatory locking. Implement both read and write locks[cite: 19].
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h> // fcntl() and struct flock

int main(int argc, char *argv[]){
    const char *filename = "q16_lockfile.txt";

    int fd = open(filename, O_RDWR | O_CREAT, 0666);
    if(fd == -1){
        perror("err opening the file");
        return 1;
    }

    /*
     * CONCEPT: File Locking Configuration
     * We define a flock structure to specify the lock parameters.
     * l_whence, l_start, and l_len determine the byte range to lock. 
     * Setting l_len to 0 locks the entire file from the starting offset[cite: 19].
     */
    struct flock lock;
    lock.l_whence = SEEK_SET; 
    lock.l_start = 0; 
    lock.l_len = 0; 
    lock.l_pid = getpid();

    int choice;
    printf("Choose lock type (1. Read lock) (2. Write lock): ");
    scanf("%d", &choice);

    if(choice == 1){
        lock.l_type = F_RDLCK; // Shared Read Lock
        printf("Acquiring read lock...\n");
    } else if(choice == 2){
        lock.l_type = F_WRLCK; // Exclusive Write Lock
        printf("Acquiring write lock...\n");
    } else {
        printf("Invalid choice\n");
        close(fd);
        return 1;
    }

    /*
     * CONCEPT: Applying the Lock
     * fcntl() is used with F_SETLKW (Set Lock and Wait). If another process 
     * holds a conflicting lock, this process will block (sleep) until it is released[cite: 19].
     */
    if (fcntl(fd, F_SETLKW, &lock) == -1){
        perror("Error acquiring lock");
        close(fd);
        return 1;
    }

    printf("Lock acquired successfully; PID: %d\n", lock.l_pid);
    printf("Press ENTER to release lock and exit...\n");

    getchar(); // Reads the '\n' leftover from scanf[cite: 19]
    getchar(); // Waits for user to press ENTER[cite: 19]

    /*
     * CONCEPT: Releasing the Lock
     * To release the lock, we change the lock type to F_UNLCK and use F_SETLK[cite: 19].
     */
    lock.l_type = F_UNLCK;
    if(fcntl(fd, F_SETLK, &lock) == -1){
        perror("Error releasing lock\n");
    } else {
        printf("Lock released.\n");
    }

    close(fd);
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_16.c -o question_16
shrutis@ubuntu:~/SS_H01$ ./question_16
Choose lock type (1. Read lock) (2. Write lock): 2
Acquiring write lock...
Lock acquired successfully; PID: 3601
Press ENTER to release lock and exit...

Lock released.
*/