

#include "global.h"
char ** getcommands(char * takecmd)
{
	int i=0;
	char ** buf = malloc(50*sizeof(char*));
	if(buf == NULL)
	{
		printf("Fail to allocate memory in getcommands\n");
		//exit(EXIT_FAILURE);
	}
	char* token = strtok(takecmd, ";\n");
	while (token != NULL) 
	{
		buf[i] = token;
		//printf("%s\n",buf[i]);
		i++;
		if(i >= sizeof(buf)/sizeof(char*))
		{
			buf = realloc(buf,50*sizeof(char*));
			if(buf == NULL)
			{
				printf("Fail to reallocate in getcommands\n");
				//exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL, ";\n");
	}
	buf[i]=NULL;
	return buf;
}
char ** separguements(char * cmd)
{

	int i=0;
	char ** buf = malloc(50*sizeof(char*));
	if(buf == NULL)
	{
		printf("Fail to allocate memory in separguements\n");
		//exit(EXIT_FAILURE);
	}
		char * token = strtok(cmd,command_sep);
		while (token != NULL) 
	{
		buf[i] = token;
		//printf("%s\n",buf[i]);
		i++;
		if(i >= sizeof(buf)/sizeof(char*))
		{
			buf = realloc(buf,50*sizeof(char*));
			if(buf == NULL)
			{
				printf("Fail to reallocate in separguements\n");
				//exit(EXIT_FAILURE);
			}
		}
		token = strtok(NULL,command_sep);
	}
	buf[i]=NULL;
	return buf;
}