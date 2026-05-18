# GL-Shell

An interactive command shell written in C with support for basic file operations and integration with a remote server for computer discovery.

## Description

GL-Shell is a simplified implementation of a Unix shell that allows you to:
- Navigate the file system
- Perform basic operations with files and directories
- Connect to a server and search for computers by hostname

The project is developed in C23 using libcurl for HTTP requests.

## Requirements

- GCC or Clang (C23 support)
- CMake 3.15+
- libcurl-dev
- POSIX-compatible OS (Linux, macOS, etc.)

## Installation and Build

### Linux/macOS

1. Install dependencies:
   ```bash
   # Ubuntu/Debian
   sudo apt-get install cmake libcurl4-openssl-dev

   # macOS
   brew install cmake curl
   ```

2. Build the project:
   ```bash
   mkdir -p build
   cd build
   cmake ..
   make
   ```

3. Run the application:
   ```bash
   ./glshell
   ```

## Commands

### Built-in Shell Commands

| Command | Description | Example |
|---------|-------------|---------|
| `ls` | List contents of the current directory | `ls` |
| `cd` | Change the current directory | `cd /home/user` |
| `pwd` | Print the current directory path | `pwd` |
| `mkdir` | Create a new directory | `mkdir my_folder` |
| `rm` | Delete a file or empty directory | `rm file.txt` |
| `clear` | Clear the terminal screen | `clear` |
| `pcsearch` | Search for computers on the server | `pcsearch` |
| `end` | Exit the program | `end` |

### pcsearch Command

Allows you to connect to a server and search for computers. After executing the `pcsearch` command:

1. The program will request the server URL
2. Request username
3. Request password

**Parameters:**
- Without arguments: displays a list of all computers on the server
- With an argument: searches for a computer by hostname

**Examples:**
```bash
pcsearch                    # Find all computers
pcsearch workstation-01     # Find a specific computer
```

## Project Structure

```
GL-Shell/
├── CMakeLists.txt           # Build configuration
├── README.md                # This file
├── inc/
│   └── functions.h          # Header file with function declarations
├── src/
│   ├── main.c               # Main program loop and input handling
│   ├── functions.c          # Implementation of built-in shell commands
│   ├── api.c                # Functions for interacting with server via HTTP
│   └── cJSON.c              # JSON library (external dependency)
├── build/                   # Directory for compiled files
└── hint.txt                 # Hint for using valgrind
```

## Architecture

### main.c
Main program loop:
- Initializes the shell in the `/home` directory
- Reads user input
- Parses command and arguments
- Calls the appropriate command handler

### functions.c
Implementation of built-in commands:
- `ls`: Output directory contents
- `cd`: Navigate between directories
- `pwd`: Output current path
- `mkdir`: Create directories
- `rm`: Delete files/directories
- `clear`: Clear screen
- `findComputer`: Computer search interface

### api.c
Functions for interacting with a remote server:
- `getAllComputers()`: Get list of all computers (GET `/api/pc`)
- `getComputerByHostname()`: Find computer by hostname (GET `/api/pc/{hostname}`)

**Note:** SSL verification is disabled for testing. Remove lines with `CURLOPT_SSL_VERIFYPEER` and `CURLOPT_SSL_VERIFYHOST` before using in production.

## Usage

### Example 1: Basic Navigation

```bash
>>home: pwd
Path is -> /home
>>home: mkdir projects
Created catalog -> projects
>>home: cd projects
>>home/projects: ls
		.		..
```

### Example 2: Computer Search

```bash
>>home: pcsearch
Enter server URL
https://glpu-server.ivkh.ee
Enter username: 
admin
Enter password: 
admin
Finding all computers...
```

## Future Extensions and TODO

The project has a development roadmap:
- [ ] Support for deleting non-empty directories (recursive deletion)
- [ ] Delete multiple files with one command
- [ ] Delete files by extension (e.g., `rm *.c`)
- [ ] Detailed file information in `ls` output (size, permissions, etc.)
- [ ] Command history and auto-completion

## Testing

The project includes a hint for checking memory leaks with valgrind:

```bash
cd build
./glshell &  # Run in background
# Execute commands...
end
# After completion:
cat ../hint.txt  # View the check command
```

## External Dependencies

- **libcurl**: For making HTTP requests to the server
- **cJSON**: JSON library (included in the project, files `cJSON.c` and `cJSON.h`)

## Compilation with Additional Flags

For debugging and testing:

```bash
# With debug information
cmake -DCMAKE_BUILD_TYPE=Debug ..

# With memory leak checking
cmake -DCMAKE_C_FLAGS="-g -fsanitize=address" ..
```

## Known Limitations

- The `rm` command only deletes files and empty directories (uses `remove()`)
- Maximum command length: 255 characters
- SSL verification is disabled for testing (requires enabling for production)
- Pipe (`|`) and redirection (`>`, `<`) are not yet supported

## License

This project is created for educational purposes.

## Author

GlebEvemi

---

**Last Updated**: 2026
