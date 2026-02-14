#ifndef FUNCTIONS_H
#define FUNCTIONS_H



#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <pwd.h>


#define END_CMD "end"
#define NUM_COMMANDS 7
#define UNKNOWN_COMMAND NULL

typedef void(*commandFuncType) (char *);


extern const char* commandsNames[NUM_COMMANDS];

extern commandFuncType commandsPtrs[NUM_COMMANDS];


commandFuncType getCommandHandlerByName(char* commandName);
void ls(char *);
void copy(char* );
void paste(char* );
void cut(char* );
void find(char* );
void replace(char* );

#endif