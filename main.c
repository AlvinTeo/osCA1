#include <stdio.h>
#include "lib/function.h"
#include <time.h>
#include <stdlib.h>

int main(){
	unsigned char *memory = malloc(sizeof(char)*MEMORY);
	unsigned char *disk_memory = malloc(sizeof(char)*DISK_MEMORY);
	write(memory);
	disk_memory_function(disk_memory);

	get_input(memory, disk_memory);
	
	free(memory);
	free(disk_memory);
	return 0;
}
