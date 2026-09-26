# SS_Hand_On_1-
Hand on 1 assignment for Software Systems 

1. Create the following types of files using (i) shell command (ii) system call: a. soft link, b. hard link, c. FIFO.
2. Develop a simple program to execute indefinitely in the background. Traverse the `/proc` directory and extract relevant process information.
3. Write a program that creates a file and prints its file descriptor value using the `creat()` system call.
4. Write a program to open an existing file in read-write mode. Experiment with the `O_EXCL` flag.
5. Create a program that generates five new files in an infinite loop. Execute the program in the background and inspect the file descriptor table at `/proc/pid/fd`.
6. Craft a program to take input from STDIN and display it on STDOUT using only read/write system calls.
7. Write a program to copy the contents of one file to another using read and write system calls.
8. Write a program to open a file in read-only mode, read line by line, and display each line as it is read.
9. Write a program to print file information (inode, hard links, UID, GID, size, blocks, and timestamps) using the `stat` system call.
10. Write a program to open a file in read-write mode, write 10 bytes, move the file pointer by 10 bytes using `lseek`, and write another 10 bytes.
11. Write a program to open a file, duplicate the file descriptor using `dup`, `dup2`, and `fcntl`, and verify they share the same file offset.
12. Write a program to find out the opening mode of a file using `fcntl` system call.
13. Write a program to wait for data to be available on STDIN within 10 seconds using the `select` system call.
14. Write a program to find the type of a file using the `lstat` system call and `S_IS*` macros.
15. Write a program to display the environmental variables of the user.
16. Write a program to perform mandatory locking. Implement both read and write locks.
17. Write a program to simulate online ticket reservation. Implement a write lock to avoid race conditions.
18. Write a program to perform record locking. Implement read and write locks dynamically on specific records.
19. Write a program to initiate a process in different states: running, sleeping, and stopped.
20. Write a program to call `fork` and print the parent and child process IDs.
21. Write a program that opens a file, calls `fork()`, and has both the parent and child write to the file.
22. Write a program to deliberately create a zombie process.
23. Write a program to deliberately create an orphan process.
24. Write a program to create three child processes and use `waitpid()` to wait for a specific child.
25. Write a program to execute an executable program using the `exec` system call.
26. Write a program to execute the `ls -Rl` command using `execl`, `execlp`, `execle`, `execv`, and `execvp`.
27. Write a program to get maximum and minimum real-time priority limits.
28. Write a program to run continuously so its priority can be modified using the nice/renice commands.
29. Write a program to get the scheduling policy and modify it to `SCHED_FIFO`.
30. Write a program to run a script at a specific time using a Daemon process.
