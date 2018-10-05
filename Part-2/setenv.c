#include "global.h"
int env_setter(char ** args)
{
	if(args[1] == NULL)
	{
            printf("variable not found\n");
	}
    else if(args[3] != NULL)
    {
        printf("Input less arguements\n");
    }
    else if(args[2] != NULL)
    {
        setenv(args[1],args[2],1);
    }
    else
    {
        setenv(args[1],"",1);
    }
return 1;
}