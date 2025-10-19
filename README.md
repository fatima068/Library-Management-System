# Library Management System

A simple and efficient C++ console application for managing books, users, and library operations such as borrowing and returning books. The system demonstrates core object-oriented programming principles and file handling.

## Features
### User Authentication
- Secure login system with credential validation.
- User data stored and verified via text files.
- Session-based access control to restrict operations to logged-in users.

### Book Management
- Add, edit, delete, and view books in inventory.
- Each record includes title, author, publisher, ID, and available quantity.
- Prevents duplicate entries and invalid updates.
- Supports book search by ID, title, or author.

### Borrow & Return System
- Borrow books with availability checks and record tracking.
- Return books and update stock automatically.
- Maintains transaction records in persistent storage.

### User & Account Handling
- Store user data (username, password, role).
- Add, modify, or remove user accounts (admin functionality if enabled).
- View borrowed books by user.

### File-Based Data Persistence
- All records saved in `textFiles/` for books, users, and transactions.
- Automatic data load on startup and save on exit.
- Handles missing or empty files gracefully.

### System Design
- Modular code structure using:
  - `allClasses.hpp` – Class definitions (Book, User, System, etc.)
  - `system.hpp` – Core logic and operations.
  - `login.hpp` – Authentication functions.
  - `main.cpp` – Program entry and menu system.
- Menu-driven interface with input validation and clear prompts.
- Simple reporting features (inventory status, borrow history).


## Team Members
- Syeda Fatima Waseem (24K-0924)  
- Syed Ikrash Ahmed (24K-0998)  
