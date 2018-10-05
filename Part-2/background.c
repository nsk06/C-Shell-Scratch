#include "global.h"
int back_changer(char ** args)
{
	if(args[2]!= NULL)
	{
		printf("Exceeding no. of arguements\n");
	}
	else if(args[1] == NULL)
	{
		//printf("%s\n",back_procs[backprocs].cmd );
		kill(back_procs[backprocs].proc_id,SIGCONT);
		printf("process \t  with pid %d changed state\n",back_procs[backprocs].proc_id);
				back_procs[backprocs].cmd_status = "Running";	
	}
	else
	{
		int jid = atoi(args[1]);
		if(jid > backprocs || jid < 1)
		{	
			printf("No such job\n");
		}
		else
		{
			if(back_procs[jid].cmd_status == "Running")
			{
				printf("Already Running\n");
				return 0;
			}
			int out = kill(back_procs[jid].proc_id,SIGCONT);
			if(out == -1)
			{
				perror("kill error");
			}
			else
			{
				printf("process \t  with pid %d changed state\n",back_procs[jid].proc_id);
				back_procs[jid].cmd_status = "Running";
			}
		}
	}
	return 1;
}