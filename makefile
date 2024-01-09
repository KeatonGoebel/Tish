# File: makefile
# Keaton Goebel, Transy University
# CS 3074, Fall 2023 
#
# makefile: Transy Interactive Shell
#

# Tish_Driver executable file 

Tish_Driver: Tish_Driver.o Tish.o Proc.o 
	g++ Tish_Driver.o Tish.o Proc.o -o Tish_Driver

# Tish_Driver object file 

Tish_Driver.o: Tish_Driver.cpp Tish.h Proc.h
	g++ -c Tish_Driver.cpp -o Tish_Driver.o

# Tish Output file 

Tish.o: Tish.cpp Tish.h Proc.h 
	g++ -c Tish.cpp -o Tish.o

# Proc Output file 

Proc.o: Proc.cpp Proc.h
	g++ -c Proc.cpp -o Proc.o

