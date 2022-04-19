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

List listInit(size_t, size_t);
void listFree(List);
bool listResize(List);
bool listAppend(List, void*);

#endif /* LIST_HEADER */