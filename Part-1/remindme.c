
#include "global.h"


void reminder(char ** args)
{
	int pid;
	pid = fork();
	if(pid < 0)
	{
		perror("forking");
	}
	else if(pid ==0)
	{
		remind x;
		//printf("in\n");
		x.call = clock();
		//printf("%s\n",args[1]);
		x.gap = atoi(args[1]);
		x.out = malloc(64*sizeof(char *));
		int i =0;
		if(x.out == NULL)
		{
			printf("Failed to allocate memory for reminder\n");
		}
		else
		{
			while(args[i+2])
			{
				if(i >= sizeof(x.out)/sizeof(char*))
				{
					x.out = realloc(x.out,64*sizeof(char*));
				}
				x.out[i] = args[i+2];
				i++;
			}
			x.out[i] = NULL;
		}
		sleep(x.gap);
		//num_reminders--;
		int k = 0;
		while(x.out[k])
		{
			printf("%s\n",x.out[k]);
			k++;
		}
		exit(EXIT_SUCCESS);
	}
	else
	{
		addbg_proc(pid,args);
	}
}