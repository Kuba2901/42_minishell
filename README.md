Here's a structured README for your **minishell** project:  

---

# 🐚 Minishell - As Beautiful as a Shell  

## 📌 Overview  
Minishell is a simple UNIX shell implemented in C, inspired by **Bash**. It handles command execution, redirections, pipes, signals, and built-in commands while maintaining a minimalistic approach.  

## 🚀 Features  
✅ **Prompt Display** - A functional command-line prompt.  
✅ **Command Execution** - Runs commands based on the `$PATH` or an absolute/relative path.  
✅ **Command History** - Keeps track of previous commands.  
✅ **Redirections**  
   - `<` (Input redirection)  
   - `>` (Output redirection)  
   - `<<` (Heredoc)  
   - `>>` (Append mode)  
✅ **Pipes (`|`)** - Allows command chaining.  
✅ **Environment Variables** - Expands variables like `$?`.  
✅ **Signal Handling**  
   - `Ctrl+C` starts a new prompt.  
   - `Ctrl+D` exits the shell.  
   - `Ctrl+\` does nothing.  

## ⏭️ Yet to be implemented 
**Built-in Commands**  
   - `echo [-n]`  
   - `cd`  
   - `pwd`  
   - `export`  
   - `unset`  
   - `env`  
   - `exit`  

## 📜 Mandatory Requirements  
- **No unclosed quotes or unneeded special character interpretations.**  
- **Minimal use of global variables (only one for signals).**  
- **Memory leaks are NOT allowed in user-implemented code.**  
- **Bash-like behavior as a reference.**  

## 🛠️ Installation & Usage with Dev Containers  
1. **Clone the repository**:  
	```sh
	git clone https://github.com/kuba2901/42_minishell.git
	cd minishell
	```

2. **Open the project in a Dev Container**:  
	- Ensure you have Docker and Visual Studio Code with the Dev Containers extension installed.
	- Open the project folder in Visual Studio Code.
	- When prompted, reopen the folder in a Dev Container.

3. **Build and run the project**:  
	```sh
	make run
	```

> **Note**: If you prefer not to use Docker, you might need to install the `readline` library manually. On Debian-based systems, you can do this with:
> ```sh
> sudo apt-get install libreadline-dev
> ```

## 🔧 External Functions Used  
Minishell utilizes system calls and libraries such as:  
- `readline`, `add_history`  
- `fork`, `execve`, `wait`, `pipe`, `dup2`  
- `signal`, `kill`, `tcsetattr`, `tcgetattr`  
- `open`, `close`, `read`, `write`, `unlink`  
- `getcwd`, `chdir`, `opendir`, `readdir`, `closedir`  

## 📖 References  
- [Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)  