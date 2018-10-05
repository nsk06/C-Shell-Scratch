
#include "global.h"


void pinfo(char ** args)
{
	char * p_pid;
	char  c1[500],c2[500],c3[500],c4[500];
	char path[2000];
	char ** cmd1, ** cmd2;
	int pid;
	if(args[1])
	{
		pid = atoi(args[1]);
		if(kill(pid,0))
		{
			perror("invalid");
			return ;
		}

	}
	else
	{
		pid = getpid(); 
	}
	printf("pid -- %d\n", pid);
	sprintf(c1 ,"/proc/%d/status",pid);
	FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    fp = fopen(c1,"r");
    if (fp == NULL)
        perror("error");
    int j=0;
    while ((read = getline(&line, &len, fp)) != -1) 
    {
       if(j==2)
       {
       		strcpy(c4,line);
       }
       if(j==17)
       {
       		strcpy(c2,line);
       }
       j++;
    }

    fclose(fp);
    if (line)
        free(line);
    char ** my = separguements(c4);
    char ** my1 = separguements(c2);
	sprintf(c3 ,"/proc/%d/exe",pid);
	printf("process Status -- ");
	fflush(stdout);
	printf("%s\n",my[1]);
	printf("Memory -- ");
	fflush(stdout);
	printf("%s\n",my1[1]);
	int p =readlink(c3 , path , sizeof(path));
	path[p] = '\0';
	printf("Executable Path -- %s\n", path);
	return ;
}
