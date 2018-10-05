#include "global.h"
int unsetter(char ** args)
{
	if(args[1] == NULL)
	{
		printf("Input a variable\n");
	}
	if(getenv(args[1])==NULL)
	{
		printf("variable not exist\n");
	}
	else if(unsetenv(args[1])== -1)
	{
		 perror("unsetenv error");
	}
	return 1;
}