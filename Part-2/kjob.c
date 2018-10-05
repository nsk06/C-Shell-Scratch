#include "global.h"
int mykj(char ** args)
{
    if(args[3] !=NULL)
    {
    	printf("Extra arguements\n");
    }
    else if(args[1] == NULL || args[2] == NULL)
    {
    	printf("Less arguements\n");
    } 
    else
    {
        int job_id=atoi(args[1]);
        int sig_no=atoi(args[2]);
        if(job_id > backprocs)
        {
            perror("No such job found");
        }
        else if(job_id < 1)
        {
        	perror("No such job found");
        }
        else
        {
            int pid=back_procs[job_id].proc_id;
            int signal = kill(pid,sig_no);
            if(signal==-1)
            {
                perror("Failed\n");
            }
        }
    }
    return 1;
}