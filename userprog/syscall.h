#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include <stdbool.h>
#include <stdio.h>
#include "threads/thread.h"

void syscall_init(void);
unsigned tell(int fd);
void sleep(int64_t ticks);
void halt(void);
bool create(const char* name, unsigned initial_size);
int open(const char *file);
void close(int fd);
bool remove(const char *file_name);
void seek(int fd, unsigned position);
int filesize(int fd);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
void exit(int status);
tid_t exec(const char *cmd_line);

#endif /* userprog/syscall.h */

