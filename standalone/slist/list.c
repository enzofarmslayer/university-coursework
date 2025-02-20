#include "list.h"
#include <stdlib.h>
#include <stdio.h>

/* Puts x at the end of the list */
void append(struct list_item *first, int x){
    struct list_item *newLast = (struct list_item *)malloc(sizeof(struct list_item));

    newLast->value = x;

    if (first->next == NULL) {
        first->next = newLast;
        newLast->next = NULL;
        return;
    }

    struct list_item *current = first;
    struct list_item *next_item;

    while (current->next != NULL) {
        next_item = current->next;
        current = next_item;
    }
    
    current->next = newLast;
    newLast->next = NULL;
}

/* Puts x at the start of the list */
void prepend(struct list_item *first, int x) {
    struct list_item *newFirst = (struct list_item *)malloc(sizeof(struct list_item));

    newFirst->value = x;
    newFirst->next = first->next;
    first->next = newFirst;
}

/* Find the first element in the list larger than x and
 * put x right before that element */
void input_sorted(struct list_item *first, int x) {
    struct list_item *newItem = (struct list_item *)malloc(sizeof(struct list_item));

    struct list_item *current_item = first;
    struct list_item *next_item;
    while(current_item->next != NULL && current_item->next->value <= x) {
        next_item = current_item->next;
        current_item = next_item;
    }
    newItem->next = current_item->next;
    current_item->next = newItem;

    newItem->value = x;
}

/* Prints all elements in the list */
void print(struct list_item *first){
    if (first->next == NULL) {
        return;
    }

    struct list_item *current_item = first->next;
    struct list_item *next_item;
    while(current_item != NULL) {
        printf("%d",current_item->value);
        printf(", ");
        next_item = current_item->next;
        current_item = next_item;
    }
    printf("\n");
}

/* Free everything that is dynamically allocated */
void clear(struct list_item *first) {
    if (first->next == NULL) {
        return;
    }

    struct list_item *current = first->next;
    struct list_item *next;

    do
    {
        next = current->next;
        free(current);
        current = next;
    } while (current != NULL);

    first->next = NULL;
    
}


/* Implement the functions here */
