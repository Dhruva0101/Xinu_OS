/* signal.c - signal */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * signal  --  signal a semaphore, releasing one waiting process
 *------------------------------------------------------------------------
 */
SYSCALL signal(int sem)
{
	long start_time, end_time;

	STATWORD ps;    
	register struct	sentry	*sptr;

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	disable(ps);
	if (isbadsem(sem) || (sptr= &semaph[sem])->sstate==SFREE) {
		restore(ps);
	
	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SIGNAL, start_time, end_time);
    }
		return(SYSERR);
	}
	if ((sptr->semcnt++) < 0)
		ready(getfirst(sptr->sqhead), RESCHYES);
	restore(ps);
	
	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SIGNAL, start_time, end_time);
    }
	return(OK);
}
