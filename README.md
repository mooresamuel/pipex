# Pipex - 42 Project

## 🚀 Project Overview

**Pipex** is a project at 42 that involves simulating a simplified version of the `pipe` command in Unix-like systems. The goal is to create a program that can execute multiple commands, redirecting their input and output streams using pipes, by forking processes and handling standard input/output redirection.

### Bonus Feature:
The bonus implementation extends the core functionality to handle **piping multiple programs** to each other, allowing a chain of processes to communicate via pipes, similar to how pipes work in the shell.

---

## 💡 Key Features & Approach

### Basic Functionality

The main objective of the project is to simulate the functionality of piping between processes. The program should:

1. **Fork Processes**: The program forks child processes for each command to execute.
2. **Pipes Between Commands**: Using the `pipe()` system call, the program creates pipes to connect the standard output of one process to the standard input of the next.
3. **Redirection**: Handle input and output redirection using the `<` and `>` operators.
4. **Execute Commands**: Use `execve()` to run each program in the forked processes.

### 🧑‍💻 Core Features:
- **Piping**: Simulate piping between processes using Unix-like pipes (`|`).
- **Forking**: Use `fork()` to create child processes that run different commands.
- **Redirection**: Handle input and output redirection using file descriptors (`<` and `>`).
- **Command Execution**: Use `execve()` to replace the child process with the desired command.

### Bonus Feature: **Piping Multiple Programs**

The bonus expands the functionality to handle multiple commands piped together. This is done by:
- Setting up multiple pipes between consecutive commands.
- Managing multiple child processes, ensuring the output of one command becomes the input of the next in the chain.
- Handling redirections properly even when multiple commands are involved.

### 🧑‍🔧 Key Concepts & System Calls
1. **Forking**: The program creates child processes using the `fork()` system call. Each child process executes a specific command.
2. **Pipes**: The `pipe()` system call is used to create a unidirectional data channel between processes. The standard output of one process is connected to the standard input of the next.
3. **Execve**: The `execve()` system call is used to load a new program into the current process, replacing the forked child process.
4. **File Descriptors**: Redirection is achieved by manipulating file descriptors using `dup2()`.

---

## 🧑‍🔧 Compilation & Setup

To compile the project, follow these steps:

### 1. Clone the repository

```bash
git clone https://github.com/your-username/pipex.git
cd pipex
```

### 2. Compile the project

To compile the project and generate the executable, run:

```bash
make
```


## 🧪 Example Usage

The program can be used to pipe commands together by providing input and output file names, along with the commands to execute.

### Basic Usage (Two Commands)

```bash
./pipex file1 "command1" "command2" file2
```
This runs command1 with file1 as input, pipes its output to command2, and writes the result to file2.

### Bonus Usage (Multiple Commands)
```bash
./pipex file1 "command1" "command2" "command3" file2
```
This will run command1, pipe its output to command2, then pipe that output to command3, and finally write the result to file2.

## 💡 Key Concepts & Challenges
Pipes Between Commands: Setting up pipes for multiple commands involves managing multiple file descriptors, which can be tricky when dealing with multiple processes.
Forking: Properly forking and managing child processes so they execute concurrently, while also ensuring correct piping and redirection.
Redirection: Ensuring the correct setup of input/output redirection using file descriptors for each command.
Multiple Commands: Handling a chain of multiple commands piped together, managing multiple pipes and processes concurrently.
## 📄 License
This project is licensed under the MIT License - see the LICENSE file for details.

## 🤝 Collaboration
Feel free to contribute to this project! Fork it, submit issues, or open a pull request. If you have suggestions or feedback, don’t hesitate to reach out.

Happy coding! 🚀
