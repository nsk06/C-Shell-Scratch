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
#include <sys/wait.h>

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define command_sep " \t\n\r\a"
#define builtins 7

char dir[400];
char previous[400];
char my_builtins[7][20];
int backprocs,sigid;

void initialise_builtin();
void pinfo(char ** args);
int execute_command(char ** args);
char **getcommands(char * takecmd);
void clidir();
void cli();
void takecmd();
void ls(char ** args);
char ** separguements(char * cmd);
void ls_simple(int checker,char * mydir);
void lsprop(int checker,char * mydir);
int cd(char ** args);
int pwd(char ** args);
int echo(char ** args);
void exit_handler (int sig);
int restcommands(char ** args);
void addbg_proc(int pid,char ** str);
int background_checker(char ** args);
void  SIGINT_handler(int signal_num);

void myclock(char ** args);
typedef struct remind
{
	clock_t call;
	int gap;
	char ** out;
}remind;
void reminder(char ** args);
typedef struct bgp{
	int proc_id;
	int j_id;
	char * cmd;
}bgp;

bgp back_procs[100];