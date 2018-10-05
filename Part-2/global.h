#include <stdio.h> 
#include <dirent.h>
#include <fcntl.h>
#include <pwd.h> 
#include <sys/types.h> 
#include <errno.h>
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
#define builtins 14

char dir[400];
char previous[400];
char my_builtins[14][20];
int backprocs,sigid;

void initialise_builtin();
int env_setter(char ** args);
int unsetter(char ** args);
int myjobs();
int mykj(char ** args);
int killer(char ** args);
int bring_foreground(char ** args);
int back_changer(char ** args);
int check_redirection(char ** args);
int piper(char ** args,char * fullcommand);
void pinfo(char ** args);
int execute_command(char ** args,char *fullcommand);
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
void SIGTSTP_handler(int signal_num);
void SIGQUIT_handler(int signal_num);
void myclock(char ** args);
int pipeforinbuilts(char ** args,int t);
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
	char * cmd_status;
	int is_bg;
}bgp;

bgp back_procs[100];
typedef struct fgp{
	int proc_id;
	int j_id;
	char * cmd;
	char * cmd_status;
	int is_fg;
}fgp;
char * test[100];
char * t;
int zchek;
fgp cur_fgproc;