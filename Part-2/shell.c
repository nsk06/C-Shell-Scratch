
#include "global.h"


//extern int num_reminders;

void clidir()
{
	char current_dir[1111]; //current working directory
	getcwd(current_dir,sizeof(current_dir));
	int check=0;
	int i=0;
	char temp[200];

	strcpy(temp,dir); //storing in temp

	while(temp[i] != '\0')
	{
		if(current_dir[i] == temp[i])   //checking if in same
			i++;
		else
		{
			check=1;
			break;
		}
	}
	if(check)
		printf(ANSI_COLOR_GREEN "%s> " ANSI_COLOR_RESET,current_dir); //if not print the current
	else
	{
		printf(  ANSI_COLOR_GREEN "~"   ANSI_COLOR_RESET);
		while(current_dir[i]!='\0')
		{
			printf(ANSI_COLOR_GREEN "%c"  ANSI_COLOR_RESET,current_dir[i]);   //print relative to directory from which code is run
			i++;
		}
		printf(ANSI_COLOR_GREEN "> "  ANSI_COLOR_RESET);
	}
}
void cli()
{
	char buf[100];
	int user = getlogin_r(buf,sizeof(buf));
	printf( ANSI_COLOR_GREEN "<%s@" ANSI_COLOR_RESET,buf);
	/*struct utsname unameData;
	uname(&unameData);
	char sysname[10][30];
	int i=0;
	char* token = strtok(unameData.version, "-");
	while (token != NULL) {
		strcpy(sysname[i],token);
		i++;
		token = strtok(NULL, " ");
	}
	printf( ANSI_COLOR_GREEN "%s:" ANSI_COLOR_RESET,sysname[1]);*/
	char hostname[1000];
	hostname[1000] = '\0';
	gethostname(hostname,1000);
	printf(ANSI_COLOR_CYAN "%s:" ANSI_COLOR_RESET,hostname);
	clidir();
}
void takecmd()
{
	int t=0;
	
	initialise_builtin();
	while(1)
	{
		
		int i=0,j=0,k=0;
		cli();
		char **cmd;
		size_t cmdlength = 0;
		char *takecommand;
		int ch =0;
		if(getline(&takecommand,&cmdlength,stdin) == -1) //take command as input
		{
				//continue;
			//printf("hbh\n");
			ch =1;
		}  
		if (feof(stdin) && ch ==1 )  //check for exit
		{
    		//printf("\x1b[H\x1b[J"); //clearing screen
    		printf("Ctrl-D Pressed\n");
			fflush(stdout);
			fflush(stderr);
			continue;
			//exit(0);
			//exit(0);  //exit
		}
		cmd = getcommands(takecommand);
		while(cmd[i])
		{
			char x[1000] ;
			strcpy(x,cmd[i]);
			char ** args = separguements(x);
			if(strcmp(args[0],"quit")==0)
			{
				//printf("ddd\n");
				exit(0);
			}
			execute_command(args,cmd[i]);
			//printf("here\n");
			i++;
		}

		//printf("heretoo\n");
		//exit(0);
	}
}
int main()
{
	//num_reminders=0;
	if (signal(SIGINT, SIGINT_handler) == SIG_ERR)
	{
		perror("sigint");
		exit(1);
	}
	backprocs =0;
	signal(SIGCHLD, exit_handler);
	signal(SIGQUIT, SIGQUIT_handler);
	signal(SIGTSTP,SIGTSTP_handler);
	//printf("hkkk\n");
	getcwd(dir,sizeof(dir));//directory where code is run
	strcpy(previous,dir);
	takecmd();
return 0;
}