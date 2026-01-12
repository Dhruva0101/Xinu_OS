/* gettime.c - gettime */

#include <conf.h>
#include <kernel.h>
#include <date.h>
#include <lab0.h>

extern long ctr1000;

extern int getutim(unsigned long *);

/*------------------------------------------------------------------------
 *  gettime  -  get local time in seconds past Jan 1, 1970
 *------------------------------------------------------------------------
 */
SYSCALL	gettime(long *timvar)
{
    /* long	now; */

	/* FIXME -- no getutim */

    long start_time, end_time;
    
    if (tracking_sys) {
        start_time = ctr1000;
    }

    if (tracking_sys) {
        end_time = ctr1000;
        STORE_SYSCALL_INFO(SYSCALL_GETTIME, start_time, end_time);
    }

    return OK;
}
