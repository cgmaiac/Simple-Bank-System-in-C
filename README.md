# Simple Bank System in C

A simple banking system developed in **C** as a study and practice project.

## About the Project

**BankSystem** is a simple console-based banking system that uses **linked lists and files** to store and manage bank accounts.

The project was created primarily for studying and practicing programming logic with the **C programming language**, while developing a better understanding of how important programming concepts work in practice.

The system currently focuses on account management and data persistence, with additional banking features planned for future implementations.

## Project Purpose

The main purpose of this project is **learning and practice**.

Through the development of BankSystem, I am practicing and improving my understanding of:

- Programming logic and problem solving
- The C programming language
- Linked lists and dynamic data structures
- Input validation
- Functions and procedures
- File handling and data persistence
- Pointers
- Program organization
- Basic banking system logic

Instead of being created as a production-ready banking application, this project is being developed as a way to understand programming concepts by implementing them in a practical project.

## Current Features

The project currently includes functionality for:

- Creating bank accounts
- Logging into accounts
- Searching for accounts by username
- Input validation
- Storing accounts using linked lists
- Saving account data to files
- Loading previously saved accounts when the program starts
- Basic account management

The project is still under development, so not all planned banking operations are available yet.

## Planned Features

Future commits will continue the development of the system and implement the remaining banking features, including:

- Deposits
- Withdrawals
- Transfers between accounts
- Account balance display
- Account deletion
- Additional account management features
- Improvements to validation and overall system organization

The project will be gradually expanded through future commits as I continue studying and implementing new concepts in C.

## Data Structures and File Handling

Bank accounts are stored in a **linked list**, allowing accounts to be dynamically created and managed during program execution.

The system also uses **file handling** to save account information and load it again when the program starts. This allows the data created during one execution of the program to persist between executions.

This combination of linked lists and files is one of the main learning objectives of the project.

## How to Compile

You need a C compiler such as **GCC** installed on your system.

Clone the repository and enter the project directory:

```bash
git clone https://github.com/cgmaiac/Simple-Bank-System-in-C.git
cd Simple-Bank-System-in-C
```

Compile the project using GCC:

```bash
gcc *.c -o bank
```

If your project contains files organized into different directories, adjust the compilation command according to the project structure.

## How to Run

After compiling the program, run the executable:

### Linux

```bash
./bank
```

### Windows

If compiled as an executable:

```cmd
bank.exe
```

The program will start in the terminal and allow you to interact with the banking system.

## Project Status

**In Development**

This project is **not finished yet**.

The current version represents an ongoing learning process. Future commits will add the remaining banking operations and improve the existing functionality as I continue studying the C language, data structures, file handling, input validation, and programming logic.

## Technologies

- **C**
- **GCC**
- **Git / GitHub**

## Author

Developed as a personal study project focused on learning and practicing programming with C.
