/* stacktrace.c - stacktrace */

#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <lab0.h>

extern long ctr1000;

static inline unsigned long read_esp(void) {
    unsigned long v;
    __asm__ __volatile__("movl %%esp, %0" : "=r"(v));
    return v;
}
static inline unsigned long read_ebp(void) {
    unsigned v;
    __asm__ __volatile__("movl %%ebp, %0" : "=r"(v));
    return v;
}

#define STKDETAIL

/*------------------------------------------------------------------------
 * stacktrace - print a stack backtrace for a process
 *------------------------------------------------------------------------
 */
SYSCALL stacktrace(int pid)
{
	long start_time, end_time;

	struct pentry	*proc = &proctab[pid];
	unsigned long	*sp, *fp;

	if (tracking_sys) {
	    start_time = ctr1000;
    }

	if (pid != 0 && isbadpid(pid)){
			
		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_STACKTRACE, start_time, end_time);
		}
	
	return SYSERR;
	}
	
	if (pid == currpid) {
		sp = read_esp();
		fp = read_ebp();
	} else {
		sp = (unsigned long *)proc->pesp;
		fp = sp + 2; 		/* where ctxsw leaves it */
	}
	kprintf("sp %X fp %X proc->pbase %X\n", sp, fp, proc->pbase);
#ifdef STKDETAIL
	while (sp < (unsigned long *)proc->pbase) {
		for (; sp < fp; sp++)
			kprintf("DATA (%08X) %08X (%d)\n", sp, *sp, *sp);
		if (*sp == MAGIC)
			break;
		kprintf("\nFP   (%08X) %08X (%d)\n", sp, *sp, *sp);
		fp = (unsigned long *) *sp++;
		if (fp <= sp) {
			kprintf("bad stack, fp (%08X) <= sp (%08X)\n", fp, sp);

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_STACKTRACE, start_time, end_time);
		}

			return SYSERR;
		}
		kprintf("RET  0x%X\n", *sp);
		sp++;
	}
	kprintf("MAGIC (should be %X): %X\n", MAGIC, *sp);
	if (sp != (unsigned long *)proc->pbase) {
		kprintf("unexpected short stack\n");

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_STACKTRACE, start_time, end_time);
		}
		return SYSERR;
	}
#endif

		if (tracking_sys) {
			end_time = ctr1000;
			STORE_SYSCALL_INFO(SYSCALL_STACKTRACE, start_time, end_time);
		}

	return OK;
}
