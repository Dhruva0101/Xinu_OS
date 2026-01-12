#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>

void printprocstks (int priority){

    int pid;
    unsigned long pointer;

    for(pid=0; pid < NPROC; pid++){

        struct pentry *ptr = &proctab[pid];

        if(ptr->pstate == PRFREE){
            continue;
        }



        if (ptr->pprio > priority){

            if(ptr->pstate == PRCURR){
                __asm__ __volatile__("movl %%esp, %0" : "=r"(pointer));
            }

            else {
                pointer = ptr->pesp;
            }

                kprintf("Process [%s]\n    pid: %d\n    priority: %d\n    base: 0x%08x\n    limit: 0x%08x\n    len: %d\n    pointer: 0x%08x\n ",ptr->pname,pid, ptr->pprio,ptr->pbase, ptr->plimit,ptr->pstklen, pointer);
        }
        
    }
    
}

// Task 2 (printprocstks)
// Process [main]
//     pid: 49
//     priority: 20
//     base: 0x00ff0ff0
//     limit: 0x00ffffff
//     len: 4096
//     pointer: 0x00ffff33