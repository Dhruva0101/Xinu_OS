#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

bool tracking_sys = FALSE;
struct syscall_info summary_table[NPROC][NSYSCALLS];

void syscallsummary_start(){

    int pid,syscall_id ;

    for(pid = 0 ; pid <  NPROC ; pid++){

        for(syscall_id = 0 ; syscall_id < NSYSCALLS ; syscall_id++){

                summary_table[pid][syscall_id].freq = 0;
                summary_table[pid][syscall_id].total_time = 0;

        }

    }

    tracking_sys = TRUE;

}

void syscallsummary_stop(){

        tracking_sys = FALSE;

}

void printsyscallsummary(){

    int pid,syscall_id ;

    const char *syscall_names[NSYSCALLS] = {

    "sys_freemem", "sys_chprio", "sys_getpid", "sys_getprio", "sys_gettime",
    "sys_kill", "sys_receive", "sys_recvclr", "sys_recvtim", "sys_resume",
    "sys_scount", "sys_sdelete", "sys_send", "sys_setdev", "sys_setnok",
    "sys_screate", "sys_signal", "sys_signaln", "sys_sleep", "sys_sleep10",
    "sys_sleep100", "sys_sleep1000", "sys_sreset", "sys_stacktrace",
    "sys_suspend", "sys_unsleep", "sys_wait"

    };

    for(pid = 0 ; pid <  NPROC ; pid++){

        int made_syscalls = 0;

        for(syscall_id = 0 ; syscall_id < NSYSCALLS ; syscall_id++){

            if(summary_table[pid][syscall_id].freq > 0){
                made_syscalls = 1;
                break;
            }
        }    
        
        if(!made_syscalls){
            continue;
        }

        kprintf("Process [pid:%d]\n", pid);
        
        for (syscall_id = 0; syscall_id < NSYSCALLS; syscall_id++) {
            
            int freq = summary_table[pid][syscall_id].freq;
            long total_time = summary_table[pid][syscall_id].total_time;

            if (freq == 0) {
                continue; 
            }

        long avg_time = (total_time / freq);
        kprintf("   Syscall: %s, count: %d, average execution time: %ld (ms)\n", syscall_names[syscall_id], freq,avg_time);

        }

    }

}

