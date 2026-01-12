/* sleep.c - sleep */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <q.h>
#include <sleep.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * sleep  --  delay the calling process n seconds
 *------------------------------------------------------------------------
 */
SYSCALL	sleep(int n)
{
	long start_time, end_time;

	STATWORD ps;    

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	if (n<0 || clkruns==0){

	    if (tracking_sys) {
            end_time = ctr1000;
            STORE_SYSCALL_INFO(SYSCALL_SLEEP, start_time, end_time);
        }

		return(SYSERR);
	}

	if (n == 0) {
	    
		disable(ps);
		resched();
		restore(ps);

        if (tracking_sys) {
            end_time = ctr1000;
            STORE_SYSCALL_INFO(SYSCALL_SLEEP, start_time, end_time);
        }

		return(OK);
	}

	while (n >= 1000) {
		sleep10(10000);
		n -= 1000;
	}
	if (n > 0){
		sleep10(10*n);
	
		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_SLEEP, start_time, end_time);
		}
	}
	return(OK);
}
