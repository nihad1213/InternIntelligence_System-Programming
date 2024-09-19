#include <stdio.h>
#include <stddef.h>

#define POOL_SIZE 1024 * 1024

typedef struct Block {
    size_t size;
    int free;
    struct Block* next;
} Block;

#define BLOCK_SIZE sizeof(Block)

static char memory_pool[POOL_SIZE];
static Block* free_list = (Block*)memory_pool;

void initialize_memory_pool() {
    free_list->size = POOL_SIZE - BLOCK_SIZE;
    free_list->free = 1;
    free_list->next = NULL;
}

void* custom_malloc(size_t size) {
    Block* current = free_list;

    while (current != NULL) {
        if (current->free && current->size >= size) {
            if (current->size > size + BLOCK_SIZE) {
                Block* new_block = (Block*)((char*)current + BLOCK_SIZE + size);
                new_block->size = current->size - size - BLOCK_SIZE;
                new_block->free = 1;
                new_block->next = current->next;
                current->size = size;
                current->next = new_block;
            }
            current->free = 0;
            return (char*)current + BLOCK_SIZE;
        }
        current = current->next;
    }
    return NULL;
}

void custom_free(void* ptr) {
    if (ptr == NULL) return;

    Block* block_to_free = (Block*)((char*)ptr - BLOCK_SIZE);
    block_to_free->free = 1;

    Block* current = free_list;
    while (current != NULL && current->next != NULL) {
        if (current->free && current->next->free) {
            current->size += BLOCK_SIZE + current->next->size;
            current->next = current->next->next;
        }
        current = current->next;
    }
}

void test_memory_management() {
    initialize_memory_pool();

    printf("Allocating 100 bytes\n");
    void* ptr1 = custom_malloc(100);
    
    printf("Allocating 200 bytes\n");
    void* ptr2 = custom_malloc(200);
    
    printf("Freeing 100 bytes block\n");
    custom_free(ptr1);
    
    printf("Allocating 50 bytes\n");
    void* ptr3 = custom_malloc(50);
    
    printf("Freeing 200 bytes block\n");
    custom_free(ptr2);
    
    printf("Freeing 50 bytes block\n");
    custom_free(ptr3);
}

int main() {
    test_memory_management();
    printf("Memory management system test completed.\n");
    return 0;
}
