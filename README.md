# Basic Memory Management System in C

## Overview
This project demonstrates the implementation of a basic memory management system in C, similar to the standard `malloc` and `free` functions. It uses a fixed-size memory pool and applies the **first-fit** algorithm for dynamic memory allocation. Additionally, it supports block splitting and merging (coalescing) to efficiently manage memory.

## Features
- **Custom `malloc`**: Allocates memory from a predefined memory pool using the **first-fit** strategy.
- **Custom `free`**: Deallocates memory and merges adjacent free blocks to avoid fragmentation.
- **Memory Pool**: A statically allocated memory block (1MB) is used as the memory pool for dynamic allocations.
- **Block Splitting**: Splits larger blocks into allocated and free blocks to minimize wasted memory.
- **Block Coalescing**: Combines adjacent free blocks during deallocation to prevent memory fragmentation.

## Files
- `main.c` - The main C source file containing the implementation of custom `malloc`, `free`, and test cases.
- `README.md` - This file describing the project, its purpose, and usage.

## Memory Pool Layout
The memory pool is divided into blocks, where each block contains:
- **Metadata**: Size of the block and whether it is free or allocated.
- **Memory Payload**: The actual block of memory returned to the user for storage.

Each block is represented by the following structure:

```c
typedef struct Block {
    size_t size;          // Size of the block (excluding metadata)
    int free;             // 1 if the block is free, 0 if allocated
    struct Block* next;   // Pointer to the next block
} Block;

Functions
1. initialize_memory_pool()

Initializes the memory pool by marking the entire pool as one large free block.
2. custom_malloc(size_t size)

Allocates memory from the pool using the first-fit algorithm:

    Finds the first free block large enough to fit the requested size.
    Splits the block if necessary (if the block is larger than required).
    Returns a pointer to the memory block or NULL if no suitable block is found.

3. custom_free(void* ptr)

Deallocates memory and marks the block as free:

    Updates the block’s metadata to mark it free.
    Coalesces adjacent free blocks to avoid fragmentation.

4. test_memory_management()

A simple test function that demonstrates memory allocation and deallocation by:

    Allocating blocks of various sizes.
    Freeing some blocks.
    Reallocating memory to ensure efficient reuse of the pool.

Example Usage

bash

gcc main.c -o memory_management
./memory_management

Output:

python

Allocating 100 bytes
Allocating 200 bytes
Freeing 100 bytes block
Allocating 50 bytes
Freeing 200 bytes block
Freeing 50 bytes block
Memory management system test completed.

Memory Pool Management Details

    First-Fit Algorithm: Allocates the first available free block that is large enough to fulfill the request.
    Block Splitting: If a larger-than-required block is found, it is split into two: one allocated block and one smaller free block.
    Block Coalescing: After freeing a block, adjacent free blocks are merged into one to prevent fragmentation and maximize usable memory.