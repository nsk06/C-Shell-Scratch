
#include "global.h"

void myclock(char ** args)
{
	int pid,wpid,proc_status;
	int timegap,stoptime;
		if(strcmp(args[1],"-t")==0)
		{
			timegap = atoi(args[2]);
			stoptime = atoi(args[4]);
		}
		else if(strcmp(args[3],"-t")==0)
		{
			timegap = atoi(args[4]);
			stoptime = atoi(args[2]);
		}
	pid = fork();
	if (pid == 0)
	{
		char c3[500],date[400],time[400],c4[500];
		FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
		strcpy(c3 ,"/sys/class/rtc/rtc0/time");  
		strcpy(c4 ,"/sys/class/rtc/rtc0/date");
		while((stoptime-timegap)>0)
		{
		   fp = fopen(c3,"r");
			    if (fp == NULL)
			        perror("error");
			   read = getline(&line, &len, fp);
			       strcpy(time,line);
			 line = NULL;
			 len = 0;
			 fp = fopen(c4,"r");
			    if (fp == NULL)
			        perror("error");
			   read = getline(&line, &len, fp);
			       strcpy(date,line);
			       date[10]='\0';
			   printf("%s %s",date,time);
		    stoptime=stoptime-timegap;
		    if(stoptime > timegap)
		    {
		    	sleep(timegap);
		    }
		    else
		    {
		    	sleep(stoptime);
		    }
		}
	}
	else if(pid < 0)
	{
		perror("forking");
	}
	else
	{	
			wait(NULL);
	}
}