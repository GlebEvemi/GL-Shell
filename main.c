#include <stdio.h>
#include <string.h>

#define END_CMD "end"
#define NUM_COMMANDS 6
#define UNKNOWN_COMMAND NULL

typedef void(*commandFuncType) (char *);


void copy(char*);
void paste(char*);
void cut(char*);
void find(char*);
void replace(char*);
commandFuncType getCommandHandlerByName(char*);

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


int main()
{
	while (1)
	{
		char input[256];
		fgets(input, 256, stdin);

		char* commandName = strtok(input, " \n");
		char* args = strtok(NULL, "\n");

		if (strcmp(commandName, END_CMD) == 0)
		{
			break;
		}

        commandFuncType commandHandler = getCommandHandlerByName(commandName);

        if(commandHandler == UNKNOWN_COMMAND)
            continue;
        commandHandler(args);
	}

	return 0;
}



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