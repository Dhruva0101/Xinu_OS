/* receive.c - receive */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 *  receive  -  wait for a message and return it
 *------------------------------------------------------------------------
 */
SYSCALL	receive()
{
	long start_time, end_time;

	STATWORD ps;    
	struct	pentry	*pptr;
	WORD	msg;

	if (tracking_sys) {
    	start_time = ctr1000;
    }

	disable(ps);
	pptr = &proctab[currpid];
	if ( !pptr->phasmsg ) {		/* if no message, wait for one	*/
		pptr->pstate = PRRECV;
		resched();
	}
	msg = pptr->pmsg;		/* retrieve message		*/
	pptr->phasmsg = FALSE;
	restore(ps);

    if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_RECEIVE, start_time, end_time);
    }

	return(msg);
}
