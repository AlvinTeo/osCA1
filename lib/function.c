s#include "function.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int write() {
	fprintf("Memory Output /t Address/t");
	char *memory = malloc(sizeof(char)*MEMORY);
	srand(time(NULL));
	int randomNum = (rand() % (BYTES_MAX - BYTES_MIN)) + BYTES_MIN;
	FILE *memoryOutput, *pageOutput;
	char memoryPhy[] = "./data/physical_memory.txt";
	char pageTable[] = "./data/page_table.txt";
	memoryOutput = fopen(memoryPhy, "w");
	pageOutput = fopen(pageTable, "w");
	fclose(memoryOutput);
	fclose(pageOutput);
	return 0;
}
