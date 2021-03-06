#ifndef _UNISTD_H
#define _UNISTD_H

#include <syscall.h>
#include <types.h>
#include <sos/signal.h>

#define _syscall0(ret_t, fn) \
ret_t fn() \
{ \
    ret_t ret;  \
    asm volatile ( "int $0x80 \n" \
            :"=a"(ret) \
            :"a"(SYS_##fn) \
            :"cc", "memory"); \
    return ret; \
}

#define _syscall1(ret_t, fn, t1, arg1) \
ret_t fn(t1 arg1) \
{ \
    ret_t ret;  \
    asm volatile ( "int $0x80 \n" \
            :"=a"(ret) \
            :"a"(SYS_##fn), "b"(arg1) \
            :"cc", "memory"); \
    return ret; \
}

#define _syscall2(ret_t, fn, t1, arg1, t2, arg2) \
ret_t fn(t1 arg1, t2 arg2) \
{ \
    ret_t ret;  \
    asm volatile ( "int $0x80 \n" \
            :"=a"(ret) \
            :"a"(SYS_##fn), "b"(arg1), "c"(arg2) \
            :"cc", "memory"); \
    return ret; \
}

#define _syscall3(ret_t, fn, t1, arg1, t2, arg2, t3, arg3) \
ret_t fn(t1 arg1, t2 arg2, t3 arg3) \
{ \
    ret_t ret;  \
    asm volatile ( "int $0x80 \n" \
            :"=a"(ret) \
            :"a"(SYS_##fn), "b"(arg1), "c"(arg2), "d"(arg3) \
            :"cc", "memory"); \
    return ret; \
}

#define _syscall4(ret_t, fn, t1, arg1, t2, arg2, t3, arg3, t4, arg4) \
ret_t fn(t1 arg1, t2 arg2, t3 arg3, t4 arg4) \
{ \
    ret_t ret;  \
    asm volatile ( "int $0x80 \n" \
            :"=a"(ret) \
            :"a"(SYS_##fn), "b"(arg1), "c"(arg2), "d"(arg3), "S"(arg4) \
            :"cc", "memory"); \
    return ret; \
}

#define STDIN_FILENO    0
#define STDOUT_FILENO   1
#define STDERR_FILENO   2

#ifndef NULL
#define NULL    ((void*)0)
#endif

#define SEEK_SET    0
#define SEEK_CUR    1
#define SEEK_END    2

extern int errno;

#ifdef __cplusplus
extern "C" {
#endif

int write(int fildes, const void *buf, size_t nbyte);
int close(int fd);
int read(int fildes, void *buf, size_t nbyte);
int fork();
int exec(const char *path, char *const argv[], char *const envp[]);
int execve(const char *path, char *const argv[], char *const envp[]);
int getpid();
int getppid();
int sleep(int);
int exit(int);
int readdir(unsigned int fd, struct dirent *dirp, unsigned int count);
int dup(int fd);
int dup2(int fd, int fd2);
int pipe(int fd[2]);
int kdump();
void* sbrk(int inc);
off_t lseek(int, off_t, int);
int stat(const char *pathname, struct stat *buf);
int fstat(int fd, struct stat *buf);
int lstat(const char *pathname, struct stat *buf);
int kill(pid_t pid, int sig);
int signal(int signum, unsigned long handler);
int sigpending(sigset_t *set);
int sigprocmask(int how, sigset_t *set, sigset_t *oldset);
int sigsuspend(sigset_t *sigmask);
int chdir(const char *path);
int fchdir(int fd);
char* getcwd(char *buf, size_t size);

// return -1 if no child, or pid of any of children exited
pid_t wait(int *status);
pid_t waitpid(pid_t pid, int *status, int options);

#ifdef __cplusplus
}
#endif
#endif
