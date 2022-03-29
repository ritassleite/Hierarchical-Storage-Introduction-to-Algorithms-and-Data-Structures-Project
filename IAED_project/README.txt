#Hierarchical Storage System

This project was developped within the course Introduction to Algorithms and Data Structures.
The objective was to create a hierarchical storage system, similar to a regular file storage system. 

Each value to be stored (a string) is identified by a path. The interaction with the program occurs through the insertion of a command and following arguments.

##Commands
help       < prints all available commands
quit       < terminates the program
set        < adds or modifies the value to store
print      < prints all paths and values
find       < prints the stored value
list       < lists all components of a path
search     < given a value, searches for the corresponding path
delete     < deletes a path and all sub-paths

##Instructions

help
   -input: help
   -output: <command>: <description>
quit
   -input: quit
   -output: NONE
set 
   -input: set <path> <value>
   -output: NONE
print:
   -input: print
   -output: all existing paths with values associated
	      <path> <value>
find:
    -input: find <path>
    -prints value associated with <path>
list:
    -input: list <path>
    -output: all immediate components of <path>, printed in alphabetical order. If no <path> is given, print all directories from root
search:
    -input: search <value>
    -output: prints the first created path with <value> associated
delete:
    -input: delete <path>
    -output: deletes <path> and all other paths from which <path> is a sub-path. If no <path> is given, delete everything.
