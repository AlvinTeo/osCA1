#include "function.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Alvins-MacBook-Pro:osCA1 alvinkhaimingteo$ ./dist/main
// Alvins-MacBook-Pro:osCA1 alvinkhaimingteo$ make
// gcc -c -Wall lib/function.c -o dist/function.o
// gcc dist/main.o dist/function.o -o dist/main
// Alvins-MacBook-Pro:osCA1 alvinkhaimingteo$ ./dist/main
// Alvins-MacBook-Pro:osCA1 alvinkhaimingteo$

int write(unsigned char *memory)
{
    srand(time(NULL));
    int randomNum = (rand() % (BYTES_MAX - BYTES_MIN)) + BYTES_MIN;

    int pagePrinted = (int)randomNum / 256;

    int startNum = (rand() % ((256 - pagePrinted - 2) - 2)) + 2;
    int pageTime = startNum * 256;

    int totalPagePrinted = pageTime + randomNum;
    FILE *memoryOutput, *pageOutput;
    char memoryPhy[] = "/Users/alvinkhaimingteo/Desktop/Com/Operating_system/osCA1/data/physical_memory.txt";
    char pageTable[] = "/Users/alvinkhaimingteo/Desktop/Com/Operating_system/osCA1/data/page_table.txt";

    memoryOutput = fopen(memoryPhy, "w");
    pageOutput = fopen(pageTable, "w");

    fprintf(memoryOutput, "Address\t | Frame\t | Content\t | Present-Bit\n");
    fprintf(memoryOutput, "-------\t | --------\t | --------\t | --------\n");
    for (int i = 0; i < pageTime; i++)
    {
        if (i >= 512)
        {
            memory[i] = '$';
        }
        fprintf(memoryOutput, "0x0%x\t | %d\t\t | \t\t\t | 0\n", i, (int)i / 256);
    }
    for (int i = pageTime; i < totalPagePrinted; i++)
    {
        char c = (rand() % (126 - 33)) + 33;
        memory[i] = c;
        fprintf(memoryOutput, "0x%x\t | %d\t\t | %c\t\t | 1\n", i, (int)i / 256, c);
    }
    for (int i = totalPagePrinted; i < MEMORY; i++)
    {
        memory[i] = '$';
        fprintf(memoryOutput, "0x%x\t | %d\t\t | \t\t\t | 0\n", i, (int)i / 256);
    }

    fprintf(pageOutput, "Page\t | Frame\t | Present-Bit\n");
    fprintf(pageOutput, "-------\t | --------\t | --------\n");

    for (int i = 0; i <= pagePrinted; i++)
    {
        memory[i] = startNum;
        memory[256 + i] = 1;
        fprintf(pageOutput, "0x0%x\t | %x\t\t | 1\n", i, startNum);
        startNum++;
    }

    for (int i = pagePrinted + 1; i < SIZE_PAGE; i++)
    {
        int numberNew = pagePrinted + 1;
        if (i == numberNew)
        {
            fprintf(pageOutput, "0x0%x\t |\t\t\t | 0\n", i);
            memory[i] = 0x00;
        }
        else if (i == numberNew + 1)
        {
            fprintf(pageOutput, "0x0%x\t |\t\t\t | 0\n", i);
            memory[i] = 0x01;
        }
        else
        {
            fprintf(pageOutput, "0x0%x\t |\t\t\t | 0\n", i);
            memory[i] = '$';
        }
    }

    fclose(memoryOutput);
    // for(int i = 0; i < 65536; i++)
    // {
    //     printf("%dMemory:%x\n ",i,memory[i]);
    //             // if(memory[i] = 0){
    //             //     memory[i] = 'E';
    //             // }

    // }

    fclose(pageOutput);

    return 0;
}

int get_input(unsigned char *memory, unsigned char *disk_memory)
{
    unsigned int numOne;
    while (1)
    {
        printf("|********************************|\n");
        printf("| Please enter hexadecimal: ");
        scanf("%04x", &numOne);
        printf("|********************************|\n");
        unsigned int offset_mask = 0x00FF;
        unsigned int offset = numOne & offset_mask;

        unsigned int vpn = numOne >> OUTRANGEBITS;

        unsigned int pfn = memory[vpn];

        unsigned int add = pfn << OUTRANGEBITS;
        add |= offset;

        // printf("Offset: %x", offset);
        // printf("VPN: %x", vpn);
        // printf("pfn: %x", pfn);
        // printf("memory[vpn + 256] : %x\n", memory[vpn + 256]);
        // printf("256: %d\n", (vpn + 256));

        if (memory[vpn + 256] == 0)
        {
            swap(memory, disk_memory, pfn, vpn);
            printf("\n|~~~~~~~~~@OUTPUT@~~~~~~~~~~|\n");
            printf("\n|~~~~~~~~ PAGE FAULT ~~~~~~~|\n");
            printf("\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n");
        }
        else
        {
            printf("\n|~~~~~~~~~@OUTPUT@~~~~~~~~~~|");
            printf("\n\n|~~~~  Address: 0x%04x  ~~~~|\n", add);
            unsigned char content = memory[add];
            printf("\n|~~~~~~~  Content: %c  ~~~~~~|\n", content);
            printf("\n|~~~~~~~~~~~~~~~~~~~~~~~~~~~|\n\n");
        }
    }

    return 0;
}

int disk_memory_function(unsigned char *disk_memory)
{
    FILE *diskOutput;
    char disk[] = "/Users/alvinkhaimingteo/Desktop/Com/Operating_system/osCA1/data/disk.txt";
    diskOutput = fopen(disk, "w");
    fprintf(diskOutput, "Address\t | Frame\t | Content\t | Present-Bit\n");
    fprintf(diskOutput, "-------\t | --------\t | --------\t | --------\n");
    for (int i = 0; i < 512; i++)
    {
        char c = (rand() % (126 - 33)) + 33;
        disk_memory[i] = c;
        fprintf(diskOutput, "0x0%x\t | %d\t\t | %c\t\t | 1\n", i, (int)i / 256, c);
    }

    fclose(diskOutput);
    return 0;
}

int swap(unsigned char *memory, unsigned char *disk_memory, unsigned int pfn, unsigned int vpn)
{
    unsigned char pfn2 = '$';
    int d = 1;
    int starting_point = 512;
    printf("\nSWAPPING NOW PLEASE TRY AGAIN \n");

    for (int i = starting_point; i < MEMORY && d != 0; i++)
    {
        // printf("memory[i] for: %x", memory[i]);

        if (memory[i] == '$')
        {
            for (int j = 0; j < 256; j++)
            {
                memory[i + j] = disk_memory[pfn * 256 + j];
                // printf("inside for: %x", memory[i + j]);
            }
            pfn2 = (int)i / 256;
            i = MEMORY;
            d = 1;
        }
    }
    memory[vpn] = pfn2;
    // printf("MEMORY vpn %x %x", memory[vpn], vpn);
    memory[vpn + 256] = 0x01;
    return 0;
}