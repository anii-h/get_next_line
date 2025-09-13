# get_next_line - File Descriptor Line Reader

A custom implementation for reading lines from file descriptors, developed as part of the 42 School curriculum operating on file descriptors (`int`) rather than `FILE*` streams, and follows 42's specific project requirements.

> 📌 **Important Note**: This implementation is designed specifically for 42's "get_next_line" project requirements. It should not be confused with the standard C library's `getline()` function which works with `FILE*` streams.

## Overview
This project implements a line-by-line reader for file descriptors using advanced C concepts including:
- Static variables for state persistence
- Linked list buffer management
- Strict memory management with no leaks
- Configurable buffer sizes
- Multiple file descriptor support (bonus)

## Features
| Feature | Mandatory | Bonus |
|---------|-----------|-------|
| Reads lines from file descriptors | ✓ | ✓ |
| Handles multiple file descriptors simultaneously | ✗ | ✓ |
| Configurable buffer size via `-D BUFFER_SIZE` | ✓ | ✓ |
| Proper memory management (Valgrind-clean) | ✓ | ✓ |
| Handles stdin, files, pipes, and sockets | ✓ | ✓ |
| Returns lines with trailing `\n` (except EOF) | ✓ | ✓ |
| Norm-compliant code (42 School standards) | ✓ | ✓ |

## Project Structure
```
get_next_line/
├── get_next_line.c        # Mandatory implementation
├── get_next_line_bonus.c  # Bonus implementation
├── includes/
│   ├── get_next_line.h    # Mandatory header
│   └── get_next_line_bonus.h # Bonus header
└── utils/
    ├── get_next_line_utils.c      # Mandatory helper functions
    └── get_next_line_utils_bonus.c # Bonus helper functions
```

## Compilation
### Mandatory Version
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -I includes get_next_line.c utils/get_next_line_utils.c -o gnl
```

### Bonus Version
```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 -I includes get_next_line_bonus.c utils/get_next_line_utils_bonus.c -o gnl_bonus
```

> 💡 **Buffer Size Notes**:
> - Test with various sizes: `1`, `42`, `4096`, `1000000`
> - Always use `-I includes` to locate header files
> - For real-world use, `4096` is recommended (typical system buffer size)

## Usage Examples
### Mandatory Version
```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd = open("input.txt", O_RDONLY);
    char *line;
    
    while ((line = get_next_line(fd)) != NULL) {
        printf("%s", line);
        free(line);
    }
    close(fd);
    return 0;
}
```

### Bonus Version (Multiple FDs)
```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void) {
    int fd1 = open("file1.txt", O_RDONLY);
    int fd2 = open("file2.txt", O_RDONLY);
    char *line;
    
    // Read from first descriptor
    while ((line = get_next_line(fd1)) != NULL) {
        printf("FD1: %s", line);
        free(line);
    }
    
    // Read from second descriptor
    while ((line = get_next_line(fd2)) != NULL) {
        printf("FD2: %s", line);
        free(line);
    }
    
    close(fd1);
    close(fd2);
    return 0;
}
```

## Technical Implementation
### Core Concepts
- **Static Variable Management**:
  - Mandatory: Single static linked list per file descriptor
  - Bonus: Static array of linked lists indexed by file descriptor (`static t_list *lists[OPEN_MAX]`)
  
- **Buffer Handling**:
  - Reads in chunks of `BUFFER_SIZE` (configurable at compile time)
  - Only processes data when newline is detected
  - Maintains partial lines between calls using linked list nodes

- **Memory Safety**:
  - All allocations properly freed via `free_the_list()`
  - No memory leaks (verified with Valgrind)
  - Strict error checking for all system calls

- **Edge Case Handling**:
  - Empty files
  - Files without trailing newlines
  - Very large lines (>1MB)
  - Multiple concurrent file descriptors (bonus)
  - Standard input (pipes and redirection)

## Testing
Verified against these scenarios:
- ✅ All buffer sizes (1-1M+)
- ✅ Multiple file descriptors simultaneously (bonus)
- ✅ Standard input via pipes (`cat file | ./program`)
- ✅ Files with/without trailing newlines
- ✅ Large files (10MB+)
- ✅ Empty files
- ✅ Binary files (undefined behavior as per project spec)
- ✅ Valgrind memory leak checks (0 leaks detected)
- ✅ Norm compliance (42 School standards)

## Why This Isn't `getline()`
| Feature | Our `get_next_line` | POSIX `getline()` |
|---------|---------------------|-------------------|
| Input Type | File descriptor (`int`) | `FILE*` stream |
| Return Type | `char*` (line buffer) | `ssize_t` (byte count) |
| Buffer Management | Manual allocation/freedom | Caller provides `char**` |
| Standard Compliance | 42 School project spec | POSIX standard |
| Error Handling | Returns `NULL` on error | Returns `-1` on error |

## Author
Ani Hambardzumyan  
Computer Science student at American University of Armenia & 42 Yerevan
## License
This project is part of the 42 School curriculum and is intended for educational purposes only. It adheres to 42 School's academic guidelines and may not be used commercially without permission.

