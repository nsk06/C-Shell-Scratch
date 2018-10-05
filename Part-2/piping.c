#include "global.h"
int pipeforinbuilts(char ** args,int t)
{
	for(int i=0;i<builtins;i++)
	{
		if(strcmp(args[0],my_builtins[i])==0)
		{
			if(strcmp(args[0],"ls")==0)
			{
				if(t>0)
					ls(args);
				return 1;
			}
			else if(strcmp(args[0],"cd")==0)
			{
				if(t>0)
				cd(args);
				return 1;
			}
			else if(strcmp(args[0],"pwd")==0)
			{
				if(t>0)
				pwd(args);
				return 1;
			}
			else if(strcmp(args[0],"remindme")==0)
			{
				//printf("yoo\n");
				if(t>0)
				reminder(args);
				return 1;
				//num_reminders++;	 
			}
			else if(strcmp(args[0],"pinfo")==0)
			{
				if(t>0)
				pinfo(args);
				return 1;
			}
			else if(strcmp(args[0],"clock")==0)
			{
				if(t>0)
				myclock(args);
				return 1;
			}
			else if(strcmp(args[0],"echo")==0)
			{
				if(t>0)
				echo(args);
				return 1;
			}
			else if(strcmp(args[0],"setenv")==0)
			{
				if(t>0)
				env_setter(args);
				return 1;
			}
			else if(strcmp(args[0],"unsetenv")==0)
			{
				if(t>0)
				unsetter(args);
				return 1;
			}
			else if(strcmp(args[0],"jobs")==0)
			{
				if(t>0)
				myjobs(args);
				return 1;
			}
			else if(strcmp(args[0],"kjob")==0)
			{
				if(t>0)
				mykj(args);
				return 1;
			}
			else if(strcmp(args[0],"overkill")==0)
			{
				if(t>0)
				killer(args);
				return 1;
			}
			else if(strcmp(args[0],"fg")==0)
			{
				if(t>0)
				bring_foreground(args);
				return 1;
			}
			else if(strcmp(args[0],"bg")==0)
			{
				if(t>0)
				back_changer(args);
				return 1;
			}
		}
	}
	if(t==2)
	{
		//printf("herer\n");
		return restcommands(args);
	}
	return 0;
}
int piper(char ** args,char * fullcommand)
{
	//printf("heya\n");
	//printf("%s\n",fullcommand);
	int in = dup(STDIN_FILENO);
	int out = dup(STDOUT_FILENO);
	int pipe_pos;	
	int pid = fork();
	if(pid < 0)
	{
		perror("forking in piper");
		return 0;
	}
	else if(pid == 0)
	{
		int i=0;
		char ** buf = malloc(50*sizeof(char*));
		if(buf == NULL)
		{
			printf("Fail to allocate memory in pipeseparator\n");
			return 0;
			//exit(EXIT_FAILURE);
		}
		char* token = strtok(fullcommand, "|");
		while (token != NULL) 
		{
			buf[i] = token;
			//printf("%s\n",buf[i]);
			i++;
			if(i >= sizeof(buf)/sizeof(char*))
			{
				buf = realloc(buf,50*sizeof(char*));
				if(buf == NULL)
				{
					printf("Fail to reallocate in pipeseparator\n");
					return 0;
					//exit(EXIT_FAILURE);
				}
			}
			token = strtok(NULL, "|");
		}
		buf[i]=NULL;
		int pipecommands = i-1;
		i=0;
		int pipelen = pipecommands;
		for(i=0;i<pipelen;i++)
		{
			int in_red_pos =-1,out_red_pos=-1,append_red_pos=-1;
			int j=0;
			char **myargs = separguements(buf[i]);
			while(myargs[j])
			{
				if(strcmp(myargs[j],"<")==0)
				{
					in_red_pos=j;
				}
				else if(strcmp(myargs[j],">")==0)
				{
					out_red_pos=j;
				}
				else if(strcmp(myargs[j],">>")==0)
				{
					append_red_pos=j;
				}
				j++;
			}
			if(out_red_pos >0)
			{
				if(in_red_pos > 0)
				{
					int fd=open(myargs[in_red_pos+1],O_RDONLY);
					dup2(fd,STDIN_FILENO);
				//close(fd);
					return 1;
				}				
				else
					;
			}
			else if(append_red_pos > 0)
			{
				if(in_red_pos > 0)
				{
					int fd=open(myargs[in_red_pos+1],O_RDONLY);
					dup2(fd,STDIN_FILENO);
				//close(fd);
					return 1;
				}				
				else
					;
			}
			else if(out_red_pos == -1 && append_red_pos == -1)
			{
				//printf("fergregregreg\n");
				int pip[2];
					pipe(pip);
					int x =0;
				//dup2(pip[1],STDOUT_FILENO);
				if(in_red_pos == -1)
				{
					//printf("hiiii\n");
					if(pipeforinbuilts(myargs,0)==1)
					{
						x = fork();
						if(x==0)
						{
							dup2(pip[1],STDOUT_FILENO);
							pipeforinbuilts(myargs,1);
							exit(0);
						}
						else{
							wait(NULL);
						}	
					}
					else
					{
						//printf("yooooooo\n");
						int pid = fork();
						if(pid == 0)
						{
							dup2(pip[1],STDOUT_FILENO);
								execvp(myargs[0],myargs);
						}
						else
						{
								wait(NULL);
						}
					}
					
				}
				else
				{
					
					int fd = open(args[in_red_pos+1],O_RDONLY);
					if(fd == -1)
					{
						printf("No such file exists\n");
						return 0;
					}
					char * exe[50];
					int j=0;
					//printf("vff\n");
					while(strcmp(myargs[j],"<"))
					{
						exe[j] = args[j];
						j++;
					}
					exe[j] = NULL;
					dup2(fd,STDIN_FILENO);
					if(pipeforinbuilts(myargs,0)==1)
					{
						x = fork();
						if(x==0)
						{
							dup2(pip[1],STDOUT_FILENO);
							pipeforinbuilts(myargs,1);
							exit(0);
						}
						else{
							wait(NULL);
						}	
					}
					else
					{
						int pid = fork();
						if(pid == 0)
						{
							dup2(pip[1],STDOUT_FILENO);
							execvp(exe[0],exe);	
						}
						else
						{
							wait(NULL);
						}
					}
					close(fd);
				}
				dup2(pip[0], STDIN_FILENO);
				close(pip[1]);
			}
		}
		//printf("hi there\n");
		char **myargs2 = separguements(buf[i]);
		int in_red_pos = -1;
		int out_red_pos = -1;
		int append_red_pos = -1;
		int j=0;
		i=0;
		while(myargs2[i])
		{
			//printf("fffff\n");
			//printf("%s\n",myargs2[i]);
			if(strcmp(myargs2[i],">") == 0)
			{
				out_red_pos = i;
			}
			if(strcmp(myargs2[i],">>") == 0)
			{
				append_red_pos= i;
			}
			if(strcmp(myargs2[i],"<") == 0)
			{
				in_red_pos = i;
			}
			i++;
		}
		if(out_red_pos > 0)
		{
			//printf("hi\n");
			int fd = open(myargs2[out_red_pos+1],O_WRONLY | O_CREAT | O_TRUNC, 0644);
			//printf("heyyyyy\n");
			char * exe[50];
			int f2;
			if(in_red_pos > 0)
			{
					int j=0;
				while(strcmp(myargs2[j],"<"))
				{
					exe[j] = myargs2[j];
					j++;
				}
				exe[j] = NULL;
				f2 = open(myargs2[in_red_pos+1],O_RDONLY);
				if(f2 == -1)
				{
					perror("No such file exists");
					return 0;
				}
				dup2(f2,STDIN_FILENO);
			}
			else
			{
				//printf("hey there\n");
				int j=0;
				while(strcmp(myargs2[j],">"))
				{
					exe[j] = myargs2[j];
					j++;
				}
				exe[j] = NULL;	
			}

			dup2(fd,STDOUT_FILENO);
			if(pipeforinbuilts(myargs2,0)==1)
					{
						int x = fork();
						if(x==0)
						{
							//dup2(pip[1],STDOUT_FILENO);
							pipeforinbuilts(myargs2,1);
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
			//printf("ok\n");
			int fd = open(myargs2[append_red_pos+1],O_WRONLY | O_CREAT | O_APPEND, 0644);
			int f2;
			char * exe[50];
			if(in_red_pos > 0)
			{
					int j=0;
				while(strcmp(myargs2[j],"<"))
				{
					exe[j] = args[j];
					j++;
				}
				exe[j] = NULL;
				f2 = open(myargs2[in_red_pos+1],O_RDONLY);
				if(f2 == -1)
				{
					perror("No such file exists");
					return 0;
				}
				dup2(f2,STDIN_FILENO);
			}
			else
			{
				int j=0;
				//printf("vff\n");
				while(strcmp(myargs2[j],">>"))
				{
					exe[j] = myargs2[j];
					j++;
				}
				exe[j] = NULL;
			}	
			dup2(fd,STDOUT_FILENO);
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
			close(fd);
			if(in_red_pos > 0)
				close(f2);
	}
	else if(out_red_pos == -1 && append_red_pos == -1)
	{
		//printf("bye\n");
		if(in_red_pos == -1)
		{
			// //printf("yo boi\n");
			// if(pipeforinbuilts(myargs2,0)==0)
			// 		{
			// 			//x = fork();
			// 			//if(x==0)
			// 			//{
			// 				//dup2(pip[1],STDOUT_FILENO);
			// 				pipeforinbuilts(myargs2,1);
			// 				//exit(0);
			// 			//}
			// 		}
			// else
			// {
			// if(execvp(myargs2[0],myargs2) == -1)
			// 	kill(getpid(),SIGTERM);
			// }
			pipeforinbuilts(myargs2,2);
			exit(0);
		}
		else
		{
				int fd = open(myargs2[in_red_pos+1],O_RDONLY);
			if(fd == -1)
			{
				printf("No such file exists\n");
				return 0;
			}
			char * exe[50];
			int j=0;
			//printf("vff\n");
			while(strcmp(myargs2[j],"<"))
			{
				exe[j] = myargs2[j];
				j++;
			}
			exe[j] = NULL;
			dup2(fd,STDIN_FILENO);
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
			close(fd);
		}
	}
		exit(0);
	}

	else
	{
		wait(NULL);
		dup2(in,STDIN_FILENO);
		dup2(out,STDOUT_FILENO);
		return 1;
	}
}