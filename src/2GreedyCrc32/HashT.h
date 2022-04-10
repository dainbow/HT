#ifndef _HASHT_H_
#define _HASHT_H_

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <immintrin.h>

#include "List.h"

typedef struct hashT {
    List** data;

    uint32_t capacity;
} HashT;

uint32_t H1(char* s, uint32_t hashsize, uint32_t stringSize);
uint32_t H2(char* s, uint32_t hashsize, uint32_t stringSize);
uint32_t H3(char* s, uint32_t hashsize, uint32_t stringSize);
uint32_t H4(char* s, uint32_t hashsize, uint32_t stringSize);
uint32_t H5(char* s, uint32_t hashsize, uint32_t stringSize);
uint32_t H6(char* s, uint32_t hashsize, uint32_t stringSize);

struct hashT* newHT(uint64_t capacity);
List* findHT(struct hashT* hT, char* key, uint32_t value);

int32_t insertHT(struct hashT* hT, char* key, uint32_t value);
void eraseHT(struct hashT* hT, char* key, uint32_t value);

struct hashT* deleteHT(struct hashT* hT);

#endif
