# 💻 Win-C-Shell: A Custom Windows Command Interpreter

A lightweight, functional command-line shell built from scratch in C for the Windows environment. This project demonstrates core systems programming concepts like process management, string parsing, and state persistence (command history).

---

## 🚀 Key Features

* **External Program Execution**: Seamlessly launches external applications like `notepad`, `gcc`, `python`, and `git`.
* **Smart Internal Commands**: Custom logic to handle native Windows shell commands such as `dir`, `cls`, and `date` without needing extra prefixes.
* **Command History**: Remembers and displays the last 10 commands executed during your session using a fixed-size queue.
* **Graceful Exit**: Includes a built-in `exit` command to safely close the interpreter.

---

## 📂 Project Structure

```text
Win-C-Shell/
├── src/
│   └── main.c      # The core source code
├── README.md       # Project documentation
└── .gitignore      # Keeps the repo clean (ignores .exe files)
