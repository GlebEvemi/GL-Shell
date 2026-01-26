#include"functions.h"

typedef void(*commandFuncType) (char *);


const char* commandsNames[NUM_COMMANDS] =
{
    "copy",
    "paste",
    "cut",
    "find",
    "replace",
    "find"
};

commandFuncType commandsPtrs[NUM_COMMANDS] =
{
    copy,
    paste,
    cut,
    find,
    replace,
    find
};

commandFuncType getCommandHandlerByName(char* commandName)
{
	if (commandName == NULL)
	{
		return UNKNOWN_COMMAND;
	}

	for (int i = 0; i < NUM_COMMANDS; i++)
	{
		if (strcmp(commandName, commandsNames[i]) == 0)
		{
			return commandsPtrs[i];
		}
	}

	return UNKNOWN_COMMAND;
}



void copy(char* args)
{
	printf("copy called with args [%s]\n", args);
}

void paste(char* args)
{
	printf("paste called with args [%s]\n", args);
}

void cut(char* args)
{
	printf("cut called with args [%s]\n", args);
}

void find(char* args)
{
	printf("find called with args [%s]\n", args);
}

void replace(char* args)
{
	printf("replace called with args [%s]\n", args);
}