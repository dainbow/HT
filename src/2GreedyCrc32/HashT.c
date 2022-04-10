#include "HashT.h"

#define H H6

uint32_t H1(char* s, uint32_t hashsize, uint32_t stringSize) {
    return 1 % hashsize;
}

uint32_t H2(char* s, uint32_t hashsize, uint32_t stringSize) {
    return s[0] % hashsize;
}

uint32_t H3(char* s, uint32_t hashsize, uint32_t stringSize) {
    uint32_t sum = 0;

    while(*s) {
        sum += *s++;
    }

    return sum % hashsize;
}

uint32_t H4(char* s, uint32_t hashsize, uint32_t stringSize) {
    return stringSize % hashsize;
}

uint32_t H5(char* s, uint32_t hashsize, uint32_t stringSize) {
    uint32_t hash = *s++;

    while (*s) {
        hash = (hash >> 31) + (hash << 1) + *s++;
    }

    return hash % hashsize;
}

uint32_t H6(char* s, uint32_t hashsize, uint32_t stringSize) {
    uint32_t hash = 0;

    while (stringSize >> 3) {
        hash = _mm_crc32_u64(hash, *((uint64_t*)s));

        s += 8;
        stringSize -= 8;
    }

    if (stringSize >> 2) {
        hash = _mm_crc32_u32(hash, *((uint32_t*)s));

        s += 4;
        stringSize -= 4;
    }

    if (stringSize >> 1) {
        hash = _mm_crc32_u16(hash, *((uint16_t*)s));

        s += 2;
        stringSize -= 2;
    }

    if (stringSize) {
        hash = _mm_crc32_u8(hash, *s);

        s++;
        stringSize--;
    }

    return hash % hashsize;
}

struct hashT* newHT(uint64_t capacity) {
    struct hashT* h = (struct hashT*)calloc(1, sizeof(struct hashT));
    if (h == NULL)
        return h;

    h->data  = (List**)calloc(h->capacity = capacity, sizeof(h->data[0]));
    
    if (h->data == NULL) {
        free(h->data);
        free(h);

        return NULL;
    }
    
    return h;
}

List* findHT(struct hashT* hT, char* key, uint32_t value) {
    assert(hT != NULL);

    uint32_t keyHash = H(key, hT->capacity, value);
    List* findedList = list_find(hT->data[keyHash], key);

    return findedList; 
}

int32_t insertHT(struct hashT* hT, char* key, uint32_t value) {
    assert(hT != NULL);

    uint32_t keyHash  = H(key, hT->capacity, value);
    
    if (list_find(hT->data[keyHash], key) == NULL) {
        hT->data[keyHash] = list_insert(hT->data[keyHash], key);

        return 1;
    }
    return 0;
}

void eraseHT(struct hashT* hT, char* key, uint32_t value) {
    assert(hT != NULL);

    uint32_t keyHash  = H(key, hT->capacity, value);
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
