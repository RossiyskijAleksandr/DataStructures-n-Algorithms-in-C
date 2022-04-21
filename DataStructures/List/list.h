#ifndef LIST_HEADER
#define LIST_HEADER

#include <assert.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int print_int(int);
int print_double(float);

#define printAny(X) _Generic((X),                                   \
    char: print_int,                                                \
    short: print_int,                                               \
    int: print_int,                                                 \
    long: print_int,                                                \
    float: print_double,                                            \
    double: print_double,                                           \
    default: print_double                                           \
)(X)

#define List(T)                                                     \
typedef struct {                                                    \
    size_t len;                                                     \
    size_t cap;                                                     \
    T*   data;                                                      \
}* T##List;                                                         \
T##List T##ListInit(size_t len, size_t cap) {                       \
    assert(len < cap);                                              \
    T##List self = malloc(sizeof(*self));                           \
    if(!self)                                                       \
        return NULL;                                                \
    self->data = malloc(sizeof(*self->data) * cap);                 \
    if(!self->data) {                                               \
        free(self);                                                 \
        return NULL;                                                \
    }                                                               \
    self->len = len;                                                \
    self->cap = cap;                                                \
    return self;                                                    \
}                                                                   \
void T##ListFree(T##List self) {                                    \
    free(self->data); self->data = NULL;                            \
    free(self); self = NULL;                                        \
}                                                                   \
bool T##ListResize(T##List self, size_t size) {                     \
    size_t cap;                                                     \
    do {                                                            \
        cap = self->cap * 2;                                        \
    } while(cap - self->len < size);                                \
    T* data = realloc(self->data, cap * sizeof(*self->data));       \
    if(!data)                                                       \
        return false;                                               \
    self->cap = cap;                                                \
    self->data = data;                                              \
    return true;                                                    \
}                                                                   \
void T##ListPrint(T##List self) {                                   \
    printf("[ ");                                                   \
    for(size_t i = 0; i < self->len; ++i)                           \
        printAny(self->data[i]);                                    \
    printf("]{len: %zu, cap: %zu\n", self->len, self->cap);         \
}                                                                   \
bool T##ListAppend(T##List self, T value) {                         \
    if(self->cap == self->len) {                                    \
        bool resizeSuccess = T##ListResize(self, 0);                \
        if(!resizeSuccess)                                          \
            return false;                                           \
    }                                                               \
    self->data[self->len++] = value;                                \
    return true;                                                    \
}                                                                   \
bool T##ListExtendByArray(T##List self, T arr[], size_t len) {      \
    if(self->cap - self->len < len) {                               \
        bool resizeSuccess = T##ListResize(self, len);              \
        if(!resizeSuccess)                                          \
            return false;                                           \
    }                                                               \
    for(size_t i = 0; i < len; i++)                                 \
        self->data[self->len++] = arr[i];                           \
    return true;                                                    \
}                                                                   \
bool T##ListExtendByVariadic(T##List self, size_t len, ...) {       \
    if(self->cap - self->len < len) {                               \
        bool resizeSuccess = T##ListResize(self, len);              \
        if(!resizeSuccess)                                          \
            return false;                                           \
    }                                                               \
    va_list args;                                                   \
    va_start(args, len);                                            \
    for(size_t i = 0; i < len; i++)                                 \
        self->data[self->len++] = va_arg(args, T);                  \
    va_end(args);                                                   \
    return true;                                                    \
}                                                                   \
                                                                    
#endif /* LIST_HEADER */