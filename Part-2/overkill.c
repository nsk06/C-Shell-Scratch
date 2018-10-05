#include "global.h"
int killer(char ** args)
{
	int i;
	for(i=1;i<=backprocs;i++)
	{
		kill(back_procs[i].proc_id,9);
	}
	return 1;
}