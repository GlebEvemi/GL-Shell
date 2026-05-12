#include "functions.h"


commandFuncType getCommandHandlerByName(char *);

int getInput(char *input, size_t size);

// 1 arg = 
int main(int argc, char *argv[])
{
    //Initilize a default path as /home
    chdir("/home");
    while (1) {

        char input[256];
        myPath = getcwd(NULL, 0);
        assert(myPath != NULL && "getcwd failed");
        printf(">>%s: ", myPath);

            
        //Input handle
        if (getInput(input, sizeof(input)) != 0) {
            fprintf(stderr, "Input error\n");
            free(myPath);
            break;
        }


        char *commandName = strtok(input, " \n");
        if (!commandName) {
            free(myPath);
            continue;
        }


        char *args = strtok(NULL, "\n");


        if (strcmp(commandName, END_CMD) == 0) {
            free(myPath);
            break;
        }

        commandFuncType commandHandler =
            getCommandHandlerByName(commandName);

        if (commandHandler == UNKNOWN_COMMAND) {
            free(myPath);
            continue;
        }
        commandHandler(args);

        free(myPath);
    }

    return 0;
}




int getInput(char *input, size_t size)
{
    if (fgets(input, size, stdin) == NULL) {
        // EOF handle (Ctrl + D)
        return 1;
    }

    size_t len = strlen(input);

    if (len > 0 && input[len - 1] != '\n') {
        // Input too long, clear the buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf("Ошибка: команда слишком длинная (максимум 255 символов)\n");
        return 1;
    }
    return 0;
}
