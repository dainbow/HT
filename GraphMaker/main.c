#include "main.h"

int main(int argc, char** argv) {
    // FILE* H1F = fopen("./data/H1.txt", "w");
    // calculate(argc, argv, H1, H1F);
    // fclose(H1F);
    // MakePlot(0, 200, "./data/H1.txt", "./plots/H1.png", "./scripts/H1.plot", "Always 1 hash");

    FILE* H2F = fopen("./data/H2.txt", "w");
    calculate(argc, argv, H2, H2F);
    fclose(H2F);
    MakePlot(0, 200, "./data/H2.txt", "./plots/H2.png", "./scripts/H2.plot", "First ascii code");

    FILE* H3F = fopen("./data/H3.txt", "w");
    calculate(argc, argv, H3, H3F);
    fclose(H3F);
    MakePlot(0, HT_CAPACITY, "./data/H3.txt", "./plots/H3.png", "./scripts/H3.plot", "Ascii sum");

    FILE* H4F = fopen("./data/H4.txt", "w");
    calculate(argc, argv, H4, H4F);
    fclose(H4F);
    MakePlot(0, 200, "./data/H4.txt", "./plots/H4.png", "./scripts/H4.plot", "String length");

    // FILE* H5F = fopen("H5.txt", "w");
    // calculate(argc, argv, H5, H5F);
    // fclose(H5F);

    FILE* H6F = fopen("./data/H6.txt", "w");
    calculate(argc, argv, H6, H6F);
    fclose(H6F);
    MakePlot(0, HT_CAPACITY, "./data/H6.txt", "./plots/H6.png", "./scripts/H6.plot", "Crc32 hash");
}

void MakePlot(uint32_t x1, uint32_t x2, char* dataName, char* outputName, char* scriptName, char* plotName) {
    FILE* scriptF = fopen(scriptName, "w");

    fprintf(scriptF, "set terminal png size 1280, 720\n");
    fprintf(scriptF, "set xrange[%u:%u]\n", x1, x2);
    fprintf(scriptF, "set output \"%s\"\n", outputName);
    
    fprintf(scriptF, "set xlabel \"List index\"\n");
    fprintf(scriptF, "set ylabel \"Amount of collisions\"\n");
    fprintf(scriptF, "set title \"%s\" font \"Helvetica Bold, 20\"\n", plotName);
    fprintf(scriptF, "set xtics %u, %u, %u\n", x1, (x2 - x1) / 20, x2);

    fprintf(scriptF, "plot \"%s\" with lines\n", dataName);

    fclose(scriptF);
    
    char command[100] = "";
    sprintf(command, "gnuplot %s", scriptName);
    system(command);
}

void calculate(int argc, char** argv, uint32_t (*hash)(char*, uint32_t), FILE* output) {
    HashT* myHT = newHT(HT_CAPACITY, hash);
    Text* inputText = CreateText(argv[1]);

    uint64_t lastWordIdx = 0;
    uint64_t wordCounter = 0;
    for (uint64_t curChar = 0; curChar < inputText->size; curChar++) {
        if (isspace(inputText->data[curChar])) {
            inputText->data[curChar] = '\0';

            char* wordBuffer = aligned_alloc(32, WORD_LENGTH * sizeof(char));
            memset(wordBuffer, 0, WORD_LENGTH);
            memmove(wordBuffer, inputText->data + lastWordIdx, curChar - lastWordIdx);

            wordCounter += insertHT(myHT, wordBuffer);
            // printf("%s\n", inputText->data + lastWordIdx);

            while (isspace(inputText->data[++curChar])) {
                ;
            }

            lastWordIdx = curChar;
        }
    }
    inputText = DeleteText(inputText);

    for (uint32_t curList = 0; curList < myHT->capacity; curList++) {
        uint32_t listSize = 0;
        
        for (struct list* curNode = myHT->data[curList]; curNode; curNode = curNode->next) {
            listSize++;
        }

        fprintf(output, "%u %u\n", curList, listSize);
    }
    
    myHT      = deleteHT(myHT);
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
