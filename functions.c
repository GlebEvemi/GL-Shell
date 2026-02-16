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
    "find",
	"clear"
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
    find,
	clear
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
}



void copy(char* args)
{
	printf("Unfortunately for now I don't know this command)))\n");
}

void paste(char* args)
{
	printf("Unfortunately for now I don't know this command)))\n");
}

void cut(char* args)
{
	printf("Unfortunately for now I don't know this command)))\n");
}

void find(char* args)
{
	printf("Unfortunately for now I don't know this command)))\n");
}

void replace(char* args)
{
	printf("Unfortunately for now I don't know this command)))\n");
}


void clear(char *args){
	printf("Unfortunately for now I don't know this command)))\n");
}