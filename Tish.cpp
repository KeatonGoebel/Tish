// File: Tish.cpp
// Keaton Goebel, Transy University
// CS 3074, Fall 2023
//
// Implementation: Transy Interactive Shell
//

#include "Tish.h"
#include "Proc.h"
#include <iostream>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
using namespace std;

Tish::Tish (void){

	string command;
	string lastCom;
	int lineCount = 0;
	Proc proc; 

	// OpenShellT is equal to the current time upon opening the shell
	int openShellT = time(NULL);

	cout << ">: ";
	getline(cin,command);

	while(command != "exit") {
		
		// flag exists to check if the input is an internal command or if Tish should check if it is an external command
		bool commandExists = false;

		// if command is lastcom, then command is changed to lastCom and Tish executes as if the last command was inputted 
		if(command == "lastcom"){

			command = lastCom;
			commandExists = true;
		}

		if(command.substr(0,4) == "help"){
			help(command);
			commandExists = true;
		}

		if(command == "tishtime"){
			commandExists = true;

			// CommandT is equal to the current time upon excuting the tishtime command. Tishtime is equal to the
			// exact time the user has been in the shell 
			int commandT = time(NULL);
			int tishTime = commandT - openShellT;

			if(tishTime >= 60){
				cout << "The Shell has been running for " << tishTime / 60
				<< " minute(s) and " << tishTime  % 60 << " second(s)" << endl;
			}
			else 
				cout << "The Shell has been running for " << tishTime
				<< " seconds" << endl;
		}

		if(command == "lines"){
			cout<< lineCount << " lines have been inputted" << endl;
			commandExists = true;
		}	

		if(command == "maxprocesses"){
			cout << "The maximum number of child processes is " << sysconf(_SC_CHILD_MAX) << endl;
			commandExists = true;
		}

		if(command == "pagesize"){
			cout << "The system page size in bytes is " << sysconf(_SC_PAGESIZE) << endl;
			commandExists = true;
		}

		if(command.substr(0,3) == "cwd" && command.length() > 4){
			string pidString = command.substr(4);
			
			char pidChar[pidString.length()];
			for(int i = 0; i < pidString.length(); i++){
				pidChar[i] = pidString[i];
			} 

			// If one of the elements of pidstring is not a number, an error string is printed out and the validPid flag is set to false 
			bool validPid = true;
			for(int i = 0; i < pidString.length(); i++){
				if(isdigit(pidChar[i]) == false){
					cout << "Invalid PID entered, cannot return working directory" << endl;
					validPid = false;
					commandExists = true;
					break;
				}
			} 
			if(validPid == true){
				cout << "The current working directory of the process is " << endl << 
				proc.cwd(pidString) << endl;
				commandExists = true;
			}
		}

		if(command.substr(0,4) == "size" && command.length() > 5){
			string pidString = command.substr(5);
			
			char pidChar[pidString.length()];
			for(int i = 0; i < pidString.length(); i++){
				pidChar[i] = pidString[i];
			} 
 
			bool validPid = true;
			for(int i = 0; i < pidString.length(); i++){
				if(isdigit(pidChar[i]) == false){
					cout << "Invalid PID entered, cannot return working directory" << endl;
					validPid = false;
					commandExists = true;
					break;
				}
			} 
			if(validPid == true){
				cout << "the size of the process in pages is " << endl << 
				proc.size(pidString) << endl;
				commandExists = true;
			}
		}

		if(command.substr(0,6) == "pstate" && command.length() > 7){
			string pidString = command.substr(7);
			
			char pidChar[pidString.length()];
			for(int i = 0; i < pidString.length(); i++){
				pidChar[i] = pidString[i];
			} 

			bool validPid = true;
			for(int i = 0; i < pidString.length(); i++){
				if(isdigit(pidChar[i]) == false){
					cout << "Invalid PID entered, cannot return working directory" << endl;
					validPid = false;
					commandExists = true;
					break;
				}
			} 
			if(validPid == true){
				cout << "The current state of the process is " << endl << 
				proc.pstate(pidString) << endl;
				commandExists = true;
			}
		}

		if(command.substr(0,6) == "parent" && command.length() > 7){
			string pidString = command.substr(7);
			
			char pidChar[pidString.length()];
			for(int i = 0; i < pidString.length(); i++){
				pidChar[i] = pidString[i];
			} 

			bool validPid = true;
			for(int i = 0; i < pidString.length(); i++){
				if(isdigit(pidChar[i]) == false){
					cout << "Invalid PID entered, cannot return working directory" << endl;
					validPid = false;
					commandExists = true;
					break;
				}
			} 
			if(validPid == true){
				cout << "The parent pid of the indicated process is " << endl << 
				proc.parent(pidString) << endl;
				commandExists = true;
			}
		}

		if(commandExists == false){
			ExecCommand(command);
		}

		lastCom = command;
		lineCount ++;
		cout << ">: ";
		getline(cin,command);
	}

}

void Tish::ExecCommand(string command){

	pid_t pid = fork();
	if(pid == -1){
		cout << "Error: Fork Failed" << endl;
	}
	else if(pid == 0){

		char *cmd = strdup(command.c_str());
		int execResult = execl("/bin/sh", "/bin/sh", "-c", cmd, NULL);
	
		if (execResult == -1 ){
			cout << "Error: Exec Failed" << endl;
		}
	}

	else {
		wait(NULL);
	}
}

void Tish::help(string command){

	bool helpExists = false; 
	if(commandLine == "help"){
		cout << endl << "The help command prints out information about every command and how to execute them." << endl 
		<< "The format for a help command is" << endl << ">:help <commandName>" << endl;
		return;
		helpExists = true;
	}

	// At this point there must be something inputted after "help," therefore the help and white space
	// is removed from commandLine and commandLine is now equal to the command inputted after help 

	commandLine = commandLine.substr(5);

	if (commandLine == "exit"){
		cout << "The exit command exits the Shell" << endl 
		<< "The format for the exit command is" << endl << ">:exit" << endl;
		helpExists = true;
	}

	if (commandLine == "tishtime"){
		cout << "The tishtime command prints out how long the shell has been running in seconds and minutes if applicable" << endl 
		<< "The format for the tishtime command is" << endl << ">:tishtime" << endl;
		helpExists = true;
	}

	if (commandLine == "lines"){
		cout << "The lines command shows how many lines have been inputted by the user.";
		cout << "A line is determined by every press of the enter/return key. Therefore using the lines command also counts as a line" << endl; 
		cout << "The format for the lines command is" << endl << ">:lines" << endl;
		helpExists = true;
	}

	if(commandLine == "lastcom"){
		cout << "The lastcom command executes the last command again. It can be used multiple times to repeat the last commmand." << endl 
		<< "The format for the lastcom command is" << endl << ">:lastcom" << endl;
		helpExists = true;
	}

	if(commandLine == "maxprocesses"){
		cout << "The maxprocesses command prints out the maximum number of child processes per user id using the sysconf commands" << endl 
		<< "The format for the maxprocesses command is" << endl<< ">:maxprocesses" << endl;
		helpExists = true;
	}

	if(commandLine == "pagesize"){
		cout << "The pagesize command prints out the system page size in bytes using the sysconf commands" << endl 
		<< "The format for the pagesize command is" << endl<< ">:pagesize" << endl;
		helpExists = true;
	}

	if(commandLine == "cwd"){
		cout << "The cwd command prints out the current working directory of the indicated process. This command is dependent on the proc file system to return without error." << endl 
		<< "The format for the cwd command is" << endl<< ">:cwd pid" << endl;
		helpExists = true;
		}

	if(commandLine == "size"){
		cout << "The size command prints out the size of the process in pages, and there are two kilobytes per page. This command is dependent on the proc file system to return without error." << endl 
		<< "The format for the size command is" << endl<< ">:size pid" << endl;
		helpExists = true;
		}

	if(commandLine == "pstate"){
		cout << "The pstate command prints out the current state of the process. This command is dependent on the proc file system to return without error." << endl 
		<< "The format for the pstate pid command is" << endl<< ">:pstate pid" << endl;
		helpExists = true;
		}

	if(commandLine == "parent"){
		cout << "The parent command prints out the parent pid of the process. This command is dependent on the proc file system to return without error." << endl 
		<< "The format for the parent command is" << endl<< ">:parent pid" << endl;
		helpExists = true;
		}

	// Printing something to the screen even if none of the inputted strings equal commandLine, the user likely mistyped a command or is unsure if it exists on the machine 

	if(helpExists == false){
		cout << "No help topics match " << commandLine << endl; 
	}

}
