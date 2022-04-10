#include <ctype.h>

#include "HashT.h"
#include "List.h"

const uint32_t HT_CAPACITY = 15013;

typedef struct text {
    char* data;

    uint64_t size;
} Text;

Text* CreateText(char* fileName);
Text* DeleteText(Text* textToDel);

uint32_t fastLog2(uint32_t number);
