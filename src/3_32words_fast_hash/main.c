#include "main.h"

int main(int argc, char** argv) {
    HashT* myHT = newHT(HT_CAPACITY);
    Text* inputText = CreateText(argv[1]);
    
    uint64_t lastWordIdx = 0;
    uint64_t wordCounter = 0;
    for (uint64_t curChar = 0; curChar < inputText->size; curChar++) {
        if (isspace(inputText->data[curChar])) {
            inputText->data[curChar] = '\0';

            char* wordBuffer = calloc(WORD_LENGTH, sizeof(char));
            memcpy(wordBuffer, inputText->data + lastWordIdx, curChar - lastWordIdx);

            wordCounter += insertHT(myHT, wordBuffer);
            // printf("%s\n", inputText->data + lastWordIdx);

            while (isspace(inputText->data[++curChar])) {
                ;
            }

            lastWordIdx = curChar;
        }
    }
    inputText = DeleteText(inputText);

    Text* findText = CreateText(argv[2]);
    uint64_t findCounter   = 0;
    uint64_t findedCounter = 0;
    lastWordIdx = 0;

    char** words = calloc(500000, sizeof(char*));
    for (uint64_t curChar = 0; curChar < findText->size; curChar ++) {
        if (isspace(findText->data[curChar])) {
            words[findCounter] = calloc(WORD_LENGTH, sizeof(char));
            memcpy(words[findCounter], findText->data + lastWordIdx, curChar - lastWordIdx);

            findText->data[curChar] = '\0';
            List* find = findHT(myHT, words[findCounter++]);

            if (find) {
                // printf("FOUND %s\n", find->key);
                findedCounter++;
            }

            while (isspace(findText->data[++curChar])) {
                ;
            }
            
            lastWordIdx = curChar;
        }   
    }

    for (uint32_t curFindIter = 0; curFindIter < 200; curFindIter++) {
        for (uint32_t curWord = 0; curWord < findCounter; curWord++) {
            findHT(myHT, words[curWord]);
        }
    }

    printf("All word amount is %lu\n"
           "Word to find amount is %lu\n"
           "Founded words amount is %lu\n", wordCounter, findCounter, findedCounter);

    
    myHT      = deleteHT(myHT);
    
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

uint32_t fastLog2(uint32_t number) {
    for (uint32_t curDigit = 0; curDigit < 32; curDigit++) {
        if (number == ((uint32_t)1 << curDigit))
            return curDigit;
    }

    return 228;
}
