
#ifndef _LAB0_H_
#define _LAB0_H_

#include <proc.h> 

#define NSYSCALLS 27 

enum syscall_id{

    SYSCALL_FREEMEM = 0,
    SYSCALL_CHPRIO,
    SYSCALL_GETPID,
    SYSCALL_GETPRIO,
    SYSCALL_GETTIME,
    SYSCALL_KILL,
    SYSCALL_RECEIVE,
    SYSCALL_RECVCLR,
    SYSCALL_RECVTIM,
    SYSCALL_RESUME,
    SYSCALL_SCOUNT,
    SYSCALL_SDELETE,
    SYSCALL_SEND,
    SYSCALL_SETDEV,
    SYSCALL_SETNOK,
    SYSCALL_SCREATE,
    SYSCALL_SIGNAL,
    SYSCALL_SIGNALN,
    SYSCALL_SLEEP,
    SYSCALL_SLEEP10,
    SYSCALL_SLEEP100,
    SYSCALL_SLEEP1000,
    SYSCALL_SRESET,
    SYSCALL_STACKTRACE,
    SYSCALL_SUSPEND,
    SYSCALL_UNSLEEP,
    SYSCALL_WAIT
};

typedef enum { false = 0, true = 1 } bool;

struct syscall_info{

    int freq;
    long total_time;
};

extern bool tracking_sys;
extern struct syscall_info summary_table[NPROC][NSYSCALLS];

void syscallsummary_start(void);

void syscallsummary_stop(void);

void printsyscallsummary(void);

#define STORE_SYSCALL_INFO(syscall_id, start_time, end_time) \
    do { \
        summary_table[currpid][syscall_id].freq++; \
        summary_table[currpid][syscall_id].total_time += ((end_time) - (start_time)); \
    } while (0)

#endif
