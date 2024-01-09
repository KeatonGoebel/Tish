//File: Proc.h
// Keaton Goebel, Transy University
// CS 3074, Fall 2023
//
// Interface: Procedure Class
//

#ifndef    PROC_H
#define    PROC_H

#include <iostream> 
using namespace std;

class Proc {
public:

// Constructor for a Procedure class object
	Proc(void);

// Reads in a pid string and returns the current working directory of the indicated process as a string

	string cwd(string pid); 

// Reads in a pid string and returns the size of the indicated process in pages 

	int size(string pid);

// Reads in a pid string and returns the current state of the indicated process in a string 

	string pstate(string pid);

// Reads in a pid string and returns the parent pid value of the indicated process in a string 

	string parent(string pid);


};
#endif