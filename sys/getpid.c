/* getpid.c - getpid */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <lab0.h>

extern long ctr1000;

/*------------------------------------------------------------------------
 * getpid  --  get the process id of currently executing process
 *------------------------------------------------------------------------
 */
SYSCALL getpid()
{
	long start_time, end_time;
    
    if (tracking_sys) {
    	start_time = ctr1000;
    }

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_GETPID, start_time, end_time);
    }

	return(currpid);
}
