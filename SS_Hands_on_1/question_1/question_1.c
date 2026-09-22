/* Program Number: 1
Student Name: Shruti Sijariya; Register Number: MT2026127
Date: 22-09-2026
Description: Create the following types of files using 
(i) shell command 
(ii) system call 
    a. soft link (symlink system call) 
    b. hard link (link system call) 
    c. FIFO (mkfifo Library Function or mknod system call)
*/

#include <stdio.h>//for prinf scanf
#include <unistd.h>//for read,writ,fork
#include <sys/types.h>//defines datatypes
#include <sys/stat.h>//for metadata and permissions ; stat() functions

int main(){

if (symlink("question_1.txt","softlink_c.txt") == 0){
printf("softlink created \n");
} else {
printf("failed to create softlink\n");
}

if(link("question_1.txt","hardlink_c.txt") == 0){
printf("hardlink created sucessfully");
}else {
printf("failed to create hardlink\n");
}

//0666 for r/w permissions
if(mkfifo("myfifo_c",0666) == 0){
printf("fifo created sucessfully");
} else{
printf("failed to create fifo");
}
}

//symlink -> softlink/symbolic link; link->hardilink
// to  run the file -> gcc question_1.c -o question_1 --> ./question_1 -> ls -l to list direc
//gcc - calls gnu;  -o - for output ; gcc A.c -o A maps the output of the c file to a file named A
// add unlink("softlink_c.txt") [same for hardlink and fifo.txt] to remove if the file already exists

/*
Output: SYSTEM CALLS

shrutis@ubuntu:~/SS_H01$ echo "This is the original target file." > question_1.txt
shrutis@ubuntu:~/SS_H01$ gcc question_1.c -o question_1
shrutis@ubuntu:~/SS_H01$ ./question_1
Softlink created successfully.
Hardlink created successfully.
FIFO created successfully.
shrutis@ubuntu:~/SS_H01$ ls -l
total 24
-rw-r--r-- 2 shrutis shrutis    34 Sep 22 19:34 hardlink_c.txt
prw-r--r-- 1 shrutis shrutis     0 Sep 22 19:34 myfifo_c
-rwxrwxr-x 1 shrutis shrutis 16120 Sep 22 19:34 question_1
-rw-r--r-- 1 shrutis shrutis  1632 Sep 22 19:34 question_1.c
-rw-r--r-- 2 shrutis shrutis    34 Sep 22 19:34 question_1.txt
lrwxrwxrwx 1 shrutis shrutis    14 Sep 22 19:34 softlink_c.txt -> question_1.txt
*/

/*
Output: SHELL COMMANDS

shrutis@ubuntu:~/SS_H01$ ln -s question_1.txt softlink_shell.txt
shrutis@ubuntu:~/SS_H01$ ln question_1.txt hardlink_shell.txt
shrutis@ubuntu:~/SS_H01$ mkfifo myfifo_shell
shrutis@ubuntu:~/SS_H01$ ls -l
total 28
-rw-r--r-- 3 shrutis shrutis    34 Sep 22 19:34 hardlink_c.txt
-rw-r--r-- 3 shrutis shrutis    34 Sep 22 19:34 hardlink_shell.txt
prw-r--r-- 1 shrutis shrutis     0 Sep 22 19:34 myfifo_c
prw-rw-r-- 1 shrutis shrutis     0 Sep 22 19:35 myfifo_shell
-rwxrwxr-x 1 shrutis shrutis 16120 Sep 22 19:34 question_1
-rw-r--r-- 1 shrutis shrutis  1632 Sep 22 19:34 question_1.c
-rw-r--r-- 3 shrutis shrutis    34 Sep 22 19:34 question_1.txt
lrwxrwxrwx 1 shrutis shrutis    14 Sep 22 19:34 softlink_c.txt -> question_1.txt
lrwxrwxrwx 1 shrutis shrutis    14 Sep 22 19:35 softlink_shell.txt -> question_1.txt
*/