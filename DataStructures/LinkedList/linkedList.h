#ifndef LINKEDLIST_HEADER
#define LINKEDLIST_HEADER

#include <assert.h>
#include <stddef.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define LinkedList(T)                                                   \
typedef struct T##linkedlist* T##LinkedList;                            \
struct T##linkedlist {                                                  \
    T value;                                                            \
    LinkedList next;                                                    \
};                                                                      \
T##LinkedList T##LinkedListInitEmpty(T value) {                         \
    T##LinkedList self = malloc(sizeof(*self));                         \
    if(!self)                                                           \
        return NULL;                                                    \
    self->value = value;                                                \
    self->next = NULL;                                                  \
    return self;                                                        \
}                                                                       \
T##LinkedList T##LinkedListInitChain(T value, T##LinkedList next) {     \
    assert(next);                                                       \
    T##LinkedList self = malloc(sizeof(*self));                         \
    if(!self)                                                           \
        return NULL;                                                    \
    self->value = value;                                                \
    self->next = next;                                                  \
    return self;                                                        \
}                                                                       \
void T##LinkedListFree(T##LinkedList self) {                            \
    while(self) {                                                       \
        T##LinkedList next = self->next;                                \
        free(self);                                                     \
        self = next;                                                    \
    }                                                                   \
}                                                                       \
bool T##LinkedListAppend(T##LinkedList self, T value) {                 \
    while(self->next)                                                   \
        self = self->next;                                              \
    self->next = T##LinkedListInitEmpty(value);                         \
    if(self->next)                                                      \
        return true;                                                    \
    return false;                                                       \
}                                                                       \
T##LinkedList T##LinkedListPrepend(T##LinkedList link, T value) {       \
    T##LinkedList self = T##LinkedListInitChain(value, self);           \
    return self;                                                        \
}                                                                       \
T##LinkedList T##LinkedListFromArray(T arr[], size_t len) {             \
    assert(arr);                                                        \
    T##LinkedList self = T##LinkedListInitEmpty(arr[0]);                \
    T##LinkedList link = self;                                          \
    if(!self)                                                           \
        return NULL;                                                    \
    for(size_t i = 1; i < len; ++i) {                                   \
        bool result = T##LinkedListAppend(link, arr[i]);                \
        if(!result)                                                     \
            T##LinkedListFree(self);                                    \
        link = link->next;                                              \
    }                                                                   \
    return self;                                                        \
}                                                                       \
void T##LinkedListPrint(T##LinkedList self) {                           \
    printf("[ ");                                                       \
    while(self) {                                                       \
        printf("%lf, ", self->value);                                   \
        self = self->next;                                              \
    }                                                                   \
    printf("]\n");                                                      \
}                                                                       \
bool T##LinkedListContains(T##LinkedList self, T value) {               \
    while(self) {                                                       \
        if(self->value == value)                                        \
            return true;                                                \
        self = self->next;                                              \
    }                                                                   \
    return false;                                                       \
}                                                                       \

#endif /* LINKEDLIST_HEADER */