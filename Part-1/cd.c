#include <stdio.h> 
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h> 
#include <sys/types.h> 
#include <unistd.h> 
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <sys/dir.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <grp.h>
#include <time.h>
#include <locale.h>
#include <langinfo.h>
#include <stdint.h>
#include <sys/utsname.h>
#include "global.h"

/*
chdir() changes the current working directory of the calling process to the directory specified in path.
chdir  On success, zero is returned.  On error, -1 is returned, and errno is set appropriately.
perror prints a description for a system error code or for a storage engine (table handler) error code.
The chdir command works, but only inside your program. Once you exit it, you're back to the parent shell current directory.

*/

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
			chdir(args[1]);
			return 1;
		}
	}
}