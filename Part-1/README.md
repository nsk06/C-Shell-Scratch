This is my basic replica of bash written in c.
* To compile: make 
* To run: ./a.out 
* Clean: make clean 
Incase the prompt doesn't appear after a background process is started/terminated or for any other reason, press ENTER.
Features implemented 
1) A shell prompt of the form: <username@hostname:curr_dir> with path relative to home 
2) Semi-colon (;) separated commands 
3) & to run a process in background 
4) Some built in commands like cd ,echo ,ls , and pwd re-implemented 
5) Type quit to exit the shell 
6) Implements foreground and background processes 
7) Process name and id printed when background process terminates 
8) Type pinfo in the prompt to print: pid, process, status, memory and executable path (on Linux machines) 
9) Ctrl-C to terminate a process 
10) Ctrl-D to exit the shell/denote EOF 
 **Some bash commands are implemented and the rest are invoked using execvp**

 ***STANDOUT FEATURE:As differ from original shell this prints completion of background process asynchronously without waiting for some command to execute
 Bonus:
 1)remindme command to set print reminders.
 To run type remindme n statement(it will print statement after n seconds)
 
 2)clock command to display dynamic date and time.
 To run type clock -t k -n x(it will print date and time after gap of k seconds and will stop after x seconds)

Files in Directory:-

1) shell.c :- contains the main ,prompt ,print_prompt function . main function calls the prompt function ,which further handles the futher implementation.

2) ls.c  :- contains ls ,lsl ,get_perms function. It handles ls command .

3) echo.c :- contains echo function . It handles echo command.

4) cd.c :- contains cd function . It handles cd command.

5) global.h :- contains all the definitions of functions and the definitions of the constants to be used.

6) pinfo.c :- contains pinfo function. It prints the process related info of our shell program.

7) pwd.c   :- contains pwd function . It handles pwd command.

9) sepcommand.c  :- conatains split_line_fxn , split_cmd_fxn function . It splits the commands entered so that they can be executed.

10)executecommand.c :- contains launch_func ,child process ,background_fxn , back_process, execute_func function.

11)signal_functions.c :- contains signal handlers for asynchronous interrupts

12)remindme.c :- contains remindme execution.

13)clock.c :- contains clock execution.