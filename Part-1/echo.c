
#include "global.h"

int echo(char ** args)
{
	if(args[1]==NULL)
	{
		printf("\n");
		return 1;
	}
		int i=1;
		while(args[i])
		{
			printf("%s ",args[i]);
			i++;
		}
		printf("\n");
}