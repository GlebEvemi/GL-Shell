#ifndef FUNCTIONS_H
#define FUNCTIONS_H


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <pwd.h>
#include <sys/stat.h>


#define END_CMD "end"
#define NUM_COMMANDS 7 // Number of commands
#define UNKNOWN_COMMAND NULL

typedef void(*commandFuncType) (char *);


extern const char* commandsNames[NUM_COMMANDS];

extern commandFuncType commandsPtrs[NUM_COMMANDS];

extern char* myPath;


commandFuncType getCommandHandlerByName(char* commandName);
void ls(char *);
void cd(char *);
void pwd(char *);
void rm(char *);
void createDir(char *);
void exitProgram(char *);
void clear(char *);

#endif