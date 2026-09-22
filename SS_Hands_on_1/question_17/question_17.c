/* Program Number: 17 (Initialization)
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to simulate online ticket reservation. (Database Initialization)[cite: 21].
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>

int main(){
    int fd = open("ticket_db.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if(fd == -1){
        perror("error opening the file\n");
        return 1;
    }

    int starting_ticket = 1000;

    /*
     * CONCEPT: Binary Data Storage
     * Instead of writing text, we write the raw memory bytes of the integer 
     * directly into the file. This makes reading and updating the number later 
     * much more efficient[cite: 21].
     */
    write(fd, &starting_ticket, sizeof(int));

    close(fd);
    printf("Ticket database initialized with starting number: %d\n", starting_ticket);

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_17.c -o question_17_init
shrutis@ubuntu:~/SS_H01$ ./question_17_init
Ticket database initialized with starting number: 1000
*/