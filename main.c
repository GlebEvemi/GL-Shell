#include "functions.h"

commandFuncType getCommandHandlerByName(char*);

int main()
{
	//Initilize a default path as /home
	chdir("/home");
	while (1)
	{
		
		char input[256];
		myPath = getcwd(NULL, 0);
		if (!myPath) {
    		perror("getcwd failed");
    		continue;
		}
		printf("->GL-Shell@%s: ", myPath);
		fgets(input, sizeof(input), stdin);
		char* commandName = strtok(input, " \n");
		char* args = strtok(NULL, "\n");
		if (!commandName){
			free(myPath);
			continue;
		}

		if (strcmp(commandName, END_CMD) == 0)
		{
			free(myPath);
			break;
		}

        commandFuncType commandHandler = getCommandHandlerByName(commandName);

        if(commandHandler == UNKNOWN_COMMAND){
			free(myPath);
			continue;
		}
        commandHandler(args);
		free(myPath);
	}

	return 0;
}