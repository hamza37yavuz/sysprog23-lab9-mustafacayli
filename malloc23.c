#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
    uint32_t size : 31;
    uint32_t free : 1;
} Info;

typedef struct block {
    Info binfo;
    struct block *next;
    //struct block *prev;
    char data[];
} Block;
//değişim///
/*head of free block list*/
Block *head = NULL;

/* tail of the list: if you use doublylinked list*/
Block *tail = NULL;

/*TODO*/
void *mymalloc(int size){
    /*implement first or best fit*/
    /*find free block*/
    /*if necessary split*/
    /* assign (remove from free list)*/
    Block *curr = head;
    while(curr) {
        if(curr->binfo.free == 1 && curr->binfo.size >= size) {
            break;
        }
        curr = curr->next;
    }
    /*if necessary split*/
    if(curr->binfo.size > size + sizeof(Block)) {
        Block *newblock = (Block *)((char *)curr + sizeof(Block) + size);
        newblock->binfo.size = curr->binfo.size - sizeof(Block) - size;
        newblock->binfo.free = 1;
        newblock->next = curr->next;
        curr->next = newblock;
        curr->binfo.size = size;
    }
    /* assign (remove from free list)*/
    curr->binfo.free = 0;
    return (void *)curr->data;
}

/*TODO*/
void myfree(void *ptr){
    /*coalescing to prev and next you need to do pointer arithmetic*/
    /*you need to add info to the end of each block*/
    Block *curr = (Block *)((char *)ptr - sizeof(Block));
    curr->binfo.free = 1;
    /*check if previous block is free*/
    if(curr->next && curr->next->binfo.free == 1) {
        curr->binfo.size += sizeof(Block) + curr->next->binfo.size;
        curr->next = curr->next->next;
    }
    /*check if next block is free*/
    if(curr != head && curr->binfo.free == 1 && ((char *)curr - (char *)curr - sizeof(Block)) && ((Block *)((char *)curr - curr->binfo.size - sizeof(Block)))->binfo.free == 1) {
        /*previous block*/
        Block *prev = (Block *)((char *)curr - curr->binfo.size - sizeof(Block));
        prev->binfo.size += sizeof(Block) + curr->binfo.size;
        prev->next = curr->next;
    }
}
int main() {
    head = (Block *)sbrk(1024); /*sbrk() returns the start of new memory*/
    head->binfo.free = 1;
    head->binfo.size = 1024 - sizeof(Block);
    head->next = NULL;
    printf("\n sizeof block is multiple of 16: %lu\n", sizeof(Block));
}
