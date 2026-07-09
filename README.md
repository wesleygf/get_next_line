*This project has been created as part of the 42 curriculum by wgolbert.*

# get_next_line

## Description

The **get_next_line** project consists of implementing a function capable of reading a file descriptor line by line. Each call to the function returns the next available line, including the newline character (`\n`) when present. When the end of the file is reached or an error occurs, the function returns `NULL`.

The main challenge of this project is that a line may be larger than `BUFFER_SIZE`, making it necessary to preserve unread data between function calls. The bonus version extends this behavior to support multiple file descriptors simultaneously, ensuring that each descriptor maintains its own reading state independently.

---

# Features

- Reads one line at a time from a file descriptor.
- Supports any positive `BUFFER_SIZE`.
- Correctly handles files with or without a trailing newline.
- Preserves unread data between function calls.
- Supports multiple file descriptors independently (bonus).
- Avoids memory leaks by properly allocating and freeing dynamic memory.

---

# Instructions

## Compilation

Compile the mandatory version:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

Compile the bonus version:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

You may change `BUFFER_SIZE` during compilation:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=100 get_next_line.c get_next_line_utils.c
```

---

# Algorithm

The implementation follows a buffered reading approach.

Instead of reading the entire file at once, the function repeatedly calls `read()` using a temporary buffer of size `BUFFER_SIZE`. Every chunk that is read is appended to an internal buffer associated with the corresponding file descriptor.

After each read, the accumulated buffer is checked for the presence of a newline character.

- If a newline is found, the function extracts the complete line.
- The remaining characters after the newline are preserved for the next function call.
- If no newline is found, additional reads are performed until either a newline or the end of the file is reached.

This approach guarantees that only the minimum amount of data required is read from the file.

---

# Why a Linked List?

The bonus version requires supporting multiple file descriptors simultaneously.

Each file descriptor may be at a completely different position in its respective file. Because of this, every descriptor needs to keep its own:

- remaining buffer;
- current buffer length;
- file descriptor identifier.

A linked list was chosen because it allows storing an arbitrary number of file descriptors without requiring a fixed-size array.

Each node contains:

```c
typedef struct s_list_fd
{
    int                 fd;
    char                *buffer;
    size_t              len;
    struct s_list_fd    *next;
} t_list_fd;
```

Whenever `get_next_line()` is called:

1. The list is searched for a node matching the requested file descriptor.
2. If the node already exists, its stored buffer is reused.
3. If it does not exist, a new node is created and added to the list.
4. After returning a line, the remaining unread characters stay inside that node.
5. When the file reaches EOF and no data remains, the node is removed and all allocated memory is freed.

This design makes every file descriptor completely independent from the others.

For example:

```
fd3 -> "Hello\nWo"
fd5 -> "ABC"
fd8 -> "12345\nXYZ"
```

Each node stores the unread portion of its own file.

Calling:

```c
get_next_line(fd3);
```

returns

```
Hello\n
```

and only updates the node for `fd3`:

```
fd3 -> "Wo"
fd5 -> "ABC"
fd8 -> "12345\nXYZ"
```

The other descriptors remain untouched.

This makes the solution scalable and independent of the number of simultaneously opened files.

---

# Memory Management

Memory allocation is carefully managed throughout the project.

- Temporary buffers are allocated only while reading.
- The internal buffer grows dynamically as needed.
- Returned lines are newly allocated and must be freed by the caller.
- Remaining data is preserved only until it is no longer needed.
- Nodes are removed from the linked list once the file has been completely read or an error occurs.

This prevents memory leaks while maintaining persistent state between function calls.

---

# Complexity

Considering **n** as the length of the returned line:

| Operation | Complexity |
|----------|------------|
| Reading a line | O(n) |
| Searching a file descriptor in the list | O(number of open file descriptors) |
| Memory usage | O(size of remaining unread data) |

Since the number of simultaneously opened file descriptors is generally small, the linked list provides an efficient and simple solution.

---

# Resources

Official documentation:

- https://man7.org/linux/man-pages/man2/read.2.html
- https://man7.org/linux/man-pages/man3/malloc.3.html
- https://man7.org/linux/man-pages/man3/free.3.html

General references:

- The C Programming Language — Brian W. Kernighan & Dennis M. Ritchie
- 42 get_next_line subject
- Linux manual pages (man)

## AI Usage

Artificial Intelligence (ChatGPT) was used exclusively as a learning and review tool.

Specifically, it was used to:

- explain memory allocation and deallocation;
- review algorithm ideas;
- improve the wording and organization of this README.

The implementation, design decisions, debugging, testing, and final code were developed by the author.
