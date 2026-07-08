# Machine Organization and Programming (CS 354)

Coursework from CS 354 (Machine Organization and Programming) at the University of Wisconsin–Madison. This repository contains systems-level C programs covering dynamic memory management, low-level bit manipulation, signal handling, and cache simulation.

**Note:** This repository is a portfolio showcase of completed coursework, not a runnable pipeline. Code and outputs are provided for review.

## Projects

### Dynamic Memory & 2D Arrays
- **`my_magic_square.c`** — Generates an odd-sized magic square using the Siamese method, dynamically allocating a 2D array on the heap and writing results to a file. Demonstrates manual pointer arithmetic and heap memory management without relying on array indexing syntax.
- **`check_sudoku_board.c`** — Validates a Sudoku board's row and column constraints from a heap-allocated 2D array read from a file, checking for duplicate values and invalid entries.
- **`p3Heap.c`** — A custom heap memory manager implementing manual allocation and deallocation logic, simulating how `malloc`/`free` work under the hood.

### Low-Level Systems Programming
- **`decode.c`** — Decodes Caesar cipher–encoded text using bitwise XOR to derive the shift key from a user's login, then applies a circular shift across lowercase letters. Includes disassembled object code (`decode.o` → `objectfile_contents.txt`) analyzed to trace program execution at the assembly level.
- **`csim.c`** — A cache simulator that models set-associative cache behavior (hits, misses, evictions) using an LRU replacement policy, built from raw memory access traces. Implements manual bit masking to extract tag, set index, and offset from memory addresses.

### Signal Handling
- **`my_c_signal_handler.c`** — Registers custom handlers for `SIGALRM`, `SIGUSR1`, and `SIGINT`, printing periodic process status and tracking signal counts.
- **`my_div0_handler.c`** — Handles `SIGFPE` (division-by-zero) and `SIGINT` gracefully, allowing a running program to report state before terminating.
- **`send_signal.c`** — A command-line utility that sends `SIGUSR1` or `SIGINT` to a target process by PID.

## Skills Demonstrated

- Manual pointer arithmetic and dynamic 2D array management on the heap
- Low-level memory allocation (custom heap manager implementation)
- Bitwise operations or bit masking for address decomposition
- Signal handling and inter-process signaling in C
- Cache behavior simulation (LRU replacement, hit/miss/eviction tracking)
- Reading and interpreting x86 disassembly

## Tools

C, GDB, Linux/Unix environment, GCC

## About

Coursework from CS 354, Spring 2025, University of Wisconsin–Madison.
