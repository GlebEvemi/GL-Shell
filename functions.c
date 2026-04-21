#include"functions.h"

typedef void (*commandFuncType)(char *);

char *myPath = NULL;

const char *commandsNames[NUM_COMMANDS] = {
    "ls",
    "cd",
    "pwd",
    "mkdir",
    "rm",
    "exit",
    "clear",
    "pcsearch"
};

commandFuncType commandsPtrs[NUM_COMMANDS] = {
    ls,
    cd,
    pwd,
    createDir,
    rm,
    exitProgram,
    clear,
    findComputer
};

commandFuncType getCommandHandlerByName(char *commandName)
{
    if (commandName == NULL) {
        return UNKNOWN_COMMAND;
    }

    for (int i = 0; i < NUM_COMMANDS; i++) {
        if (strcmp(commandName, commandsNames[i]) == 0) {
            return commandsPtrs[i];
        }
    }

    return UNKNOWN_COMMAND;
}

//Prints all catalog in selected catalog
void ls(char *args)
{
    DIR *dir = NULL;
    struct dirent *dp = NULL;
    int count = 0;
    if ((dir = opendir(".")) == NULL) {
        perror("Cannot open .");
        abort();
    }


    while ((dp = readdir(dir)) != NULL) {
        count++;
        printf("\t%-20s", dp->d_name);

        if (count % 4 == 0) {
            putchar('\n');
        }
    }
    putchar('\n');
    closedir(dir);

}

//Changes Directory
void cd(char *args)
{
    if (args == NULL) {
        printf("No arguments provided, so still in same directory\n");
        return;
    }
    chdir(args);
}

//Prints path
void pwd(char *args)
{
    char *path = getcwd(NULL, 0);

    if (path == NULL) {
        perror("getcwd");
        return;
    }
    printf("Path is -> %s\n", path);
    free(path);
}

//Creates directory
void createDir(char *args)
{
    if (args == NULL) {
        printf("Arguments needed\n");
        return;
    }
    if (!mkdir(args, 0755))
        printf("Created catalog -> %s\n", args);
    else
        perror("mkdir");
}

//Deletes empty dir or file
//WIP -> You delete files and empty catalogs, but
//rm should delete non-empty catalogs, several files and files by type(.c, .txt, .h etc.)
void rm(char *args)
{

    if (!remove(args))
        printf("Deleted -> %s\n", args);
    else {
        printf("Something went wrong((\n");
    }

}


void exitProgram(char *args)
{
    printf("Exiting the program\n");
    exit(0);
}

//Clears screen
void clear(char *args)
{
    printf("\ec");
}

//Basically function find a computer by hostname in args, but if args = NULL, it finds all computers
void findComputer(char *args){
    char server_url[128];
    char username[64];
    char password[64];
    puts("Enter server URL");
    if (fgets(server_url, sizeof(server_url), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return;
    }
    server_url[strcspn(server_url, "\n")] = 0;
    if(server_url[0] == '\0'){
        fprintf(stderr, "Server URL is required\n");
        return;
    }
    puts("Enter username: ");
    if (fgets(username, sizeof(username), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return;
    }
    username[strcspn(username, "\n")] = 0;
    if(username[0] == '\0'){
        fprintf(stderr, "Username is required\n");
        return;
    }
    puts("Enter password: ");
    if (fgets(password, sizeof(password), stdin) == NULL) {
        fprintf(stderr, "Invalid input\n");
        return;
    }
    password[strcspn(password, "\n")] = 0;
    if(password[0] == '\0'){
        fprintf(stderr, "Password is required\n");
        return;
    }
    if(args == NULL || strlen(args) == 0){
        puts("Finding all computers...");
        if(getAllComputers(server_url, username, password) == -1)
            fprintf(stderr, "Failed to get all computers\n");
        putchar('\n');
    }
    else{
        if(getComputerByHostname(server_url, args, username, password) == -1)
            fprintf(stderr, "Failed to get computer by hostname\n");
    }
        
}