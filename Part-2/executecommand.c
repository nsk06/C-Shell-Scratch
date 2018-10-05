
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
	strcpy(my_builtins[7],"jobs");
	strcpy(my_builtins[8],"setenv");
	strcpy(my_builtins[9],"unsetenv");
	strcpy(my_builtins[10],"kjob");
	strcpy(my_builtins[11],"overkill");
	strcpy(my_builtins[12],"bg");
	strcpy(my_builtins[13],"fg");
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
void exit_handler (int sig)
 {
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
				if(back_procs[i].proc_id == wpid && back_procs[i].is_bg == 1)
					{
						chek = 1;
						if(strcmp(back_procs[i].cmd,"remindme")==0)
						{
							printf("reminder\n");
						}
						else
						{
							printf("[%d]+   Done\t\t%s \t normally pid %d\n",back_procs[i].j_id,  back_procs[i].cmd, wpid);
						}
						back_procs[i].cmd_status = "Done";
						back_procs[i].is_bg  = 0;
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
				if(back_procs[i].proc_id == wpid && back_procs[i].is_bg == 1)
					{
						//printf("%d\n",WTERMSIG(status));
						chek=1;
						if(strcmp(back_procs[i].cmd,"remindme")==0)
						{
							printf("reminder\n");
							
						}
						else
						{
							printf("[%d]+   Done\t\t%s \t abnormally with pid %d\n",back_procs[i].j_id,  back_procs[i].cmd , wpid);
						}
						back_procs[i].cmd_status = "Terminated";
						//back_procs[i].is_bg  = 0;
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
	backprocs++;
	back_procs[backprocs].proc_id = pid;
	back_procs[backprocs].cmd = str[0];
	//printf("%s\t%d\n",back_procs[backprocs].cmd,backprocs);
	// t = str[0];
	back_procs[backprocs].j_id = backprocs;
	back_procs[backprocs].cmd_status = "Running";
	back_procs[backprocs].is_bg = 1;

	//printf("%s\t%d\n",back_procs[backprocs].cmd_status,backprocs);
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
	//printf("inside\n");
	//exit(0);
	int checker = background_checker(args);
	pid_t proc_id, wpid;
	int proc_status;
	int i=0;
	proc_id = fork();
	if(proc_id == 0)
	{
		if(checker)
		{
			int ch = setpgid(0,0);
			if(ch != 0)
			{
				perror("pgid");
			}
		}
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
			//printf("here i am brooo\n");
			printf("%d\n",proc_id);
			addbg_proc(proc_id,args);
			//printf("%s\n",back_procs[backprocs].cmd);
		}
		else
		{	
			cur_fgproc.proc_id = proc_id;
			cur_fgproc.cmd = args[0];
			cur_fgproc.is_fg = 1; 
			sigid = proc_id;
			waitpid(proc_id,NULL,WUNTRACED); 
			sigid=0;
			cur_fgproc.proc_id = 0;
			cur_fgproc.is_fg = 0;
			cur_fgproc.cmd = "";
		}
	return 0;
	}
}
int execute_command(char ** args,char *fullcommand)
{
	int i;
	int t =0;
	int pipe_detect=0,red_detect=0;
	int k =0;
	while(args[k])
	{
		if(strcmp(args[k],"|")==0)
		{
			pipe_detect = 1;
		}
		if(strcmp(args[k],"<")==0 || strcmp(args[k],">")==0 || strcmp(args[k],">>")==0)
		{
			red_detect = 1;
		}
		k++;
	}
	if(red_detect == 1 && pipe_detect == 0)
	{
		int v = check_redirection(args);
		if(v==1)
			return 1;
	}
	else if(pipe_detect ==1)
	{
		piper(args,fullcommand);
		return 1;
	}
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
			else if(strcmp(args[0],"setenv")==0)
			{
				env_setter(args);
				return 1;
			}
			else if(strcmp(args[0],"unsetenv")==0)
			{
				unsetter(args);
				return 1;
			}
			else if(strcmp(args[0],"jobs")==0)
			{
				myjobs(args);
				return 1;
			}
			else if(strcmp(args[0],"kjob")==0)
			{
				mykj(args);
				return 1;
			}
			else if(strcmp(args[0],"overkill")==0)
			{
				killer(args);
				return 1;
			}
			else if(strcmp(args[0],"fg")==0)
			{
				bring_foreground(args);
				return 1;
			}
			else if(strcmp(args[0],"bg")==0)
			{
				back_changer(args);
				return 1;
			}
		}
	}
	
	return restcommands(args);
}