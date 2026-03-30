#include "functions.h"

commandFuncType getCommandHandlerByName(char *);

int getInput(char *input);

int main()
{
    //Initilize a default path as /home
    chdir("/home");
    while (1) {

        char input[256];
        myPath = getcwd(NULL, 0);
        assert(myPath != NULL && "getcwd failed");
        printf("->GL-Shell@%s: ", myPath);


        //Input handle
        if (getInput(input)) {
            perror("Input error");
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




int getInput(char *input)
{
    if (fgets(input, sizeof(input), stdin) == NULL) {
        // EOF handle (Ctrl + D)
        return 1;
    }

    size_t len = strlen(input);
    if (len > 0 && input[len - 1] != '\n') {
        // Input too long, clear the buffer
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        printf
            ("Ошибка: команда слишком длинная (максимум 255 символов)\n");
        return 1;
    }
    return 0;
}
