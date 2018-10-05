
#include "global.h"
int cd(char ** args)
{
	char c[400];
getcwd(c,sizeof(c));
char run[400];
strcpy(run,dir);
	if(!args[1])
	{
		chdir(dir);
		return 2;
	}
	else if(args[1])
	{
		if(strcmp(args[1],"~")==0)
		{
			chdir(dir);
			return 1;
		}
		else if((strcmp(args[1],".")==0))
		{
			chdir(c);
			return 1;
		}
		else if((strcmp(args[1],"-")==0))
		{
			chdir(previous);
			printf("%s\n",previous);
			strcpy(previous,c);
			return 1;
		}
		else
		{
			DIR* dir = opendir(args[1]);
				if (dir)
				{
				    chdir(args[1]);
				}
				else if (ENOENT == errno)
				{
				    printf("No such directory\n");
				}
			
			return 1;
		}
	}
}