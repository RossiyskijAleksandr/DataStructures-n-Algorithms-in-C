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

List listInit(size_t len, size_t cap) {
    assert(len < cap);
    List self = malloc(sizeof(*self));
    self->data = malloc(sizeof(*self->data) * cap);
    if(!self->data)
        free(self);
    self->len = len;
    self->cap = cap;

    return self;
}

void listFree(List self) {
    free(self->data); self->data = NULL;
    free(self); self = NULL;
}

bool listResize(List self) {
    size_t cap = self->cap * 2;
    void** data = realloc(self->data, cap * sizeof(*self->data));
    if(!data) 
        return false;
    self->cap = cap;
    self->data = data;
    return true;
}

bool listAppend(List self, void* value) {
    if(self->cap == self->len) {
        bool resizeSuccess = listResize(self);
        if(!resizeSuccess)
            return false;
    }
    self->data[self->len++] = value;
    return true;
}