//File: Tish.h
// Keaton Goebel, Transy U 
// CS 3074, Fall 2023
// 
// Interface: Transy Interactive Shell
//

#ifndef    TISH_H
#define    TISH_H

#include <iostream> 
using namespace std;

class Tish {
public:

// Constuctor: When a Tish object is created it prompts for input and tests it for commands, its tests for both
// embedded internal commands and external commands outside of the CLI

	Tish(void);

// ExecCommand reads in a string for the command and creates a new process to handle the executing of external commands outside the Tish CLI  

	void ExecCommand(string command);

// Help command reads in a string for the command and returns information about every Tish command and their formats

	void help(string command);

};
#endif