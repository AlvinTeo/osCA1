#ifndef FUNCTION
#define FUNCTION
#define OUTRANGEBITS 8
#define SIZE_PAGE 256
#define MEMORY 65536
#define DISK_MEMORY 512
#define SYSTEMBITS 16
#define BYTES_MAX 20480
#define BYTES_MIN 2048


int write(unsigned char *memory);

int get_input(unsigned char *memory, unsigned char *disk_memory);

int disk_memory_function(unsigned char *disk_memory);

int swap(unsigned char *memory, unsigned char *disk_memory, unsigned int pfn, unsigned int vpn);

#endif


   