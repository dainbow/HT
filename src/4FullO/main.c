#include "main.h"

int main(int argc, char** argv) {
    HashT* myHT = newHT(HT_CAPACITY);
    Text* inputText = CreateText(argv[1]);
    
    const __m256i spaces   = _mm256_set_epi8(' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    const __m256i newLines = _mm256_set_epi8('\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n', '\n');
    
    uint64_t lastWordIdx = 0;
    uint64_t wordCounter = 0;
    for (uint64_t curChar = 0; curChar < inputText->size; curChar += 32) {
        int32_t mask      = 0;
        __m256i curArr = _mm256_loadu_si256((const __m256i*)(inputText->data + curChar));

        mask |= _mm256_movemask_epi8(_mm256_cmpeq_epi8(curArr, spaces));
        mask |= _mm256_movemask_epi8(_mm256_cmpeq_epi8(curArr, newLines));
    
        while (mask) {
            uint32_t nowChar = curChar + fastLog2((mask & (mask - 1)) ^ mask);
            mask = mask & (mask - 1);

            if (nowChar != (lastWordIdx)) {
                inputText->data[nowChar] = '\0';
                wordCounter += insertHT(myHT, inputText->data + lastWordIdx, nowChar - lastWordIdx);
                // printf("%s\n", inputText->data + lastWordIdx);

                lastWordIdx = nowChar;
            }

            lastWordIdx++;
        }
    }

    Text* findText = CreateText(argv[2]);
    uint64_t findCounter   = 0;
    uint64_t findedCounter = 0;
    lastWordIdx = 0;

    for (uint64_t curChar = 0; curChar < findText->size; curChar += 32) {
        int32_t mask      = 0;
        __m256i curArr = _mm256_loadu_si256((const __m256i*)(findText->data + curChar));

        mask |= _mm256_movemask_epi8(_mm256_cmpeq_epi8(curArr, newLines));

        while (mask) {
            uint32_t nowChar = curChar + fastLog2((mask & (mask - 1)) ^ mask);
            mask = mask & (mask - 1);

            if (nowChar != (lastWordIdx)) {
                findCounter++;
                findText->data[nowChar] = '\0';
                List* find = findHT(myHT, findText->data + lastWordIdx, nowChar - lastWordIdx);

                if (find) {
                    // printf("FOUND %s\n", find->key);
                    findedCounter++;
                }

                
                lastWordIdx = nowChar;
            }

            lastWordIdx++;
        }
    }
    printf("All word amount is %lu\n"
           "Word to find amount is %lu\n"
           "Founded words amount is %lu\n", wordCounter, findCounter, findedCounter);

    
    myHT      = deleteHT(myHT);
    inputText = DeleteText(inputText);
    findText  = DeleteText(findText);
}

Text* CreateText(char* fileName) {
    assert(fileName);

    Text* newText = (Text*)calloc(1, sizeof(newText[0]));
    FILE* curFile = fopen(fileName, "rb");

    fseek(curFile, 0, SEEK_END);
    newText->size = ftell(curFile);
    fseek(curFile, 0, SEEK_SET);

    newText->data = (char*)calloc((newText->size / 32) * 32 + 32, sizeof(char));
    fread(newText->data, sizeof(char), newText->size, curFile);

    fclose(curFile);

    return newText;
}

Text* DeleteText(Text* textToDel) {
    assert(textToDel);

    free(textToDel->data);
    free(textToDel);

    return NULL;
}

uint32_t __attribute__ ((noinline)) fastLog2(uint32_t number) {
    __asm(".intel_syntax noprefix\n\t"
          "bsr eax, edi\n\t"
          "pop rbp\n\t"
          "ret\n\t"
          ".att_syntax prefix\n\t");
}
