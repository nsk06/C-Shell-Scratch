compile: shell.o sepcommand.o ls.o cd.o echo.o pwd.o remindme.o executecommand.o signal_functions.o pinfo.o clock.o
	gcc shell.o sepcommand.o ls.o cd.o echo.o pwd.o remindme.o executecommand.o signal_functions.o pinfo.o clock.o
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
clean: shell.o sepcommand.o ls.o cd.o pwd.o echo.o remindme.o executecommand.o signal_functions.o pinfo.o clock.o
	rm *.o
