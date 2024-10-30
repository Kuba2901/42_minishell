# Minishell Allowed External Functions

### 1. **Readline Library Functions**
- **`readline`**: Reads a line of text from standard input, providing editing capabilities. Often used in command-line interfaces.
- **`rl_clear_history`**: Clears the history of commands entered by the user.
- **`rl_on_new_line`**: Tells the readline library that a new line has started, useful when customizing behavior in interactive applications.
- **`rl_replace_line`**: Replaces the current line in the readline buffer with a specified string.
- **`rl_redisplay`**: Updates the display to reflect the current contents of the line buffer.
- **`add_history`**: Adds the most recently inputted line to the history list, useful for tracking previously entered commands.

### 2. **Standard Input/Output**
- **`printf`**: Formats and prints data to the standard output, typically the terminal.
  
### 3. **Memory Management**
- **`malloc`**: Allocates a specified amount of memory in the heap, returning a pointer to the allocated space.
- **`free`**: Deallocates memory previously allocated by `malloc`, preventing memory leaks.

### 4. **File Operations**
- **`write`**: Writes data to a file descriptor, commonly used for output.
- **`access`**: Checks for the accessibility of a file (e.g., read, write, execute permissions).
- **`open`**: Opens a file and returns a file descriptor, used for file manipulation.
- **`read`**: Reads data from a file descriptor into a buffer.
- **`close`**: Closes an open file descriptor to release resources.

### 5. **Process Management**
- **`fork`**: Creates a new process by duplicating the current process, returning a process ID.
- **`wait`**: Waits for a child process to finish execution.
- **`waitpid`**: Waits for a specific child process to finish execution.
- **`wait3`** and **`wait4`**: Similar to `waitpid` but with additional options, allowing for resource usage statistics.
- **`exit`**: Terminates the current process, returning a specified exit status.

### 6. **Signal Handling**
- **`signal`**: Sets up a signal handler, allowing processes to respond to asynchronous events (e.g., SIGINT).
- **`sigaction`**: Provides a more flexible interface than `signal` for handling signals.
- **`sigemptyset`**: Initializes a signal set to exclude all signals.
- **`sigaddset`**: Adds a specified signal to a signal set.
- **`kill`**: Sends a specified signal to a process, allowing for process control.

### 7. **Directory and Path Manipulation**
- **`getcwd`**: Retrieves the current working directory of the process.
- **`chdir`**: Changes the current working directory.
- **`opendir`**: Opens a directory stream to read directory entries.
- **`readdir`**: Reads a directory entry from the directory stream.
- **`closedir`**: Closes a directory stream to release resources.

### 8. **File Information**
- **`stat`**, **`lstat`**, and **`fstat`**: Retrieve information about a file (e.g., size, permissions, timestamps) where `lstat` is used for symbolic links, and `fstat` is used with file descriptors.

### 9. **File and Directory Manipulation**
- **`unlink`**: Deletes a file by removing its directory entry.
- **`dup`**: Duplicates an open file descriptor.
- **`dup2`**: Duplicates a file descriptor to a specified file descriptor.

### 10. **Pipes and IPC**
- **`pipe`**: Creates a unidirectional data channel (pipe) that can be used for inter-process communication.

### 11. **Execution**
- **`execve`**: Replaces the current process image with a new process image, commonly used to run different programs.

### 12. **Error Handling**
- **`strerror`**: Returns a string describing an error number.
- **`perror`**: Prints a descriptive error message to the standard error based on the global `errno`.

### 13. **Terminal Operations**
- **`isatty`**: Determines if a file descriptor is associated with a terminal.
- **`ttyname`**: Returns the name of the terminal associated with a file descriptor.
- **`ttyslot`**: Returns the terminal slot number for the process.
- **`ioctl`**: Provides control over devices, used for device-specific input/output operations.

### 14. **Environment Variables**
- **`getenv`**: Retrieves the value of an environment variable by name.

### 15. **Terminal Control (termcap)**
- **`tcsetattr`**: Sets the parameters associated with the terminal.
- **`tcgetattr`**: Gets the parameters associated with the terminal.
- **`tgetent`**: Loads the entry for a terminal type.
- **`tgetflag`**: Checks for specific terminal flags.
- **`tgetnum`**: Gets numeric capabilities for the terminal.
- **`tgetstr`**: Retrieves string capabilities for terminal handling.
- **`tgoto`**: Returns cursor-movement commands based on position.
- **`tputs`**: Outputs terminal capabilities (like moving the cursor) using a specified function. 