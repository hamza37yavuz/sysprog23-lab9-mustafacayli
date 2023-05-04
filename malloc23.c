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
}

/*TODO*/
void myfree(void *ptr){
    /*coalescing to prev and next you need to do pointer arithmetic*/
    /*you need to add info to the end of each block*/
}
int main() {
    head = (Block *)sbrk(1024); /*sbrk() returns the start of new memory*/
    head->binfo.free = 1;
    head->binfo.size = 1024 - sizeof(Block);
    head->next = NULL;
    printf("\n sizeof block is multiple of 16: %lu\n", sizeof(Block));
}
