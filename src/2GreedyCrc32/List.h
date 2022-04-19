#ifndef _LIST_H_
#define _LIST_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct list {
    char* key;

    struct list* next;
} List;

struct list* list_new(char* key);
struct list* list_insert(struct list* head, char* key);

struct list* list_find (struct list* head, char* key);
struct list* list_erase (struct list* head, char* key);
struct list* list_insert_after(struct list *head, struct list *where, struct list *what);
struct list* list_insert_before(struct list *head, struct list *where, struct list *what);
struct list* list_delete(struct list* head);
struct list* list_next(struct list *curr);
void list_print(struct list const *head);

#endif
