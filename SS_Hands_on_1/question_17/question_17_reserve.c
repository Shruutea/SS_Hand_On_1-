/* Program Number: 17 (Reservation)
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to simulate online ticket reservation. Implement a write lock to avoid race conditions[cite: 20].
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(){
    int fd = open("ticket_db.txt", O_RDWR);
    if(fd == -1){
        perror("error opening the ticket file - run question_17.c first");
        return 1;
    }

    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET; 
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();

    printf("Waiting to acquire ticket DB lock...\n");
    
    /*
     * CONCEPT: Critical Section Protection
     * F_SETLKW blocks this process if another reservation is happening concurrently. 
     * This prevents race conditions where two processes read the same ticket number 
     * at the same time and issue duplicate tickets[cite: 20].
     */
    fcntl(fd, F_SETLKW, &lock);
    printf("Lock acquired! Processing your reservation...\n");

    int ticket_no;
    read(fd, &ticket_no, sizeof(int));

    printf("Current ticket number in the system: %d\n", ticket_no);

    ticket_no++;
    printf("Your newly reserved ticket number is: %d\n", ticket_no);

    /*
     * CONCEPT: Repositioning the Pointer
     * After reading the ticket, the file offset moves forward. We must use lseek() 
     * to reset the pointer to the beginning of the file before writing, otherwise 
     * we will append the new number instead of overwriting the old one[cite: 20].
     */
    lseek(fd, 0, SEEK_SET);
    write(fd, &ticket_no, sizeof(int));

    printf("Press ENTER to complete the transaction and release the lock.\n");
    getchar();

    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Lock released.\n");

    close(fd);
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_17_reserve.c -o question_17_reserve
shrutis@ubuntu:~/SS_H01$ ./question_17_reserve
Waiting to acquire ticket DB lock...
Lock acquired! Processing your reservation...
Current ticket number in the system: 1000
Your newly reserved ticket number is: 1001
Press ENTER to complete the transaction and release the lock.

Lock released.
*/