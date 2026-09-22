/* Program Number: 14
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Write a program to find the type of a file using the lstat system call and S_IS* macros[cite: 17].
*/

#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h> // required for lstat() and S_IS* file type macros

int main(int argc , char *argv[]){
    if(argc != 2){
        perror("file open err");
        return 1;
    }

    struct stat file_stat;

    /*
     * CONCEPT: File Types and lstat()
     * Unlike stat(), lstat() gathers information about a symbolic link itself, 
     * rather than the file it points to. We pass the stat structure to receive the data[cite: 17].
     */
    if(lstat(argv[1], &file_stat) == -1){
        perror("error getting file info");
        return 1;
    }

    printf("File: %s\n", argv[1]);
    printf("Type: ");

    /*
     * CONCEPT: Bitwise File Type Macros
     * The st_mode field contains both permissions and file type information.
     * POSIX provides S_IS* macros that perform bitwise masking to easily 
     * identify the specific file type (e.g., regular, directory, symlink)[cite: 17].
     */
    if(S_ISREG(file_stat.st_mode)){
        printf("Regular file\n");
    } else if(S_ISDIR(file_stat.st_mode)){
        printf("Directory\n");
    } else if(S_ISLNK(file_stat.st_mode)){
        printf("Symbolic link\n");
    } else if(S_ISFIFO(file_stat.st_mode)){
        printf("FIFO / named pipe\n");
    } else if(S_ISSOCK(file_stat.st_mode)){
        printf("Socket\n");
    } else if(S_ISBLK(file_stat.st_mode)){
        printf("Block special device\n");
    } else if(S_ISCHR(file_stat.st_mode)){
        printf("Character special device\n");
    } else {
        printf("Unknown type\n");
    }

    return 0;
}

/*
Output:
shrutis@ubuntu:~/SS_H01$ gcc question14.c -o question14
shrutis@ubuntu:~/SS_H01$ ./question14 question14.c
File: question14.c
Type: Regular file
shrutis@ubuntu:~/SS_H01$ mkdir test_dir
shrutis@ubuntu:~/SS_H01$ ./question14 test_dir
File: test_dir
Type: Directory
*/