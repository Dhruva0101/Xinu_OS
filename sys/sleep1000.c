/* sleep1000.c - sleep1000 */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * sleep1000 --  delay the caller for a time specified in 1/100 of seconds
 *------------------------------------------------------------------------
 */
SYSCALL sleep1000(int n)
{
	long start_time, end_time;

	STATWORD ps;    

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	if (n < 0  || clkruns==0){

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_SLEEP1000, start_time, end_time);
		}
	
	return(SYSERR);
	}

	disable(ps);
	if (n == 0) {		/* sleep1000(0) -> end time slice */
	        ;
	} else {
		insertd(currpid,clockq,n);
		slnempty = TRUE;
		sltop = &q[q[clockq].qnext].qkey;
		proctab[currpid].pstate = PRSLEEP;
	}
	resched();
        restore(ps);

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_SLEEP1000, start_time, end_time);
		}
		
	return(OK);
}
