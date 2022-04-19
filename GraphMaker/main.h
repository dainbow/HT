#include <ctype.h>

#include "HashT.h"
#include "List.h"

const uint32_t HT_CAPACITY = 2003;
const uint32_t WORD_LENGTH = 32;

struct word {
    char* data;
    
    uint32_t length;
};

typedef struct text {
    char* data;

    uint64_t size;
} Text;

void MakePlot(uint32_t x1, uint32_t x2, char* dataName, char* outputName, char* scriptName, char* plotName);
void calculate(int argc, char** argv, uint32_t (*hash)(char*, uint32_t), FILE* output);

Text* CreateText(char* fileName);
Text* DeleteText(Text* textToDel);

uint32_t fastLog2(uint32_t number);
