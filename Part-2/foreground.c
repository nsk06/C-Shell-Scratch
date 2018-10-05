#include "global.h"
int bring_foreground(char ** args)
{
	if(args[2]!= NULL)
	{
		printf("Exceeding no. of arguements\n");
	}
	else if(args[1] == NULL)
	{
		kill(back_procs[backprocs].proc_id,SIGCONT);
		sigid = back_procs[backprocs].proc_id;
				back_procs[backprocs].is_bg = 0;
				printf("process \t  with pid %d brought to foreground\n",back_procs[backprocs].proc_id);
				cur_fgproc.proc_id = sigid;
				waitpid(back_procs[backprocs].proc_id,NULL,WUNTRACED);
				sigid = 0;
				cur_fgproc.proc_id  = 0;
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
			int out = kill(back_procs[jid].proc_id,SIGCONT);
			if(out == -1)
			{
				perror("kill error");
			}
			else
			{
				sigid = back_procs[jid].proc_id;
				back_procs[jid].is_bg = 0;
				cur_fgproc.proc_id  = sigid;
				printf("process \t  with pid %d brought to foreground\n",back_procs[jid].proc_id);
				waitpid(back_procs[jid].proc_id,NULL,WUNTRACED);
				sigid = 0;
				cur_fgproc.proc_id  = 0;
			}
		}
	}
	return 1;
}