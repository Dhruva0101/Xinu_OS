/* freemem.c - freemem */

#include <conf.h>
#include <kernel.h>
#include <mem.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;
/*------------------------------------------------------------------------
 *  freemem  --  free a memory block, returning it to memlist
 *------------------------------------------------------------------------
 */
SYSCALL	freemem(struct mblock *block, unsigned size)
{
	STATWORD ps;    
	struct	mblock	*p, *q;
	unsigned top;

	long start_time,end_time;


	if(tracking_sys){
		start_time = ctr1000;
	}

	if (size==0 || (unsigned)block>(unsigned)maxaddr
	    || ((unsigned)block)<((unsigned) &end)){

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_FREEMEM, start_time, end_time);
	}
		
		return(SYSERR);

		}
		
	size = (unsigned)roundmb(size);
	disable(ps);
	for( p=memlist.mnext,q= &memlist;
	     p != (struct mblock *) NULL && p < block ;
	     q=p,p=p->mnext )
		;
	if (((top=q->mlen+(unsigned)q)>(unsigned)block && q!= &memlist) ||
	    (p!=NULL && (size+(unsigned)block) > (unsigned)p )) {
		restore(ps);

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_FREEMEM, start_time, end_time);
	}
		

		return(SYSERR);
	}
	if ( q!= &memlist && top == (unsigned)block )
			q->mlen += size;
	else {
		block->mlen = size;
		block->mnext = p;
		q->mnext = block;
		q = block;
	}
	if ( (unsigned)( q->mlen + (unsigned)q ) == (unsigned)p) {
		q->mlen += p->mlen;
		q->mnext = p->mnext;
	}
	restore(ps);

	if (tracking_sys) {
		end_time = ctr1000;
		STORE_SYSCALL_INFO(SYSCALL_FREEMEM, start_time, end_time);
	}
		
	return(OK);
}
