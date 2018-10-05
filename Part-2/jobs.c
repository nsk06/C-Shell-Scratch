#include "global.h"
int myjobs()
{
	int i;
	//printf("%d\n",backprocs);
	for(i=1;i<=backprocs;i++)
	{
		if(back_procs[i].is_bg == 1)
		{
			printf("[%d]\t%s  with pid \t%d \n",back_procs[i].j_id,back_procs[i].cmd_status,back_procs[i].proc_id);
		}
	}
	return 1;
}