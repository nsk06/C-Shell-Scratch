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


int pwd(char ** args)
{
	char cwd[1111];
	getcwd(cwd,sizeof(cwd));
	printf("%s\n",cwd);
    return 2;
}