#include "List.h"

int32_t myStrcmp(char* str1, char* str2) {
    __m256i string1 = _mm256_load_si256((const __m256i*)str1);
    __m256i string2 = _mm256_load_si256((const __m256i*)str2);

    return ~_mm256_movemask_epi8(_mm256_cmpeq_epi8(string1, string2));
}

struct list* list_new(char* key) {
    struct list* newList = (struct list*)calloc(1, sizeof(struct list));
    if (newList == NULL)
        return NULL;

    newList->key   = key;

    newList->next = NULL;

    return newList;
}

struct list* list_insert(struct list* head, char* key) {
    if (head == NULL) {
        return list_new(key);
    }

    struct list* rememberHead = head;

    while (head->next != NULL) {
        head = head->next;
    }

    head->next = list_new(key);

    return rememberHead;
}

struct list* list_find (struct list* head, char* key) {
    if (head == NULL) {
        return head;
    }

    for (;;) {
        if (myStrcmp(head->key, key) == 0)
            return head;

        if (head->next != NULL)
            head = head->next;
        else
            break;
    }

    return NULL;
}

struct list* list_erase (struct list* head, char* key) {
    if (head == NULL)
        return NULL;

    if (myStrcmp(head->key, key)) {
        struct list* nodeToRet = head->next;
        
        free(head->key);
        free(head);
        return nodeToRet;
    }

    struct list* rememberHead = head;

    while (head->next != NULL) {
        if (myStrcmp(head->next->key, key)) {
            struct list* listToDel  = head->next;
            head->next              = head->next->next;

            free(listToDel);
            return rememberHead;
        }

        head = head->next;
    }
 
    return rememberHead;
}

struct list *list_insert_after(struct list *head, struct list *where, struct list *what) {
    if ((where == NULL) || (what == NULL))
        return head;
    
    if (head == NULL)
        return what;

    struct list* rememberHead = head;
    
    while (1) {
        if (head == where) {
            what->next = head->next;
            head->next = what;

            return rememberHead;
        }

        if (head->next != NULL)
            head = head->next;
        else
            break;
    }

    return NULL;
}

struct list *list_insert_before(struct list *head, struct list *where, struct list *what) {    
    if ((where == NULL) || (what == NULL))
        return head;
    
    if (head == NULL)
        return what;
    
    if (where == head) {
        what->next = where;
        return what;
    }

    struct list* rememberHead = head;

    while (head->next != NULL) {
        if (head->next == where) {
            head->next = what;
            what->next = where;

            return rememberHead;
        }
     

        head = head->next;
    }

    return NULL;
}

struct list* list_delete(struct list* head) {
    if (head == NULL)
        return NULL;
    
    while(head->next != NULL) {
        struct list* prevNode = head;

        head = head->next;

        free(prevNode);
    }

    free(head);
    return NULL;
}

struct list* list_next(struct list *curr) {
    if (curr == NULL)
        return NULL;

    return curr->next;
}

void list_print(struct list const *head) {
    printf("[");

    if (head != NULL) {
        while (head->next != NULL) {
            printf("%s, ", head->key);

            head = head->next;
        }

        printf("%s", head->key);
    }

    printf("]\n");
}
