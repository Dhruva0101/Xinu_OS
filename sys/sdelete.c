/* sdelete.c - sdelete */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * sdelete  --  delete a semaphore by releasing its table entry
 *------------------------------------------------------------------------
 */
SYSCALL sdelete(int sem)
{	
	long start_time, end_time;

	STATWORD ps;    
	int	pid;
	struct	sentry	*sptr;

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	disable(ps);
	if (isbadsem(sem) || semaph[sem].sstate==SFREE) {
		restore(ps);

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SDELETE, start_time, end_time);
    }
		return(SYSERR);
	}
	sptr = &semaph[sem];
	sptr->sstate = SFREE;
	if (nonempty(sptr->sqhead)) {
		while( (pid=getfirst(sptr->sqhead)) != EMPTY)
		  {
		    proctab[pid].pwaitret = DELETED;
		    ready(pid,RESCHNO);
		  }
		resched();
	}
	restore(ps);
	
	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SDELETE, start_time, end_time);
    }

	return(OK);
}
