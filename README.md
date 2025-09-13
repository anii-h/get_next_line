# Get Next Line

A C function that reads a line from a file descriptor, handling both static files and standard input with dynamic buffer size management.

## 📋 Description

This project implements a function `get_next_line` that returns one line at a time from a file descriptor. It demonstrates efficient memory management and proper handling of file reading operations using static variables to maintain state between function calls.

### Features
- Reads from any file descriptor (files, stdin, etc.)
- Handles variable buffer sizes through compile-time definition
- Properly manages memory with no leaks
- Includes both mandatory and bonus implementations
- Bonus version supports multiple file descriptors simultaneously

## 🏗️ Project Structure

```
get_next_line/
├── includes/
│   ├── get_next_line.h          # Main header
│   └── get_next_line_bonus.h    # Bonus header
├── utils/
│   ├── get_next_line_utils.c    # Helper functions
│   └── get_next_line_utils_bonus.c  # Bonus helpers
├── get_next_line.c              # Main implementation
├── get_next_line_bonus.c        # Bonus implementation
└── Makefile
```

## 🔧 Compilation

### Mandatory Part
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<size> get_next_line.c get_next_line_utils.c
```

### Bonus Part
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=<size> get_next_line_bonus.c get_next_line_utils_bonus.c
```

### Using Makefile
```bash
make        # Compiles mandatory version
make bonus  # Compiles bonus version
make clean  # Removes object files
make fclean # Removes object files and compiled binaries
make re     # Recompiles project
```

## 📝 Usage

```c
#include "get_next_line.h"  // or "get_next_line_bonus.h" for bonus

int main(void)
{
    int fd = open("file.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

## ⚙️ Parameters

- `fd`: File descriptor to read from
- `BUFFER_SIZE`: Compile-time buffer size definition (default if not specified)

## 📤 Return Value

- Returns the read line (including terminating '\n' character)
- Returns NULL if there's nothing left to read or if an error occurs

## 🚫 Restrictions

- No global variables allowed
- No use of `libft` library
- `lseek()` function is forbidden
- Must handle variable BUFFER_SIZE values (from 1 to very large numbers)

## 🏆 Bonus Features

The bonus implementation adds:
- Single static variable usage
- Multiple file descriptor support
- Ability to switch between different file descriptors without losing reading state

## 📚 Testing

The function should be tested with:
- Different BUFFER_SIZE values (1, 10, 100, 1000000, etc.)
- Various file types (text files, empty files, etc.)
- Standard input
- Multiple file descriptors simultaneously (bonus)
- Binary files (undefined behavior but should not crash)

## 📝 Notes

- The function maintains reading state between calls using static variables
- Memory is properly freed when appropriate
- The implementation is efficient, reading only as much as necessary each call
- The bonus version can manage multiple file descriptors at once

This project demonstrates understanding of file I/O operations, memory management, and static variables in C programming.
