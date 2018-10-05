#include "global.h"


int check_redirection(char ** args)
{
	int in_red_pos =-1,out_red_pos=-1,append_red_pos=-1;
	int i=0;
	
	while(args[i])
	{
		if(strcmp(args[i],"<")==0)
		{
			in_red_pos=i;
		}
		else if(strcmp(args[i],">")==0)
		{
			out_red_pos=i;
		}
		else if(strcmp(args[i],">>")==0)
		{
			append_red_pos=i;
		}
		i++;
	}
	//printf("hey\n");
	if(in_red_pos == -1&& out_red_pos == -1&& append_red_pos == -1)
	{
		return 0;
	}
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
	//close(STDIN_FILENO);
	//close(STDOUT_FILENO);
	if(in_red_pos > 0 && out_red_pos == -1 && append_red_pos == -1)
	{
		int fd = open(args[in_red_pos+1],O_RDONLY);
		if(fd == -1)
		{
			printf("No such file exists\n");
			return 1;
		}
		char * exe[50];
		int j=0;
		//printf("vff\n");
		while(strcmp(args[j],"<"))
		{
			exe[j] = args[j];
			j++;
		}
		exe[j] = NULL;
		dup2(fd,STDIN_FILENO);
		if(pipeforinbuilts(exe,0)==1)
		{
				int x = fork();
				if(x==0)
				{
					//dup2(pip[1],STDOUT_FILENO);
					pipeforinbuilts(exe,1);
					exit(0);
				}
			else{
					wait(NULL);
						dup2(in,STDIN_FILENO);
		dup2(out,STDOUT_FILENO);
		close(in);
		close(out);
			}	
		}
		else
		{
			int pid = fork();
			if(pid == 0)
			{
				//printf("yo\n");
				//exit(0);
				execvp(exe[0],exe);	
			}
			else
			{
				wait(NULL);
				//rintf("f\n");
				dup2(in,STDIN_FILENO);
			dup2(out,STDOUT_FILENO);
			close(in);
			close(out);
			}
		}
		close(fd);
	}
	else if(out_red_pos > 0)
	{
		int fd = open(args[out_red_pos+1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
		//printf("heyyyyy\n");
		char * exe[50];
		int f2;
		if(in_red_pos > 0)
		{
				int j=0;
			while(strcmp(args[j],"<"))
			{
				exe[j] = args[j];
				j++;
			}
			exe[j] = NULL;
			f2 = open(args[in_red_pos+1],O_RDONLY);
			if(f2 == -1)
			{
				perror("No such file exists");
				return 1;
			}
			dup2(f2,STDIN_FILENO);
		}
		else
		{
			//printf("hey there\n");
			int j=0;
			while(strcmp(args[j],">"))
			{
				exe[j] = args[j];
				j++;
			}
			exe[j] = NULL;	
		}

		dup2(fd,STDOUT_FILENO);
		if(pipeforinbuilts(exe,0)==1)
		{
				int x = fork();
				if(x==0)
				{
					//dup2(pip[1],STDOUT_FILENO);
					pipeforinbuilts(exe,1);
					exit(0);
				}
			else{
					wait(NULL);
						dup2(in,STDIN_FILENO);
		dup2(out,STDOUT_FILENO);
		close(in);
		close(out);
			}	
		}
		else
		{
			int pid = fork();
			if(pid == 0)
			{
				//printf("yooo\n");	
				execvp(exe[0],exe);	
			}
			else
			{
				wait(NULL);
				dup2(in,STDIN_FILENO);
			dup2(out,STDOUT_FILENO);
			close(in);
			close(out);
			}
		}
		close(fd);
		if(in_red_pos > 0)
			close(f2);
	}
	else if(append_red_pos > 0)
	{
		int fd = open(args[append_red_pos+1],O_WRONLY | O_CREAT | O_APPEND, 0644);
		int f2;
		char * exe[50];
		if(in_red_pos > 0)
		{
				int j=0;
			while(strcmp(args[j],"<"))
			{
				exe[j] = args[j];
				j++;
			}
			exe[j] = NULL;
			f2 = open(args[in_red_pos+1],O_RDONLY);
			if(f2 == -1)
			{
				perror("No such file exists");
				return 1;
			}
			dup2(f2,STDIN_FILENO);
		}
		else
		{
			int j=0;
			//printf("vff\n");
			while(strcmp(args[j],">>"))
			{
				exe[j] = args[j];
				j++;
			}
			exe[j] = NULL;
		}	
		dup2(fd,STDOUT_FILENO);
		if(pipeforinbuilts(exe,0)==1)
		{
				int x = fork();
				if(x==0)
				{
					//dup2(pip[1],STDOUT_FILENO);
					pipeforinbuilts(exe,1);
					exit(0);
				}
			else{
					wait(NULL);
						dup2(in,STDIN_FILENO);
		dup2(out,STDOUT_FILENO);
		close(in);
		close(out);
			}	
		}
		else
		{
			int pid = fork();
			if(pid == 0)
			{
				
				execvp(exe[0],exe);	
			}
			else
			{
				wait(NULL);
				dup2(in,STDIN_FILENO);
			dup2(out,STDOUT_FILENO);
			close(in);
			close(out);
			}
		}
		close(fd);
		if(in_red_pos > 0)
			close(f2);
	}
	return 1;
}