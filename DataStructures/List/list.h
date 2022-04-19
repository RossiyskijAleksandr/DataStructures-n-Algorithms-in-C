#ifndef LIST_HEADER
#define LIST_HEADER

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdbool.h>

#define List(T)                                                     \
typedef struct {                                                    \
    size_t len;                                                     \
    size_t cap;                                                     \
    T*   data;                                                      \
}* T##List;                                                         \
T##List T##ListInit(size_t len, size_t cap) {                       \
    assert(len < cap);                                              \
    T##List self = malloc(sizeof(*self));                           \
    self->data = malloc(sizeof(*self->data) * cap);                 \
    if(!self->data)                                                 \
        free(self);                                                 \
    self->len = len;                                                \
    self->cap = cap;                                                \
    return self;                                                    \
}                                                                   \
void T##ListFree(T##List self) {                                    \
    free(self->data); self->data = NULL;                            \
    free(self); self = NULL;                                        \
}                                                                   \
bool T##ListResize(T##List self) {                                  \
    size_t cap = self->cap * 2;                                     \
    T* data = realloc(self->data, cap * sizeof(*self->data));       \
    if(!data)                                                       \
        return false;                                               \
    self->cap = cap;                                                \
    self->data = data;                                              \
    return true;                                                    \
}                                                                   \
bool T##ListAppend(T##List self, T value) {                         \
    if(self->cap == self->len) {                                    \
        bool resizeSuccess = T##ListResize(self);                   \
        if(!resizeSuccess)                                          \
            return false;                                           \
    }                                                               \
    self->data[self->len++] = value;                                \
    return true;                                                    \
}                                            

#endif /* LIST_HEADER */