#include "function.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int write() {
        char *memory = malloc(sizeof(char)*MEMORY);
        srand(time(NULL));
        int randomNum = (rand() % (BYTES_MAX - BYTES_MIN)) + BYTES_MIN;
        
        int pagePrinted = (int)randomNum/256;
    
        int startNum = (rand() % ((256-pagePrinted)- 2)) + 2;
        int pageTime = startNum*256;

        int totalPagePrinted = pageTime+ randomNum;
        FILE *memoryOutput, *pageOutput;
        char memoryPhy[] = "/Users/alvinkhaimingteo/Desktop/Com/Operating_system/osCA1/data/physical_memory.txt";
        char pageTable[] = "/Users/alvinkhaimingteo/Desktop/Com/Operating_system/osCA1/data/page_table.txt";
        memoryOutput = fopen(memoryPhy, "w");
        pageOutput = fopen(pageTable, "w");
        fprintf(memoryOutput,"Address\t | Frame\t | Content\t | Use\n");
        fprintf(memoryOutput,"-------\t | --------\t | --------\t | --------\n");
        for(int i = 0; i < pageTime ; i++){
            fprintf(memoryOutput,"0x0%x\t | %d\t\t | \t\t\t | 0\n",i ,(int)i/256);
        }
        for(int i = pageTime; i <= totalPagePrinted; i++){
            char c = (rand()%(126-33)) + 33;
            memory[i] = c;
            fprintf(memoryOutput,"0x%x\t | %d\t\t | %c\t\t | 1\n",i ,(int)i/256 ,c);
        }
        for(int i = totalPagePrinted; i <= MEMORY; i++){
            fprintf(memoryOutput,"0x%x\t | %d\t\t | \t\t\t | 0\n",i ,(int)i/256);
        }

        fprintf(pageOutput,"Page\t | Frame\t | Use\n");
        fprintf(pageOutput,"-------\t | --------\t | --------\n");
        
        for(int i = 0; i <= pagePrinted ; i++){
            fprintf(pageOutput,"0x0%x\t | %d\t\t | 1\n",i ,startNum);
            startNum++;
        }   

        for(int i = pagePrinted+1; i < SIZE_PAGE ; i++){
            fprintf(pageOutput,"0x0%x\t |\t\t\t | 0\n",i );
        }   

        fclose(memoryOutput);
        fclose(pageOutput);
        return 0;
}
