/* send.c - send */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 *  send  --  send a message to another process
 *------------------------------------------------------------------------
 */
SYSCALL	send(int pid, WORD msg)
{	
	long start_time, end_time;

	STATWORD ps;    
	struct	pentry	*pptr;

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	disable(ps);
	if (isbadpid(pid) || ( (pptr= &proctab[pid])->pstate == PRFREE)
	   || pptr->phasmsg != 0) {
		restore(ps);

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SEND, start_time, end_time);
    }
	
		return(SYSERR);
	}
	pptr->pmsg = msg;
	pptr->phasmsg = TRUE;
	if (pptr->pstate == PRRECV)	/* if receiver waits, start it	*/
		ready(pid, RESCHYES);
	else if (pptr->pstate == PRTRECV) {
		unsleep(pid);
		ready(pid, RESCHYES);
	}
	restore(ps);

	if (tracking_sys) {
	    end_time = ctr1000;
	    STORE_SYSCALL_INFO(SYSCALL_SEND, start_time, end_time);
    }
	
	return(OK);
}
