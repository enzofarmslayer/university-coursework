#include "userprog/syscall.h"

#include "threads/interrupt.h"
#include "threads/thread.h"

#include <stdio.h>
#include <syscall-nr.h>

#include "devices/input.h" //osäker om behövs
#include <string.h>

#include "devices/timer.h"      // for timer_sleep
#include "threads/init.h"       // for shutdown_power_off
#include "filesys/filesys.h"    // for filesys_create and filesys_open

//Our own syshandlers
static void syscall_handler(struct intr_frame*);
unsigned sys_tell(int fd);
void sys_sleep(int64_t ticks);
void sys_halt(void);
bool sys_create(const char* name, unsigned initial_size);
int sys_open(const char *file);
void sys_close(int fd);
bool sys_remove(const char *file_name);
void sys_seek(int fd, unsigned position);
int sys_filesize(int fd);
int sys_read(int fd, void *buffer, unsigned size);
int sys_write(int fd, const void *buffer, unsigned size);
void sys_exit(int status);

//Already implemented
void shutdown_power_off(void);
void file_close(struct file *);
void file_seek(struct file *, unsigned position);
unsigned file_tell(struct file *);
int file_length(struct file *);
int file_read(struct file *, void *buffer, unsigned size);
int file_write(struct file *, const void *buffer, unsigned size);

void syscall_init(void)
{
	intr_register_int(0x30, 3, INTR_ON, syscall_handler, "syscall");
}

static void syscall_handler(struct intr_frame* f UNUSED)
{
	int fd;
	void *buffer;
	unsigned size;
	switch(*(int*)(f->esp))
	{
	
	case SYS_SLEEP:{
		int64_t sleep_duration = *((int*)(f->esp) + 1);
		sys_sleep(sleep_duration);
		break;
	}

	case SYS_HALT:{
		sys_halt();
		break;
	}


	case SYS_CREATE:{
		const char* name = (char*)(*((int*)(f->esp) + 1));
		unsigned initial_size = *((int*)(f->esp) + 2);
		f->eax = sys_create(name, initial_size);
		break;
	}

	case SYS_OPEN:{
		const char* file = (char*)(*((int*)(f->esp) + 1));
		f->eax = sys_open (file);
		break;
	}
	
	case SYS_CLOSE:{
		fd = *((int*)(f->esp) + 1);
		sys_close(fd);
		break;
	}

	case SYS_REMOVE:{
		const char* filename = (char*)(*((int*)(f->esp) + 1));
        f->eax = sys_remove(filename);
        break;
	}

	case SYS_SEEK: {
		fd = *((int*)(f->esp) + 1);
		unsigned position = *((int*)(f->esp) + 2);
		sys_seek(fd, position);
		break;
	}

	case SYS_TELL:{
		fd = *((int*)(f->esp) + 1);
		f->eax = sys_tell(fd);
		break;
	}

	case SYS_FILESIZE:{
		fd = *((int*)(f->esp) + 1);
		f->eax = sys_filesize(fd);
		break;
	}
	
	case SYS_READ:{
		fd = *((int*)(f->esp) + 1);
		buffer = *((void**)(f->esp) + 2);
		size = *((unsigned*)(f->esp) + 3);
		f->eax = sys_read(fd, buffer, size);
		break;
	}

	case SYS_WRITE: {
		fd = *((int*)(f->esp) + 1);
		buffer = *((void**)(f->esp) + 2);
		size = *((unsigned*)(f->esp) + 3);
		f->eax = sys_write(fd, buffer, size);
		break;
	}

	case SYS_EXIT: {
		int status = *((int*)(f->esp) + 1);
		sys_exit(status);
		break;
	}
	}
}

void sys_sleep(int64_t ticks)
{
	timer_sleep(ticks);
}

void sys_halt(void)
{
	shutdown_power_off();
}

bool sys_create(const char* name, unsigned initial_size)
{
	struct file *file_ptr = filesys_open(name);
    if (file_ptr != NULL) {
        // The file already exists, so close it and return false.
        file_close(file_ptr);
        return false;
    }
	return filesys_create(name, initial_size);
}

int sys_open(const char *file) 
{
    struct file *file_ptr = filesys_open(file);

    if (file_ptr == NULL) {
        return -1;
    }

    for (int fd = 2; fd <= MAX_FILES; fd++) {
        if (thread_current()->open_files[fd] == NULL) {
            thread_current()->open_files[fd] = file_ptr;
            return fd;
        }
    }
    // All file descriptors are in use.
	file_close(file_ptr);
    return -1;
}

void sys_close(int fd)
{
	if (fd < 2 || fd > MAX_FILES) {
		return;
	}

	struct file *file_ptr = thread_current()->open_files[fd];
	if (file_ptr == NULL) {
		return;
	}

	file_close(file_ptr);
	thread_current()->open_files[fd] = NULL;
}

bool sys_remove(const char *file_name) {
    return filesys_remove(file_name);
}

void sys_seek(int fd, unsigned position) {
    if (fd < 2 || fd >= MAX_FILES) {
        return;
    }

    struct file *file_ptr = thread_current()->open_files[fd];
    if (file_ptr != NULL) {
        // Make sure we do not seek past EOF
        unsigned file_size = file_length(file_ptr);
        if (position > file_size) {
            position = file_size;  // Prevents seeking beyond EOF
        }
        file_seek(file_ptr, position);
    }
}


unsigned sys_tell(int fd) {
  if (fd < 2 || fd >= MAX_FILES) {
      return -1;  // Invalid FD
  }

  struct file *file_ptr = thread_current()->open_files[fd];
  if (file_ptr != NULL) {
      return file_tell(file_ptr);  // Correctly return position
  }
  return -1;
}


int sys_filesize(int fd) {
    if (fd < 2 || fd >= MAX_FILES) {
        return -1;  // Invalid file descriptor
    }

    struct file *file_ptr = thread_current()->open_files[fd];
    if (file_ptr == NULL) {
        return -1;
    }

    int size = file_length(file_ptr);
    return (size >= 0) ? size : 0;  // Ensure non-negative file size
}



int sys_read(int fd, void *buffer, unsigned size) {
    if (fd == 0) {
        // Read from the keyboard.
        unsigned i;
        uint8_t* local_buffer = (uint8_t*) buffer;
        for (i = 0; i < size; i++) {
            local_buffer[i] = input_getc();
            if (local_buffer[i] == '\r') {  // Convert '\r' to '\n'
                local_buffer[i] = '\n';
            }
			      printf("%c", local_buffer[i]);
        }
        return i;
    } else if (fd > 1 && fd < MAX_FILES) {
		struct file *file_ptr = thread_current()->open_files[fd];
        if (file_ptr != NULL) {
            return file_read(file_ptr, buffer, size);
        }
    }

    return -1;
}

int sys_write(int fd, const void *buffer, unsigned size) {
    if (fd == 1) {  // Writing to STDOUT (console)
        const char *buf = (const char *)buffer;
        for (unsigned i = 0; i < size; i++) {
            if (buf[i] == '\n') {  
                putbuf("\r", 1);  // Convert '\n' to '\r' for proper display
            }
            putbuf(&buf[i], 1);
        }
        return size;
    } else if (fd > 1 && fd < MAX_FILES) {  // Writing to a file
        struct file *file_ptr = thread_current()->open_files[fd];
        if (file_ptr != NULL) {
            return file_write(file_ptr, buffer, size);  // Do NOT modify file content
        }
    }
    return -1;
}

void sys_exit(int status) {

	//NÅT SKA HÄNDA MED STATUS MEN INTE NU I LAB 2

    // Terminate the current thread.
    thread_exit();
}