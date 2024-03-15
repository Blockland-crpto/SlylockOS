#include <system/mem.h>
#include <system/mltb/multibootinfo.h>
#include <string.h>
 
uintptr_t current_break;
int has_initialized = 0;
void *managed_memory_start;
void *last_valid_address;

typedef struct mem_control_block {
  int is_available;
  int size;
} mem_control_block;
mem_control_block pmcb; 
#define asizeof(x) ((char *)(&x + 1) - (char *)&x)

	
int ram_size() {
	return (mbi->mem_lower + mbi->mem_upper)+513;
}

void *sbrk(intptr_t incr)
{
    uintptr_t old_break = current_break;
    current_break += incr;
    return (void*) old_break;
}

void kalloc_init() {
  
  last_valid_address = sbrk(0);
  managed_memory_start = last_valid_address;
  has_initialized = 1;  
}
void kfree(void *firstbyte) {
  mem_control_block *mcb;
  mcb = firstbyte - asizeof(pmcb);
  mcb->is_available = 1;
  return;
}
void *kalloc(long numbytes) {
  void *current_location;
  mem_control_block *current_location_mcb;
  void *memory_location;
  if (!has_initialized) {
    kalloc_init();
  }
  numbytes = numbytes + asizeof(pmcb);
  memory_location = 0;
  current_location = managed_memory_start;
  while (current_location != last_valid_address) {
    current_location_mcb = (mem_control_block *)current_location;
    if (current_location_mcb->is_available) {
      if (current_location_mcb->size >= numbytes) {
        current_location_mcb->is_available = 0;
        memory_location = current_location;
        break;
      }
    }
    current_location = current_location + current_location_mcb->size;
  }
  if (!memory_location) {
    sbrk(numbytes);
    memory_location = last_valid_address;
    last_valid_address = last_valid_address + numbytes;
    current_location_mcb = memory_location;
    current_location_mcb->is_available = 0;
    current_location_mcb->size = numbytes;
  }
  memory_location = memory_location + asizeof(pmcb);
  return memory_location;
}

void bzero(void *s, int n)
{
  char * c = s; // Can't work with void *s directly.
  int i;
  for (i = 0; i < n; ++i)
    c[i] = '\0';
}