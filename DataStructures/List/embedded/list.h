#ifndef LIST_HEADER
#define LIST_HEADER

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct {
    size_t len;
    size_t cap;
    void** data;
}* List;

extern List listInit(size_t, size_t);
extern void listFree(List);
extern bool listResize(List);
extern bool listAppend(List, void*);

#endif /* LIST_HEADER */