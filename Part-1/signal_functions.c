
#include "global.h"


void  SIGINT_handler(int signal_num)
{
	int i=0;
	if(sigid){
		if(kill(sigid,SIGINT))
		{			
			return;
		}
		i =1;
	}
	if(!i){
		signal(signal_num, SIG_IGN); // The signal is ignored.
		printf("\n");
		cli();
		fflush(stdout); // Flushes the output
		signal(signal_num, SIGINT_handler); //Again it checks for signal
	}
}