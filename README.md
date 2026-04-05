# Get Next Line

A C library that reads a file (or any readable file descriptor) **one line at a time**. Each call to `get_next_line` returns the next line as a heap-allocated string. This project follows the **42 School** *get_next_line* assignment: it uses only `read`, `malloc`, and `free` for I/O and memory, and keeps unread data between calls in a **static buffer**.

## What it does

- **`get_next_line(int fd)`** reads from `fd` in chunks of **`BUFFER_SIZE`** bytes until it can build a full line.
- A **line** is a sequence of bytes ending with **`'\n'`**, or the remainder of the file if there is no newline before EOF.
- The returned string **includes** the `'\n'` when the line was terminated by a newline.
- **`NULL`** is returned when there is nothing left to read (EOF with empty remainder) or on **invalid `fd`**, **`BUFFER_SIZE <= 0`**, **`read` error**, or **allocation failure**.

## Project layout

| Part | Files | Role |
|------|--------|------|
| **Mandatory** | `get_next_line.c`, `get_next_line_utils.c`, `get_next_line.h` | Single static stash: one open FD at a time in typical use. |
| **Bonus** | `get_next_line_bonus.c`, `get_next_line_utils_bonus.c`, `get_next_line_bonus.h` | Static stash **per file descriptor** (`buffer[fd]`), so you can interleave `get_next_line` on **different** `fd` values (e.g. multiple files). The bonus implementation indexes an array of size **1024**, so behavior is only defined for `fd` values that fit that model. |

Helper routines (string length, substring, join, duplicate, memory copy, custom `strchr`-style newline search) live in the `*_utils*.c` files and are declared from the matching header.

## Configuration: `BUFFER_SIZE`

The read chunk size is set at **compile time** via the `BUFFER_SIZE` macro. If you do not define it, the headers default it to **1**:

```c
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
#endif
```

You should pass it when compiling, for example:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c
```

For the bonus sources:

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c
```

Larger `BUFFER_SIZE` values reduce the number of `read` calls; correctness should not depend on a specific value (subject to normal limits and available memory).

## Using in your own program

1. Add the appropriate `.c` files to your project and `#include` either `get_next_line.h` or `get_next_line_bonus.h`.
2. Compile with `-D BUFFER_SIZE=<n>` as needed.
3. Call `get_next_line(fd)` in a loop until it returns `NULL`.
4. **Free** each non-`NULL` line when you are done with it.

Example sketch:

```c
char *line;

while ((line = get_next_line(fd)) != NULL)
{
	/* use line */
	free(line);
}
close(fd);
```

## Implementation notes

- **Static storage** holds leftover bytes after the last newline so the next call continues from the correct position.
- **`read` loop**: keeps reading until a newline appears in the stash or `read` returns 0 (EOF).
- **Edge cases**: empty file, file ending without `'\n'`, very long lines, and `read` returning fewer bytes than requested are handled by accumulating into the stash.

## Requirements

- A C compiler (`cc` / `gcc` / `clang`).
- POSIX-like `read` / `close` on `fd` (typical on Linux and macOS).

## Author

Student project — headers credit **ecakdemi** (@ student.42.fr).

## License

No license file is included in this repository; reuse is at your discretion and subject to your school or workplace rules.
