
#include "global.h"

void initialise_builtin()
{
	strcpy(my_builtins[0],"ls");
	strcpy(my_builtins[1],"pwd");
	strcpy(my_builtins[2],"remindme");
	strcpy(my_builtins[3],"cd");
	strcpy(my_builtins[4],"pinfo");
	strcpy(my_builtins[5],"clock");
	strcpy(my_builtins[6],"echo");
}
int background_checker(char ** args)
{
	int i=0;
	while(args[i])
	{
		if(strcmp(args[i],"&")==0)
		{
			args[i] = NULL;
			return 1;
		}
		i++;
	}
	return 0;
}
void exit_handler (int sig) {
    pid_t pid,wpid;
    int status,i;
    int chek = 0;
    wpid = waitpid(-1, &status, WNOHANG);
    //printf("%d\n",wpid);
    if(wpid) // Checks for the child processes which have changed there status. 
	{
		if(WIFEXITED(status))
		{
			for(i = 1; i <=backprocs; i++)
			{
				if(back_procs[i].proc_id == wpid)
					{
						chek = 1;
						if(strcmp(back_procs[i].cmd,"remindme")==0)
						{
							printf("reminder\n");
						}
						else
						{
							printf("[%d]+   Done\t\t%s pid %d\n",back_procs[i].j_id,  back_procs[i].cmd, wpid);
						}
					}
			}
			if(chek)
			cli();
			fflush (stdout);
		}

		else if(WIFSIGNALED(status))
		{
			for(i = 1; i <=backprocs; i++)
			{
				if(back_procs[i].proc_id == wpid)
					{
						chek=1;
						if(strcmp(back_procs[i].cmd,"remindme")==0)
						{
							printf("reminder\n");
							
						}
						else
						{
							printf("[%d]+   Done\t\t%s with pid %d\n",back_procs[i].j_id,  back_procs[i].cmd , wpid);
						}
					}
			}
			if(chek)
			cli();
			fflush (stdout);
		}
	}
	return;
}

void addbg_proc(int pid,char ** str)
{
	back_procs[++backprocs].proc_id = pid;
	back_procs[backprocs].cmd = str[0];
	back_procs[backprocs].j_id = backprocs;
	if(strcmp(str[0],"remindme")==0)
	{
		return;
	}
	printf("process %s with pid %d has started in the background\n",str[0],pid);
	printf("[%d] %d\n",back_procs[backprocs].j_id,pid);
	return;
}
int restcommands(char ** args)
{
	int checker = background_checker(args);
	pid_t proc_id, wpid;
	int proc_status;
	int i=0;
	proc_id = fork();
	if(proc_id == 0)
	{
		if(execvp(args[0],args) < 0)
		{
			perror("exec");
		}
		else
		{
			exit(EXIT_SUCCESS);
		}
	}
	else if(proc_id < 0)
	{
		printf("Forking error in restcommands\n");
	}
	else
	{
		if(checker)
		{
			addbg_proc(proc_id,args);
		}
		else
		{	
			sigid = proc_id;
			wait(NULL); 
		sigid=0;
		}
	return 1;
	}
}
int execute_command(char ** args)
{
	int i;
	int t =0;
	for(i=0;i<builtins;i++)
	{
		if(strcmp(args[0],my_builtins[i])==0)
		{
			if(strcmp(args[0],"ls")==0)
			{
				ls(args);
				return 1;
			}
			else if(strcmp(args[0],"cd")==0)
			{
				int y= cd(args);
				return 1;
			}
			else if(strcmp(args[0],"pwd")==0)
			{
				pwd(args);
				return 1;
			}
			else if(strcmp(args[0],"remindme")==0)
			{
				//printf("yoo\n");
				reminder(args);
				return 1;
				//num_reminders++;	 
			}
			else if(strcmp(args[0],"pinfo")==0)
			{
				pinfo(args);
				return 1;
			}
			else if(strcmp(args[0],"clock")==0)
			{
				myclock(args);
				return 1;
			}
			else if(strcmp(args[0],"echo")==0)
			{
				echo(args);
				return 1;
			}
		}
	}
	return restcommands(args);
}