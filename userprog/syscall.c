#include "userprog/syscall.h"


#include "threads/interrupt.h"
#include "threads/thread.h"

#include <stdio.h>
#include <syscall-nr.h>
#include "userprog/process.h"

#include "devices/input.h" 
#include <string.h>

#include "devices/timer.h"      // for timer_sleep
#include "threads/init.h"       // for shutdown_power_off
#include "filesys/filesys.h"    // for filesys_create and filesys_open


static void syscall_handler(struct intr_frame*);

//Fanns sedan innan
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

bool is_valid_ptr(const void* ptr) {
	if (ptr >= PHYS_BASE) {
		return false;
	}
 
	// Validate the first page
	if (pagedir_get_page(thread_current()->pagedir, ptr) == NULL) {
		return false;
	}

	int length = sizeof(void*);
	void* upper_bound = pg_round_up(ptr);
	void* page;

	// Validate the next pages
	while ((ptr + length) > upper_bound) {

		// Make sure the next page is valid in pagedir
		upper_bound++;
		page = pagedir_get_page(thread_current()->pagedir, upper_bound);
		if (page == NULL) {
			return false;
		}

		// Upper bound is valid page in the pagedir, update upper bound
		upper_bound = pg_round_up(page);
	}

	// If we get here, we know all the pages the string spans over are valid
	return true;
}

/* Validates if a string has a terminator character */
bool is_valid_string(const char* s) {
	bool valid_ptr = is_valid_ptr(s);
	if (!valid_ptr) return false;

	// Find out the length of the string
	int length = strlen(s);

	// Find the end of the page
	void* upper_bound = pg_round_up(s);
	void* page;
	bool result = false;

	// Loop while string might be out of the page, but still in a valid page
	while ((void*)(s + (length * sizeof(char))) > upper_bound) {
		
		// Make sure the next page is valid in pagedir
		upper_bound++;
		page = pagedir_get_page(thread_current()->pagedir, upper_bound);
		if (page == NULL) {
			return false;
		}

		// Upper bound is a valid page in the pagedir, update the upper_bound
		upper_bound = pg_round_up(page);
	}

	// If we get here, we know all the pages the string spans over are valid
	return true;
}

bool is_valid_buffer(const void* buffer, unsigned length) {

	bool valid_ptr = is_valid_ptr(buffer);
	if(!valid_ptr) return false;

	// Find out how long the buffer is
	unsigned size = length * sizeof(char);

	void* upper_bound = pg_round_up(buffer); 
	void* page;

	// Loop while buffer might be out of the page, but still in a valid page
	while ((void*)(buffer + size) > upper_bound) {
		
		// Make sure next page is valid in the pagedir
		upper_bound++;
		page = pagedir_get_page(thread_current()->pagedir, upper_bound);
		if (page == NULL) {
			return false;
		}

		// Upper bound is a valid page in the pagedir, update the upper_bound
		upper_bound = pg_round_up(page);
	}

	// If we get here, we know all the pages the buffer spans over are valid
	return true;
}

static void syscall_handler(struct intr_frame* f UNUSED)
{
	if(!is_valid_ptr(f->esp)) exit(-1);

	int fd;
	void *buffer;
	unsigned size;
	
	switch(*(int*)(f->esp))
	{
	
	case SYS_SLEEP:{
		int64_t sleep_duration = *((int*)(f->esp) + 1);
		sleep(sleep_duration);
		break;
	}
	case SYS_HALT:{
		halt();
		break;
	}
	case SYS_CREATE:{
		if(!is_valid_ptr(f->esp + 8)) exit(-1);
		const char* name = (char*)(*((int*)(f->esp) + 1));
		if (!is_valid_string(file)) exit(-1);
		unsigned initial_size = *((int*)(f->esp) + 2);
		f->eax = create(name, initial_size);
		break;
	}
	case SYS_OPEN:{
		const char* file = (char*)(*((int*)(f->esp) + 1));
		if (!is_valid_string(file)) exit(-1);
		f->eax = open(file);
		break;
	}
	case SYS_CLOSE:{
		fd = *((int*)(f->esp) + 1);
		close(fd);
		break;
	}
	case SYS_REMOVE:{
		const char* filename = (char*)(*((int*)(f->esp) + 1));
        if (!is_valid_string(filename)) exit(-1);
		f->eax = remove(filename);
        break;
	}
	case SYS_SEEK: {
		fd = *((int*)(f->esp) + 1);
		unsigned position = *((int*)(f->esp) + 2);
		seek(fd, position);
		break;
	}
	case SYS_TELL:{
		fd = *((int*)(f->esp) + 1);
		f->eax = tell(fd);
		break;
	}
	case SYS_FILESIZE:{
		fd = *((int*)(f->esp) + 1);
		f->eax = filesize(fd);
		break;
	}
	case SYS_READ:{
		fd = *((int*)(f->esp) + 1); // första arg
		buffer = *((void**)(f->esp) + 2); //andra arg
		size = *((unsigned*)(f->esp) + 3);// tredje arg
		f->eax = read(fd, buffer, size);
		if (!is_valid_buffer(buffer, size)) exit(-1);
		break;
	}
	case SYS_WRITE: {
		if(!is_valid_ptr(f + 12)) exit(-1);
		fd = *((int*)(f->esp) + 1);
		buffer = *((void**)(f->esp) + 2);
		size = *((unsigned*)(f->esp) + 3);
		if (!is_valid_buffer(buffer, size)) exit(-1);
		f->eax = write(fd, buffer, size);
		break;
	}
	case SYS_EXIT: {
		int status = *((int*)(f->esp) + 1);
		exit(status);
		break;
	}
	case SYS_WAIT: { // LAB 5
		if(!is_valid_ptr(f->esp + 4)) exit(-1);
		// tid_t child_pid = *((int*)(f->esp) + 1);
		// f->eax = process_wait(child_pid);
    	break; 
	}
	case SYS_EXEC: {
		const char* filename = (char*)(*((int*)(f->esp) + 1));
		if (!is_valid_string(filename)) exit(-1);
		f->eax = exec(filename);
	}
	}
}

tid_t exec(const char *cmd_line) {
	return process_execute(cmd_line);
}

// Ändrad i lab4
void sleep(int64_t ticks)
{
	timer_sleep(ticks);
}

void halt(void)
{
	shutdown_power_off();
}

bool create(const char* name, unsigned initial_size)
{
	struct file *file_ptr = filesys_open(name);
    if (file_ptr != NULL) {
        // Fil already exists 
        file_close(file_ptr);
        return false;
    }
	return filesys_create(name, initial_size);
}

int open(const char *file) 
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
	// return fd;

    // All file descriptors are in use.
	file_close(file_ptr);
    return -1;
}

void close(int fd)
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

bool remove(const char *file_name) {
    return filesys_remove(file_name);
}

void seek(int fd, unsigned position) {
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


unsigned tell(int fd) {
  if (fd < 2 || fd >= MAX_FILES) {
      return -1; 
  }

  struct file *file_ptr = thread_current()->open_files[fd];
  if (file_ptr != NULL) {
      return file_tell(file_ptr);  
  }
  return -1;
}


int filesize(int fd) {
    if (fd < 2 || fd >= MAX_FILES) {
        return -1;  
    }

    struct file *file_ptr = thread_current()->open_files[fd];
    if (file_ptr == NULL) {
        return -1;
    }

    int size = file_length(file_ptr);
    return (size >= 0) ? size : 0;  // Ensure non-negative file size
}


int read(int fd, void *buffer, unsigned size) {
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
    } else if (fd > 1 && fd < MAX_FILES) { // read from file 
		struct file *file_ptr = thread_current()->open_files[fd];
        if (file_ptr != NULL) {
            return file_read(file_ptr, buffer, size);
        }
    }

    return -1;
}

int write(int fd, const void *buffer, unsigned size) {
    if (fd == 1) {  // Writing to console
        const char *buf = (const char *)buffer;
        for (unsigned i = 0; i < size; i++) {
            if (buf[i] == '\n') {  
                putbuf("\r", 1);  // Convert '\n' to '\r' for display
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

// status behöver hanteras lab5 ignorera warning
void exit(int status) {

	// lab5
	// if (status < 0){
	// 	status = -1
	// }

	// for (int i=2; i < MAX_FILES; i++){
	// 	close(i);
	// } 

	// thread_current()->child_parent->exit_status = status;

	thread_exit();
}