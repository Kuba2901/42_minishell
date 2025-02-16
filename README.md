# 🇵🇱🇮🇹 Polska Madonna - A Minimalist UNIX Shell

> A 42 school project implementing a lightweight shell inspired by Bash

## 📌 Overview

**Polska Madonna** is a simple yet powerful UNIX shell implemented in C as part of the 42 school's common core curriculum. Taking inspiration from **Bash**, it delivers essential shell functionalities while maintaining a minimalist design philosophy. The name reflects its Polish/Italian heritage, bringing a unique cultural fusion to the world of shell implementations. 🎭🐚

## 🚀 Features

✅ **Core Shell Functions**
- Functional command-line prompt
- Command execution from `$PATH` or using absolute/relative paths
- Command history tracking
- Environment variable handling with `$?` expansion

✅ **I/O Operations**
- Input redirection (`<`)
- Output redirection (`>`)
- Heredoc support (`<<`)
- Append mode (`>>`)
- Command chaining through pipes (`|`)

✅ **Signal Management**
- `Ctrl+C`: Initiates new prompt
- `Ctrl+D`: Exits shell
- `Ctrl+\`: No action (intentionally ignored)

✅ **Built-in Commands**
- `echo [-n]`: Display text
- `cd`: Change directory
- `pwd`: Print working directory
- `export`: Set environment variables
- `unset`: Remove environment variables
- `env`: Display environment
- `exit`: Terminate shell

## 📜 Technical Requirements

- Robust handling of unclosed quotes and special characters
- Single global variable (restricted to signal handling)
- Zero memory leaks in implementation
- Behavior modeled after Bash

## 🛠️ Installation & Usage

1. **Clone the repository**
```sh
git clone https://github.com/kuba2901/42_polska_madonna.git
cd polska_madonna
```

2. **Development Environment Setup**
   - **Option A: Dev Container (Recommended)**
     - Prerequisites: Docker + VS Code with Dev Containers extension
     - Open in VS Code and accept container prompt
   
   - **Option B: Local Setup**
     - Install readline library (Debian/Ubuntu):
       ```sh
       sudo apt-get install libreadline-dev
       ```

3. **Build and Launch**
```sh
make roni
```

## 🔧 System Calls & Libraries

The implementation utilizes standard UNIX system calls and libraries:

- **Input/History**: `readline`, `add_history`
- **Process Control**: `fork`, `execve`, `wait`, `pipe`, `dup2`
- **Signal Handling**: `signal`, `kill`, `tcsetattr`, `tcgetattr`
- **File Operations**: `open`, `close`, `read`, `write`, `unlink`
- **Directory Operations**: `getcwd`, `chdir`, `opendir`, `readdir`, `closedir`

## 📖 References

- [Bash Manual](https://www.gnu.org/savannah-checkouts/gnu/bash/manual/)
- [42 School](https://42.fr/) - Part of the Common Core curriculum

---

*Developed with 💖 as part of the 42 school's common core curriculum*