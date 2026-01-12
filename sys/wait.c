/* wait.c - wait */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * wait  --  make current process wait on a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL	wait(int sem)
{
	long start_time, end_time;

	STATWORD ps;    
	struct	sentry	*sptr;
	struct	pentry	*pptr;

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_WAIT, start_time, end_time);
    }
		return(SYSERR);
	}
	
	if (--(sptr->semcnt) < 0) {
		(pptr = &proctab[currpid])->pstate = PRWAIT;
		pptr->psem = sem;
		enqueue(currpid,sptr->sqtail);
		pptr->pwaitret = OK;
		resched();
		restore(ps);

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_WAIT, start_time, end_time);
    }
		return pptr->pwaitret;
	}
	restore(ps);

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_WAIT, start_time, end_time);
    }

	return(OK);
}
