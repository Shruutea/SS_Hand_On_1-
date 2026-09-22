/* Program Number: 9
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to print file information (inode, hard links, UID, GID, size, blocks, and timestamps) using the stat system call[cite: 12].
*/

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>      // ctime()
#include <sys/stat.h>  // stat() and struct stat

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    struct stat file_stat;

    /*
     * CONCEPT: The stat() System Call
     * The stat() function populates a `stat` structure with metadata about a file
     * without actually opening the file. This allows us to inspect internal OS details
     * like the inode number, ownership IDs, allocated blocks, and modification times[cite: 12].
     */
    if(stat(argv[1], &file_stat) == -1) {
        perror("Error getting file status");
        return 1;
    }

    printf("Info for %s:\n", argv[1]);
    printf("a. Inode: %lu\n", file_stat.st_ino);
    printf("b. Number of hard links: %lu\n", file_stat.st_nlink);
    printf("c. UID (User ID): %u\n", file_stat.st_uid);
    printf("d. GID (Group ID): %u\n", file_stat.st_gid);
    printf("e. Size: %ld bytes\n", file_stat.st_size);
    printf("f. Block size: %ld bytes\n", file_stat.st_blksize);
    printf("g. Number of blocks: %ld\n", file_stat.st_blocks);

    // ctime() converts raw time_t epoch values into readable text strings[cite: 12]
    printf("h. Time of last access: %s", ctime(&file_stat.st_atime));
    printf("i. Time of last modification: %s", ctime(&file_stat.st_mtime));
    printf("j. Time of last change: %s", ctime(&file_stat.st_ctime));

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question_9.c -o question_9
shrutis@ubuntu:~/SS_H01$ ./question_9 question_9.c
Info for question_9.c:
a. Inode: 131584
b. Number of hard links: 1
c. UID (User ID): 1000
d. GID (Group ID): 1000
e. Size: 1420 bytes
f. Block size: 4096 bytes
g. Number of blocks: 8
h. Time of last access: Tue Sep 22 19:40:10 2026
i. Time of last modification: Tue Sep 22 19:35:22 2026
j. Time of last change: Tue Sep 22 19:35:22 2026
*/