/* recvclr.c - recvclr */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 *  recvclr  --  clear messages, returning waiting message (if any)
 *------------------------------------------------------------------------
 */
SYSCALL	recvclr()
{	
	long start_time, end_time;

	STATWORD ps;    
	WORD	msg;

	if (tracking_sys) {
    	start_time = ctr1000;
    }

	disable(ps);
	if (proctab[currpid].phasmsg) {
		proctab[currpid].phasmsg = 0;
		msg = proctab[currpid].pmsg;
	} else
		msg = OK;
	restore(ps);

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_RECVCLR, start_time, end_time);
    }

	return(msg);
}
