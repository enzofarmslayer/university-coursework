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


#include "devices/shutdown.h"
#include "devices/input.h"
#include "threads/vaddr.h"
#include <stdlib.h>

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

bool is_valid_fd(int fd) {
	return fd >= 0 && fd < MAX_FILES;
}

static void syscall_handler(struct intr_frame* f) {
	if(!is_valid_ptr(f->esp)) exit(-1);

    int syscall_number = *(int*) f->esp;

	int fd;
	void *buffer;
	unsigned size;
	const char* filename;

	switch (syscall_number) {
		//3 
		case SYS_READ:
		case SYS_WRITE: if(!is_valid_ptr(f->esp + 12)) exit(-1);
		//2 
		case SYS_SEEK:
		case SYS_CREATE: if(!is_valid_ptr(f->esp + 8)) exit(-1);
		//1 
		case SYS_TELL:
		case SYS_FILESIZE:
		case SYS_REMOVE:
		case SYS_OPEN:
		case SYS_EXEC:
		case SYS_EXIT:
		case SYS_CLOSE:
		case SYS_WAIT: if(!is_valid_ptr(f->esp + 4)) exit(-1);
		// 0 
		default:;
	}

    switch (syscall_number) {
		case SYS_SLEEP:
			int64_t sleep_duration = *(int*) (f->esp + 4);
			sleep(sleep_duration);
			break;
		case SYS_HALT:
            halt();
            break;
		case SYS_CREATE:
			const char* name = (const char*) *(int*) (f->esp + 4);
			unsigned initial_size = *(unsigned*) (f->esp + 8);
			
			f->eax = create(name, initial_size);
			break;
        case SYS_OPEN:
			const char* file = (const char*) *(int*) (f->esp + 4);
            
			f->eax = open(file);
            break;
        case SYS_CLOSE:
			fd = *(int*) (f->esp + 4);
            
			close(fd);
            break;
        case SYS_REMOVE:
			filename = (const char*) *(int*) (f->esp + 4);
            f->eax = remove(filename);
            break;
        case SYS_SEEK:
            fd = *(int*) (f->esp + 4);
			unsigned position = *(unsigned*) (f->esp + 8);
			seek(fd, position);
            break;
        case SYS_TELL:
            fd = *(int*) (f->esp + 4);
			
			f->eax = tell(fd);
            break;
		case SYS_FILESIZE:
            fd = *(int*) (f->esp + 4);
			
			f->eax = filesize(fd);
            break;
		case SYS_READ:
			fd = *(int*) (f->esp + 4); // första arg
			buffer = (void*) *(int*) (f->esp + 8); //andra arg
			size = *(unsigned*) (f->esp + 12);// tredje arg

            f->eax = read(fd, buffer, size);
            break;
		case SYS_WRITE:
            fd = *(int*) (f->esp + 4); // första arg
			buffer = (void*) *(int*) (f->esp + 8); //andra arg
			size = *(unsigned*) (f->esp + 12);// tredje arg
			
			f->eax = write(fd, buffer, size);
            break;
		case SYS_EXIT:
            int status = *(int*) (f->esp + 4);
			
			exit(status);
            break;
		case SYS_WAIT: // lab5
			//if(!is_valid_ptr(*((int*)(f->esp) + 1)) exit(-1);
			int child_pid = *(int*) (f->esp + 4);
            f->eax = wait(child_pid);
            break;
		case SYS_EXEC:			
			//if (!is_valid_string((char*)(*((int*)(f->esp) + 1)))) exit(-1);

			filename = (const char*) *(int*) (f->esp + 4);
			f->eax = exec(filename);
			break;
        default:
            //printf("Unknown system call: %d\n", syscall_number);
            exit(-1);

    }
}

tid_t exec(const char *cmd_line){
	if (!is_valid_string(cmd_line)) exit(-1);
	tid_t pid = process_execute(cmd_line);
	return pid;
}

//ändrad i lab 4
void sleep(int64_t millis) {
	timer_msleep(millis);
}

void halt(void){
	shutdown_power_off();
}

bool create(const char *name, unsigned initial_size) {
	if (!is_valid_string(name)) exit(-1);

	return filesys_create(name, initial_size);
}

int open(const char *file) {
	if (!is_valid_string(file)) exit(-1);

	struct file* file_ptr = filesys_open(file);
	if (file_ptr == NULL){
		return -1;		
	}

	//struct thread* curr_thread = thread_current(); 
	for (int fd = 2; fd < MAX_FILES; fd++){    
		if (thread_current() -> open_files[fd] == NULL){     
			thread_current() -> open_files[fd] = file_ptr;  
			return fd;
		}
	}

	//return fd;
	return -1;
}

void close (int fd){ 
	if (!is_valid_fd(fd)) exit(-1);

	struct thread* curr_thread = thread_current(); 
	file_close(curr_thread->open_files[fd]);
	curr_thread->open_files[fd] = NULL;
}

bool remove(const char *file_name) {
	if (!is_valid_string(file_name)) exit(-1);

	return filesys_remove(file_name);
}

void seek(int fd, unsigned position) {
	if (!is_valid_fd(fd)) exit(-1);

	struct file* file = thread_current()->open_files[fd]; 

	if (file == NULL) {
		return;
	}

	if (position <= (unsigned)filesize(fd)) { // prevents seeking beyond EOF
		file_seek(file, position);
	}
}

unsigned tell(int fd){
	if (!is_valid_fd(fd)) exit(-1);

	struct file* file = thread_current()->open_files[fd]; 

	if (file == NULL) {
		return 0;
	}

	return file_tell(file);
}	

int filesize(int fd) { 
	if (!is_valid_fd(fd)) exit(-1);

	struct file* file = thread_current()->open_files[fd]; 

	if (file == NULL) {
		return 0;
	}

	return file_length(file); 
}

int read(int fd, void *buffer, unsigned size) {
	if (!is_valid_fd(fd)) exit(-1);
	if (!is_valid_buffer(buffer, size)) exit(-1);

    // Läs från tangentbord
	if (fd == STDIN_FILENO) { 
		for (unsigned int i = 0; i < size; i++) {
			char input = input_getc();
			if (input == '\r') {  //convert '/r' to '/n'
				input = '\n';
			}

			((char*)buffer)[i] = input;
			putbuf(&input, 1);
		}  
		return size;
	}

	struct file* file = thread_current()->open_files[fd]; 

	if (file == NULL) {
	    return -1;
	}

	int NoBAR = file_read(file, buffer, size); 

	if (NoBAR < 0){ 
		return -1;
	}

	return NoBAR;	
}

int write(int fd, const void *buffer, unsigned size){
	if (!is_valid_fd(fd)) exit(-1);
	if (!is_valid_buffer(buffer, size)) exit(-1);

	if (fd == STDOUT_FILENO) {
        putbuf(buffer, size);
		return size;
    }

	if (fd == STDIN_FILENO) {
		return -1;
	}

	struct file* file = thread_current()->open_files[fd]; 

	if (file == NULL) {
        return -1;
	}

	int NoBAW = file_write(file, buffer, size); 
	
	if (NoBAW < 0) { 
		return -1;
	}

	return NoBAW;
}

// status behöver hanteras i lab5 ingorera warning 
void exit(int status) {
	
	//lab5
	for (int i=2; i < MAX_FILES; i++){
		close(i);
	}

	if (status < 0) {
		status = -1;
	}

	thread_current()->child_parent->exit_status = status;
    
	thread_exit();
}

//lab5
int wait(int pid) {
    return process_wait(pid);
}
