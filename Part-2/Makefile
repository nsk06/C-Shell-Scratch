compile: shell.o sepcommand.o ls.o cd.o echo.o pwd.o remindme.o executecommand.o signal_functions.o pinfo.o clock.o redirection.o piping.o setenv.o unset.o jobs.o kjob.o overkill.o foreground.o background.o
	gcc shell.o sepcommand.o ls.o cd.o echo.o pwd.o remindme.o executecommand.o signal_functions.o pinfo.o clock.o redirection.o piping.o setenv.o unset.o jobs.o kjob.o overkill.o foreground.o background.o
shell.o: shell.c
	gcc -c shell.c
sepcommand.o: sepcommand.c
	gcc -c sepcommand.c
ls.o: ls.c
	gcc -c ls.c
cd.o: cd.c
	gcc -c cd.c
echo.o: echo.c
	gcc -c echo.c
pwd.o: pwd.c
	gcc -c pwd.c
remindme.o: remindme.c
	gcc -c remindme.c
execute_command.o: executecommand.c
	gcc -c executecommand.c
signal_functions.o: signal_functions.c
	gcc -c signal_functions.c
pinfo.o: pinfo.c
	gcc -c pinfo.c
clock.o: clock.c
	gcc -c clock.c
redirection.o: redirection.c
	gcc -c redirection.c
piping.o: piping.c
	gcc -c piping.c
setenv.o: setenv.c
	gcc -c setenv.c
unset.o: unset.c
	gcc -c unset.c
jobs.o: jobs.c
	gcc -c jobs.c
kjob.o: kjob.c
	gcc -c kjob.c
overkill.o: overkill.c
	gcc -c overkill.c
foreground.o: foreground.c
	gcc -c foreground.c
background.o: background.c
	gcc -c background.c
clean: shell.o sepcommand.o ls.o cd.o pwd.o echo.o remindme.o executecommand.o signal_functions.o pinfo.o clock.o redirection.o piping.o setenv.o unset.o jobs.o kjob.o overkill.o foreground.o background.o
	rm *.o
