/* scount.c - scount */

#include <conf.h>
#include <kernel.h>
#include <sem.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 *  scount  --  return a semaphore count
 *------------------------------------------------------------------------
 */
SYSCALL scount(int sem)
{
	long start_time, end_time;

	extern	struct	sentry	semaph[];

	if (tracking_sys) {
		start_time = ctr1000;
	}

	if (isbadsem(sem) || semaph[sem].sstate==SFREE){

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SCOUNT, start_time, end_time);
    }
		return(SYSERR);
	}

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SCOUNT, start_time, end_time);
    }

	return(semaph[sem].semcnt);
}
