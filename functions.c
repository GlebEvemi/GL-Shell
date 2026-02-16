#include"functions.h"


typedef void(*commandFuncType) (char *);

char myPath[256];

const char* commandsNames[NUM_COMMANDS] =
{
	"ls",
	"cd",
    "copy",
    "paste",
    "cut",
    "find",
    "replace",
    "find"
};

commandFuncType commandsPtrs[NUM_COMMANDS] =
{
	ls,
	cd,
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

//Prints all catalog in selected catalog
void ls(char* args){
	DIR *dir = NULL;
    struct dirent *dp = NULL;
	int count = 0;
	if ((dir = opendir (".")) == NULL) {
        perror ("Cannot open .");
        abort();
    }


    while ((dp = readdir (dir)) != NULL) {
		count++;
		printf("%-20s",dp->d_name);
		
		if(count % 4 == 0){
			putchar('\n');
		}
	}
	putchar('\n');

}

//WIP
void cd(char * args){
	chdir(args);
	if(args == "..")
	chdir("/home");
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