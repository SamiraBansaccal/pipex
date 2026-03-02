# pipex (42 School)

## 📋 Description
The **pipex** project is a deep dive into UNIX mechanisms. It handles the redirection of standard input and output through a pipe, mimicking the behavior of the shell command: `< file1 cmd1 | cmd2 > file2`.

## 🧠 Implementation Logic (Score: 121/100)
This project requires a rigorous handling of system calls and file descriptors to ensure smooth data flow without leaks or process blocking.

- **Process Management**: Uses `fork()` to create child processes, executing commands in isolated environments via `execve()`.
- **Pipe Handling**: Implemented `pipe()` to create unidirectional data channels. I focused on closing unused FDs immediately to prevent zombie processes or I/O hanging.
- **Path Resolution**: Parses the `PATH` environment variable to dynamically locate command binaries.
- **🌟 Bonus Performance**:
  - **Multiple Pipes**: Fully functional support for an unlimited number of pipes (e.g., `file1 cmd1 | cmd2 | ... | cmdN file2`).
  - **Here_doc**: The logic was implemented in `src/bns/here_doc_bonus.c`. Although it faced a minor regression during the final evaluation, the overall logic contributed to a 121/100 score.

## 📂 Project Structure
- `src/`: Mandatory source files (`main.c`, `pipex.c`, `utils.c`).
- `src/bns/`: Bonus implementation for multiple pipes and here_doc.
- `includes/libft/`: Custom C library used for string and memory utilities.

## 🛠️ Usage & Compilation
To compile the **mandatory** part:
```bash
make
```
To compile with multiple pipes and here_doc:
```bash
make bonus
```
Execution
Standard usage:
```bash
./pipex infile "ls -l" "wc -l" outfile
```
Bonus usage (Multiple pipes):
```bash
./pipex infile "cat" "grep hello" "wc -l" outfile
```
Bonus usage (Here_doc):
```bash
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```
