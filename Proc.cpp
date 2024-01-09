//File: Proc.cpp
// Keaton Goebel, Transy University
// CS 3074, Fall 2023 
//
// Implementation: Procedure Class
//

#include "Proc.h"
#include <iostream>
#include <unistd.h>
#include <fstream>
using namespace std;

Proc::Proc(void){
}

string Proc::cwd(string pid){
	
	// Creating a filepath to the proc file system and opening the link with readlink.
	// This assumes there will not be a symbolic link longer than 10000 and 9999 is used
	// on line 29 to avoid segmentation faults

	string cwdPath = "/proc/" + pid + "/cwd";

	char pathBuff[10000];
	int pathSize = readlink(cwdPath.c_str(),pathBuff,9999);

	if(pathSize == -1){
		return "Error";
	}
	else{
	string cwd;
	for(int i = 0; i < pathSize; i++){
		cwd += pathBuff[i];
	}
	return cwd;
	}

}

int Proc::size(string pid){

	// Creating a filepath to the proc file system and opening it for reading with the ifsteam command

	string statusPath = "/proc/" + pid + "/status";
	ifstream file(statusPath.c_str());

	// Returns -1 if the file fails to open, otherwise searches through status line by looking for "VmSize," which holds the virtual memory of the process
	if(!file){
		return -1;
	}
	else {

		string line;
		while(getline(file,line)){

			if(line.substr(0,7) == "VmSize:"){

				// Parsing the string to grab the integers after VmSize. Size is mesured in kilobytes 
				// and divides size by page size to get size in number of pages 

				int size = stoi(line.substr(7));
				return size/sysconf(_SC_PAGESIZE);
			}
		}
		return -1;
	}
}

string Proc::pstate(string pid){

	string statusPath = "/proc/" + pid + "/status";
	ifstream file(statusPath.c_str());

	if(!file){
		return "Error";
	}
	else {

		string line;
		while(getline(file,line)){

			if(line.substr(0,6) == "State:"){ //Parsing out the state
				return line.substr(7);
			}
		}
		return "Error";
	}
}

string Proc::parent(string pid){

	string statusPath = "/proc/" + pid + "/status";
	ifstream file(statusPath.c_str());

	if(!file){
		return "Error";
	}
	else {

		string line;
		while(getline(file,line)){

			//Parsing out the parent pid value
			if(line.substr(0,5) == "PPid:"){
				return line.substr(6);
			}
		}
		return "Error";
	}
}