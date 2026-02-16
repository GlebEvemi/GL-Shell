#include "functions.h"

commandFuncType getCommandHandlerByName(char*);

int main()
{
	//Initilize a default path as /home
	chdir("/home/lee");
	while (1)
	{
		
		char input[256];
		printf("GL-Shell@%s: ", getcwd(myPath, 256));
		fgets(input, 256, stdin);

		char* commandName = strtok(input, " \n");
		char* args = strtok(NULL, "\n");

		if (!commandName)
		continue;

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