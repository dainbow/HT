#include "HashT.h"

#define H H6

uint32_t H1(char* s, uint32_t hashsize) {
    return 1 % hashsize;
}

uint32_t H2(char* s, uint32_t hashsize) {
    return s[0] % hashsize;
}

uint32_t H3(char* s, uint32_t hashsize) {
    uint32_t sum = 0;
    __asm__ (".intel_syntax noprefix;"
            "push %1;"
            "mov ecx, 32;"
            "xor rax, rax;"
            "xor rdx, rdx;"
            "lop%=:"
            "cmp ecx, 0;"
            "je end%=;"
            "xor ebx, ebx;"
            "mov bl, [%1];"
            "add eax, ebx;"
            "inc %1;"
            "dec ecx;"
            "jmp lop%=;"
            "end%=:"
            "pop %1;"
            "div rsi;"
            "mov rax, rdx;"
            "mov %0, eax;"
            ".att_syntax prefix;"
            : "=r" (sum)
            : "r" (s)
            : "ecx", "rax", "ebx", "rdx");

    return sum;
}

uint32_t H4(char* s, uint32_t hashsize) {
    return strlen(s) % hashsize;
}

uint32_t H5(char* s, uint32_t hashsize) {
    
}

uint32_t H6(char* s, uint32_t hashsize) {
    uint32_t hash = 0;

    for (uint32_t curPart = 0; curPart < 4; curPart++) {
        hash = _mm_crc32_u64(hash, *((uint64_t*)s));

        s += 8;
    }

    return hash % hashsize;
}

struct hashT* newHT(uint64_t capacity, uint32_t (*hash)(char*, unsigned)) {
    struct hashT* h = (struct hashT*)calloc(1, sizeof(struct hashT));
    if (h == NULL)
        return h;

    h->data  = (List**)calloc(h->capacity = capacity, sizeof(h->data[0]));
    h->hash  = hash;

    if (h->data == NULL) {
        free(h->data);
        free(h);

        return NULL;
    }
    
    return h;
}

List* findHT(struct hashT* hT, char* key) {
    assert(hT != NULL);

    uint32_t keyHash = hT->hash(key, hT->capacity);
    List* findedList = list_find(hT->data[keyHash], key);

    return findedList; 
}

int32_t insertHT(struct hashT* hT, char* key) {
    assert(hT != NULL);

    uint32_t keyHash  = hT->hash(key, hT->capacity);
    if (list_find(hT->data[keyHash], key) == NULL) {
        hT->data[keyHash] = list_insert(hT->data[keyHash], key);

        return 1;
    }

    return 0;
}

void eraseHT(struct hashT* hT, char* key) {
    assert(hT != NULL);

    uint32_t keyHash  = hT->hash(key, hT->capacity);
    hT->data[keyHash] = list_erase(hT->data[keyHash], key);
}

struct hashT* deleteHT(struct hashT* hT) {
    if (hT == NULL)
        return NULL;

    for (uint32_t curElem = 0; curElem < hT->capacity; curElem++) {
        hT->data[curElem] = list_delete(hT->data[curElem]);
    }

    free(hT->data);
    free(hT);
    return NULL;    
}
