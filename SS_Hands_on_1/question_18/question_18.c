/* Program Number: 18
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to perform record locking. Implement read and write locks dynamically on specific records[cite: 22].
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

// Define record structure
struct Record {
    int id;
    int value;
};

int main(){
    int fd = open("records_db.dat", O_RDWR | O_CREAT, 0644);
    if (fd == -1){
        perror("error opening the db file");
        return 1;
    }

    // Check if the file is empty and initialize if necessary[cite: 22]
    off_t file_size = lseek(fd, 0, SEEK_END);
    if (file_size == 0){
        struct Record init_records[3] = {{1, 100}, {2, 200}, {3, 300}};
        write(fd, init_records, sizeof(init_records));
        printf("DB initialized with 3 records.\n\n");
    }

    int rec_num, choice;
    printf("--- Record Locking System ---\n");
    printf("Select record to access (1, 2, or 3): ");
    scanf("%d", &rec_num);

    if(rec_num < 1 || rec_num > 3){
        printf("Invalid record number.\n");
        close(fd);
        return 1;
    }

    printf("1. Read record (applies read / shared lock)\n");
    printf("2. Modify record (applies write / exclusive lock)\n");
    printf("Enter choice: ");
    scanf("%d", &choice);

    /*
     * CONCEPT: Record-Level Byte Locking
     * Instead of locking the entire file, we calculate the exact byte offset 
     * of the requested record. `l_start` is set to the record's index multiplied 
     * by the struct size, and `l_len` is restricted to just one struct size. 
     * This allows concurrent access to different records in the same file[cite: 22].
     */
    struct flock lock;
    lock.l_whence = SEEK_SET;
    lock.l_start = (rec_num - 1) * sizeof(struct Record);
    lock.l_len = sizeof(struct Record); 
    lock.l_pid = getpid();

    if(choice == 1){
        lock.l_type = F_RDLCK;
        printf("Waiting to acquire read lock on record %d...\n", rec_num);
        fcntl(fd, F_SETLKW, &lock);
        printf("READ lock acquired.\n");

        struct Record rec;
        lseek(fd, lock.l_start, SEEK_SET);
        read(fd, &rec, sizeof(struct Record));
        printf("Record %d data: Value = %d\n", rec.id, rec.value);
    } else if(choice == 2){
        lock.l_type = F_WRLCK;
        printf("Waiting to acquire write lock on record %d...\n", rec_num);
        fcntl(fd, F_SETLKW, &lock);
        printf("WRITE Lock acquired.\n");

        struct Record rec;
        lseek(fd, lock.l_start, SEEK_SET);
        read(fd, &rec, sizeof(struct Record));
        printf("Current value: %d\n", rec.value);

        rec.value += 50; // Modify data to simulate an update[cite: 22]

        lseek(fd, lock.l_start, SEEK_SET);
        write(fd, &rec, sizeof(struct Record));
        printf("New value successfully written: %d\n", rec.value);
    } else {
        printf("Invalid choice.\n");
        close(fd);
        return 1;
    }

    printf("Press ENTER to release the lock and exit.\n");
    getchar(); // Clear '\n' from scanf[cite: 22]
    getchar(); // Wait for user

    // Release lock
    lock.l_type = F_UNLCK;
    fcntl(fd, F_SETLK, &lock);
    printf("Lock released. Done.\n");

    close(fd);
    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_18.c -o question_18
shrutis@ubuntu:~/SS_H01$ ./question_18
DB initialized with 3 records.

--- Record Locking System ---
Select record to access (1, 2, or 3): 2
1. Read record (applies read / shared lock)
2. Modify record (applies write / exclusive lock)
Enter choice: 2
Waiting to acquire write lock on record 2...
WRITE Lock acquired.
Current value: 200
New value successfully written: 250
Press ENTER to release the lock and exit.

Lock released. Done.
*/