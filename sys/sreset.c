/* sreset.c - sreset */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sem.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 *  sreset  --  reset the count and queue of a semaphore
 *------------------------------------------------------------------------
 */
SYSCALL sreset(int sem, int count)
{
	long start_time, end_time;

	STATWORD ps;    
	struct	sentry	*sptr;
	int	pid;
	int	slist;

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	disable(ps);
	if (isbadsem(sem) || count<0 || semaph[sem].sstate==SFREE) {
		restore(ps);

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_SRESET, start_time, end_time);
		}
		return(SYSERR);
	}
	sptr = &semaph[sem];
	slist = sptr->sqhead;
	while ((pid=getfirst(slist)) != EMPTY)
		ready(pid,RESCHNO);
	sptr->semcnt = count;
	resched();
	restore(ps);

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SRESET, start_time, end_time);
    }
	return(OK);
}
