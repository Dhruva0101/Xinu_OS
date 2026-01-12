/* chprio.c - chprio */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * chprio  --  change the scheduling priority of a process
 *------------------------------------------------------------------------
 */
SYSCALL chprio(int pid, int newprio)
{	
	long start_time, end_time;

	STATWORD ps;    
	struct	pentry	*pptr;

	if(tracking_sys){
		start_time = ctr1000;
	}

	disable(ps);
	if (isbadpid(pid) || newprio<=0 ||
	    (pptr = &proctab[pid])->pstate == PRFREE) {
		restore(ps);

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_CHPRIO, start_time, end_time);
		}

		return(SYSERR);
	}
	pptr->pprio = newprio;
	restore(ps);

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_CHPRIO, start_time, end_time);
		}

	return(newprio);
}
