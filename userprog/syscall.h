#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H
#include <stdbool.h>

void syscall_init(void);
//void sys_sleep(int64_t ticks); JON DEN E SUR HÄR VARFÖR?
bool sys_create(const char* name, unsigned initial_size);
int sys_open (const char *file);
bool sys_remove(const char *file_name);

#endif /* userprog/syscall.h */

