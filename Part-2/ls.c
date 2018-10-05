
#include "global.h"


struct dirent **namelist;
struct stat buf;
int n;

int selector(const struct dirent *namelist)
{
	if(namelist->d_name[0]=='.')
		return 0;
	else
	{
		return 1;
	}
}
int perms(mode_t perm)
{
	char ftype = '?';

	if (S_ISREG(perm)) ftype = '-';                  //regular file
	else if (S_ISLNK(perm)) ftype = 'l';			 //symbolic link
	else if (S_ISDIR(perm)) ftype = 'd';			// directory
	else if (S_ISBLK(perm)) ftype = 'b';			// block device
	else if (S_ISCHR(perm)) ftype = 'c';			// character device
	else if (S_ISFIFO(perm)) ftype = '|';			// Pipe(FIFO)
	else if (S_ISSOCK(perm)) ftype = 's';			// Socket
	printf("%c",ftype);
	int allperms = 0;
	if((perm & S_IRUSR) )
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if((perm & S_IWUSR) )
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	if((perm & S_IXUSR) )
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
	if((perm & S_IRGRP) )
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	if((perm & S_IWGRP) )
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	
	if((perm & S_IXGRP) )
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
	if((perm & S_IROTH) )
	{
		printf("r");
	}
	else
	{
		printf("-");
	}
	
	if((perm & S_IWOTH) )
	{
		printf("w");
	}
	else
	{
		printf("-");
	}
	if((perm & S_IXOTH) )
	{
		printf("x");
	}
	else
	{
		printf("-");
	}
	
		if(perm & S_IXOTH)
		{
			allperms++;
		}
	return allperms;
}
void ls_simple(int checker,char * mydir)
{
	if (checker==1)
	{
		n = scandir(mydir, &namelist, selector, alphasort);	
	}
	else if(checker==0)
	{
		n = scandir(mydir, &namelist,NULL, alphasort);
	}
	int j =0;
	    if (n == -1) 
	    {
	    	perror("scandir");
	    }

	    while (j<n) 
	    {
	        printf("%s\n", namelist[j]->d_name);
	        free(namelist[j]);
	        j++;
	    }
	     free(namelist);
	     return;
}
void lsprop(int checker,char * mydir)
{
	if (checker==1)
	{
		n = scandir(mydir, &namelist, selector, alphasort);	
	}
	else if(checker==0)
	{
		n = scandir(mydir, &namelist,NULL, alphasort);
	}
	int j =0;
			 
		    if (n == -1) 
		    {
		    	perror("scandir");
		    }

		    while (j<n) 
		    {
		        char usr[100];
		        struct group * grp;
		        struct tm time;
		        char date[200];
		        stat(namelist[j]->d_name,&buf);
		        int allperms = perms(buf.st_mode);
		        printf(" %2lu",buf.st_nlink);
		        int user = getlogin_r(usr,sizeof(usr));
		        printf(" %s",usr );
		        grp = getgrgid(buf.st_gid);
		        printf(" %s",grp->gr_name);
		        printf(" %7ld ",buf.st_size );
		        localtime_r(&buf.st_mtime, &time);
		        strftime(date, sizeof(date), "%b %d %H:%M ", &time);
				printf("  %s ", date);
				if (S_ISDIR(buf.st_mode)) // Blue color to the directories
					printf(ANSI_COLOR_BLUE "%s" ANSI_COLOR_RESET "\n",namelist[j]->d_name);
				else if(allperms)  // Green color is given if user,group and other all have 'rwx' permission
					printf(ANSI_COLOR_GREEN "%s" ANSI_COLOR_RESET "\n",namelist[j]->d_name);
				else // else file name is printed
					printf("%s\n",namelist[j]->d_name);
		        free(namelist[j]);
		        j++;
		    }
		     free(namelist);
}
void ls(char ** args)
{
	
	
    if(!args[1])
    {	
    	ls_simple(1,".");
    	return;
	}
	else if (args[1] && !args[2])
	{
		if(strcmp(args[1],"-a")==0)
		{
			ls_simple(0,".");
			return;
		}
		else if (strcmp(args[1],"-l")==0)
		{
			lsprop(1,".");
			return;
		}
		else if ((strcmp(args[1],"-la")==0)||(strcmp(args[1],"-al")==0))
		{
			lsprop(0,".");
			return;
		}
		else
		{
				char *mydir = args[1];
				ls_simple(1,mydir);
				return;
		}
	}
	else if(args[1] && args[2] &&!args[3])
	{
		if( (strcmp(args[1],"-l")==0)&&(strcmp(args[2],"-a")==0) || (strcmp(args[1],"-a")==0)&&(strcmp(args[2],"-l")==0) )
		{
			lsprop(0,".");
			return;
		}
		else if ( (strcmp(args[1],"-l")==0) && (strcmp(args[2],"-a")!=0))
		{
			ls_simple(1,args[2]);
			return;
		}
		else if ( (strcmp(args[1],"-a")==0) && (strcmp(args[2],"-l")!=0))
		{
			ls_simple(0,args[2]);
			return;
		}
		else if ( (strcmp(args[1],"-la")==0) || (strcmp(args[1],"-al")==0) )
		{
			lsprop(0,args[2]);
			return;
		}
	}
}