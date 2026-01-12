#include <conf.h>
#include <kernel.h>
#include <proc.h>
#include <stdio.h>
#include <zfunction.h>
#include <lab0.h>

/*------------------------------------------------------------------------
*  main  --  user main program
*------------------------------------------------------------------------
*/
void prch(char c)
{
    int i;
    sleep(5);	
}
int main()
{
    kprintf("\n\nTask 1 (zfunction)\n");
    kprintf("0xaabbccdd => 0x%1X\n", zfunction(0xaabbccdd));

    kprintf("\nTask 2 (printprocstks)\n");
    printprocstks(10);

    kprintf("\nTask 3 (printsyscallsummary)\n");
    syscallsummary_start(); 
    int prX = create(prch, 2000, 20, "proc X", 1, 'A');       
    resume(prX);
    sleep(10);
    syscallsummary_stop();
    printsyscallsummary();

    return 0;
}