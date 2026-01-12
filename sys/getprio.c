/* getprio.c - getprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * getprio -- return the scheduling priority of a given process
 *------------------------------------------------------------------------
 */
SYSCALL getprio(int pid)
{
	long start_time, end_time;
	STATWORD ps;    
	struct	pentry	*pptr;
	
	if (tracking_sys) {
    	start_time = ctr1000;
    }

	disable(ps);
	if (isbadpid(pid) || (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_GETPRIO, start_time, end_time);
    }

		return(SYSERR);
	}
	restore(ps);

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_GETPRIO, start_time, end_time);
    }

	return(pptr->pprio);
}
