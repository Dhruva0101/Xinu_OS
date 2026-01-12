/* setdev.c - setdev */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 *  setdev  -  set the two device entries in the process table entry
 *------------------------------------------------------------------------
 */
SYSCALL	setdev(int pid, int dev1, int dev2)
{
	long start_time, end_time;

	short	*nxtdev;

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	if (isbadpid(pid)){

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_SETDEV, start_time, end_time);
		}

	return(SYSERR);

	}

	nxtdev = (short *) proctab[pid].pdevs;
	*nxtdev++ = dev1;
	*nxtdev = dev2;

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_SETDEV, start_time, end_time);
	}

	return(OK);
}
