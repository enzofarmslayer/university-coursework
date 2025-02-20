#include "../userprog/syscall.h"
#include <stdio.h>
#include <syscall-nr.h>
#include "../threads/interrupt.h"
#include "../threads/thread.h"
#include "../threads/init.h"
#include "../filesys/filesys.h"
#include "../filesys/file.h"
#include "../devices/input.h"
#include "../lib/user/syscall.h"
#include "../threads/malloc.h"
#include "../userprog/process.h"
#include "../threads/synch.h"
#include "../userprog/pagedir.h"
#include "../threads/vaddr.h"
#include <stdio.h>
#include "syscall-nr.h"
#include "threads/interrupt.h"
#include "threads/thread.h"
#include "threads/init.h"
#include "syscall.h"
#include "filesys/filesys.h"
#include "devices/input.h"
#include "filesys/file.h"

/* Given */
static void syscall_handler (struct intr_frame *);
void halt (void);
bool create (const char*file, unsigned initialsize);
int open (const char*file);
void close(int fd);
int read(int fd, void *buffer, unsigned size);
int write(int fd, const void *buffer, unsigned size);
void exit (int status);
bool validate_fd(int fd);
void close (int fd);

//lab3
pid_t exec (const char *cmd_line);

void
syscall_init (void)
{
  intr_register_int (0x30, 3, INTR_ON, syscall_handler, "syscall");
}

bool
validate_fd(int fd)
{
  if(fd < 0 || fd >= 129) {
    return false;
  }
  else {
    return true;
  }
}


static void
syscall_handler (struct intr_frame *f UNUSED)
{
  int num = *((int*)f->esp);
  switch (num) {
    case SYS_HALT:
    {
      halt();
      break;
    }
    case SYS_CREATE:
    {
      const char *name = *((char**)(f->esp + 4));
      unsigned size = *((unsigned*)(f->esp + 8));
      f->eax = create(name,size);
      break;
    }
    case SYS_OPEN:
    {
      char*name = *((char**)(f->esp + 4));
      f->eax = open(name);
      break;
    }
    case SYS_CLOSE:
    {
      int fd = *((int*)(f->esp + 4));
      close(fd);
      break;
    }
    case SYS_READ:
    {
      int fd = *((int*)(f->esp + 4));
      void *buffer = *((void**)(f->esp + 8));
      unsigned size = *((unsigned*)(f->esp + 12));
      f->eax = read(fd, buffer, size);
      break;
    }
    case SYS_WRITE:
    {
      int fd = *((int*)(f->esp + 4));
      const void *buffer = *(const void**)(f->esp + 8);
      unsigned size = *((unsigned*)(f->esp + 12));
      f->eax = write(fd, buffer, size);
      break;
    }

    case SYS_EXIT:
    {
      int status = *((int*)(f->esp + 4));
      exit(status);
      break;
    }
    case SYS_EXEC:
    {
      const char *cmd_line = *((char**)(f->esp + 4));
      f->eax = exec(cmd_line);
      break;
    }
  }
}

pid_t
exec (const char *cmd_line)
{
  /*
  1. validate input -> return -1 if program cant run
  2. run process execute
   */
  pid_t pidt = process_execute(cmd_line);
  return pidt;
  //return process_execute(cmd_line);

}

void
halt (void)
{
  power_off();
}

bool
create (const char*file, unsigned initial_size)
{
  return filesys_create(file, initial_size);
}

int
open (const char*file)
{
  struct file*f = filesys_open(file);
  struct thread*t = thread_current();

  if (f == NULL) {
    return -1;
  }

  for (size_t fd = 2; fd < 130; fd++) {
    if(t->fd_list[fd] == NULL){
      t->fd_list[fd] = f;
      return fd;
    }
  }
  return -1;
}

void
close (int fd) {
  if((validate_fd(fd) == false)) {
    return -1;
  }

  struct thread *t = thread_current();
  struct file *f = t->fd_list[fd];
  t->fd_list[fd] = NULL;

  file_close(f);
}

int
write (int fd, const void *buffer, unsigned size)
{
  //FIX VALIDATION OF FD, if fd = false or 0 enter if
  if((validate_fd(fd) == false) || fd == 0) {
    return -1;
  }
  if(size < 1) {
    return 0;
  }

  //fd = 1 write to console, 1 = STDOUT_FILEN0
  if(fd == 1) {
    putbuf(buffer, size);
     return size;
   }
   struct thread *t = thread_current();
   struct file *f = t->fd_list[fd];

   if (f == NULL) {
     return -1;
   }

   return file_write(f, buffer, size);
}

int
read (int fd, void *buffer, unsigned size)
{
  //FIX VALIDATION OF FD, if fd = false or 1 enter if
  if((validate_fd(fd) == false) || fd == 1){
    return -1;
  }
  unsigned i;
  //fd = 0 read from keyboard, 0 = STDIN_FILEN0
  if(fd == 0) {
     //read from console into buffer
    for(i = 0; i < size; i++) {
      ((uint8_t*)buffer)[i] = input_getc();
    }
    return size;
   }

   struct thread *t = thread_current();
   struct file *f = t->fd_list[fd];

   if (f == NULL) {
     return -1;
   }

   return file_read(f, buffer, size);
}

void
exit(int status)
{
  thread_exit();
}
