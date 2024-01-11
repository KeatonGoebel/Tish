# Tish
Tish is a C++ implementation of a command-line interface program. It was written in my fall semester at Transylvania University, and stands for Transy Interactive Shell. The project acts as an extension to the command-line interface on the user's computer. Users can run the Tish program and then have access to all new commands from the terminal. For example, when Tish is running, the user will see ">:" indicating that Tish is awaiting input from the user. Users must input Tish commands exactly as they are with no spaces in the terminal. However, some Tish commands depend on the Proc file system, meaning they will only work on certain systems. The commands that depend on the Proc file system are explained below. If the user types a command into Tish that is not programmed into the system, Tish will attempt to fork and exec the command and run it from the shell normally on the system. This technique is important because users can execute all commands programmed into Tish along with all other commands in the command line interface by default. 
## Tish Commands 

* help: The help command prints out information about every command and how to execute them.

* exit: The exit command exits the Shell

* tishtime: The tishtime command prints out how long the shell has been running in seconds and minutes if applicable

* lines: The lines command shows how many lines have been inputted by the user.A line is determined by every press of the enter/return key. Therefore using the lines command also counts as a line

* lastcom: The lastcom command executes the last command again. It can be used multiple times to repeat the last commmand.

* maxprocesses: The maxprocesses command prints out the maximum number of child processes per user id using the sysconf commands

* pagesize: The pagesize command prints out the system page size in bytes using the sysconf commands

* cwd: The cwd command prints out the current working directory of the indicated process. This command is dependent on the proc file system to return without error. If there is an error, the output of cwd will be "Error."
The format of the cwd command is ">:cwd pid" 

* size: The size command prints out the size of the process in pages, and there are two kilobytes per page. This command is dependent on the proc file system to return without error. If there is an error, the output of cwd will be "-1."
The format for the size command is ">:size pid"

* pstate: The pstate command prints out the current state of the process. This command is dependent on the proc file system to return without error. If there is an error, the output of cwd will be "Error."
The format for the pstate pid command is ">:pstate pid"

* parent: The parent command prints out the parent pid of the process. This command is dependent on the proc file system to return without error. If there is an error, the output of cwd will be "Error."
The format for the parent command is ">:parent pid"

### Tish Example Intputs and Outputs 
Executing Internal Commands: 
```
>:tishtime
The Shell has been running for 22 minute(s) and 18 second(s)
>:lines
18 lines have been inputted
```
Executing External Commands:
```
>:pwd
/Users/keatongoebel/Desktop/Tish
>:ls
Proc.cpp	Proc.o		Tish.h		Tish_Driver	Tish_Driver.o
Proc.h		Tish.cpp	Tish.o		Tish_Driver.cpp	makefile
```

