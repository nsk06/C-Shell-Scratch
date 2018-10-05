
#include "global.h"


void  SIGINT_handler(int signal_num)
{
	/*if(cur_fgproc.is_fg == 0)
	{
		printf("hey\n");
		return ;
	}*/
	if(cur_fgproc.proc_id)
	{
		//printf("here\n");
		if(kill(sigid,SIGINT) == 0)
		{	
			//printf("here\n");
			cur_fgproc.is_fg = 0;
			return;
		}
	}
	else
	{
		//printf("yooo\n");
		signal(signal_num, SIG_IGN); 
		//signal(SIGCHLD, exit_handler);
		printf("\n");
		cli();
		fflush(stdout); 
		signal(signal_num, SIGINT_handler);
	}
	 //killpg(200,SIGCONT);
	//killpg(100,SIGKILL);
}

void SIGTSTP_handler(int signal_num)
{
	/*if(cur_fgproc.is_fg == 0)
	{
		printf("hey\n");
		return ;
	}*/
	if(cur_fgproc.proc_id)
	{
		if(kill(sigid,SIGTSTP) == 0)
		{
			//printf("hi\n");
			zchek = 1;
			backprocs++;
			back_procs[backprocs].proc_id = sigid;
			back_procs[backprocs].j_id = backprocs;
			back_procs[backprocs].cmd_status = "Stopped";
			back_procs[backprocs].is_bg = 1;
			cur_fgproc.is_fg = 0;
			//printf("%s\n",cur_fgproc.cmd);
			back_procs[backprocs].cmd = cur_fgproc.cmd;
			printf("[%d] Stopped [%d]  \t%s\n",back_procs[backprocs].j_id,back_procs[backprocs].proc_id,cur_fgproc.cmd);
			sigid = 0;
			//cli();
			fflush(stdout);
			return;
		}
	}
	else
	{
		printf("\n");
		cli();
		signal(signal_num, SIG_IGN); 
		signal(SIGCHLD, exit_handler);
		fflush(stdout); 
		signal(signal_num, SIGTSTP_handler);

	}
}
void SIGQUIT_handler(int signal_num)
{
	printf("Recieved sigquit\n");
	cli();
	fflush(stdout);
	return;
}