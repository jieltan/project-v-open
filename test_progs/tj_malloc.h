//////////////////////////////////////////////////////
// tj_malloc.h
// this provides a pseudo malloc that we can use
// this implementation of malloc is O(n^2)
// and free is O(n), so not the most efficient malloc
// 
// since we are allocating everything statically
// we can only keep track of so many mallocs,
// and the default number is 16
// Jielun Tan and James Connolly, 02/2019
/////////////////////////////////////////////////////

#include<stdbool.h>
#include<stdint.h>
#include<stdlib.h>

#define HEAP_SIZE 2048
#define NUM_TRACKER 16
static unsigned char heap[HEAP_SIZE]; //reserve 2 KiB for malloc
static void* next_index = (void *)heap; //the next place to be allocated
static unsigned int avail_mem = sizeof(heap); //the most CONTIGUOUS memory available

typedef struct {
	void* start_pointer;
	uint16_t size;
	bool valid;
}tracker_t;

static tracker_t Tracker[NUM_TRACKER];

void *tj_malloc(unsigned int size) {
	//we want strict word alignment just to make things easier
	//and so that we don't have improper alignment issues
	if ((size & 3) != 0) {
		size = size + 4 - (size & 3);
	}

	// this is the pointer that gets returned
    void *mem = NULL;
	int tracker_index;
	bool tracker_avail = 0;
	unsigned int most_avail_mem;
	unsigned int mem_gap;
	unsigned int least_avail_mem;
	void* current_index;
	unsigned int current_size;

    if((size < avail_mem)) {
		for (int i = 0; i < NUM_TRACKER; ++i) {
			if (!Tracker[i].valid) {
				tracker_avail = 1;
				tracker_index = i;
				break;
			}
		}
		if (tracker_avail) {
		    mem = next_index;
			next_index += size;
			most_avail_mem = avail_mem - size;
			for (int i = 0; i < NUM_TRACKER; ++i) {
				if (Tracker[i].valid) {
					current_index = Tracker[i].start_pointer;
					current_size  = Tracker[i].size;
					for (int j = 0; j < NUM_TRACKER; ++j) {
						if ((i != j) && Tracker[j].valid && 
							(current_index < Tracker[j].start_pointer)) {
							mem_gap = Tracker[j].start_pointer - current_index - current_size;
							least_avail_mem = (mem_gap < least_avail_mem) ? mem_gap : least_avail_mem;
						}
					}
					if (least_avail_mem > most_avail_mem) {
						most_avail_mem = least_avail_mem;
						next_index = current_index + current_size;
					}
				}			
			}
			avail_mem = most_avail_mem;

			Tracker[tracker_index].start_pointer = mem;
			Tracker[tracker_index].size = (uint16_t)size;
			Tracker[tracker_index].valid = 1;
		}
	}
    return mem;
}

void tj_free(void *mem) {

	int tracker_index;
	bool found = 0;
	for (int i = 0; i < NUM_TRACKER; ++i) {
		if (Tracker[i].valid && (Tracker[i].start_pointer == mem)) {
			tracker_index = i;
			found = 1;
			break;
		}
	}
	if (!found) exit(1);

	unsigned int most_avail_mem;
	unsigned int mem_gap;
	unsigned int least_avail_mem;
	void* current_index;
	unsigned int current_size;
	most_avail_mem = avail_mem;
	for (int j = 0; j < NUM_TRACKER; ++j) {
		if ((tracker_index != j) && Tracker[j].valid && 
			(Tracker[tracker_index].start_pointer < Tracker[j].start_pointer)) {
			mem_gap = Tracker[j].start_pointer - Tracker[tracker_index].start_pointer;
			least_avail_mem = (mem_gap < least_avail_mem) ? mem_gap : least_avail_mem;
		}
	}
	if (least_avail_mem > most_avail_mem) {
		most_avail_mem = least_avail_mem;
		next_index = Tracker[tracker_index].start_pointer;
	}
	Tracker[tracker_index].valid = 0;

	avail_mem = most_avail_mem;
}
