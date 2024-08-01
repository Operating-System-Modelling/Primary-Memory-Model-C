/**
 * @author ECE 3058 TAs
 */

//Caches set ->

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cachesim.h"

// Statistics you will need to keep track. DO NOT CHANGE THESE.
counter_t accesses = 0;     // Total number of cache accesses
counter_t hits = 0;         // Total number of cache hits
counter_t misses = 0;       // Total number of cache misses
counter_t writebacks = 0;   // Total number of writebacks

/**
 * Function to perform a very basic log2. It is not a full log function, 
 * but it is all that is needed for this assignment. The <math.h> log
 * function causes issues for some people, so we are providing this. 
 * 
 * @param x is the number you want the log of.
 * @returns Techinically, floor(log_2(x)). But for this lab, x should always be a power of 2.
 */
int simple_log_2(int x) {
    int val = 0;
    while (x > 1) {
        x /= 2;
        val++;
    }
    return val; 
}

//  Here are some global variables you may find useful to get you started.
//      Feel free to add/change anyting here.
cache_set_t* cache;     // Data structure for the cache
int block_size;         // Block size
int cache_size;         // Cache size
int ways;               // Ways
int num_sets;           // Number of sets
int num_offset_bits;    // Number of offset bits
int num_index_bits;     // Number of index bits. 


//Globally
//tag bits, number of lines

/**
 * Function to intialize your cache simulator with the given cache parameters. 
 * Note that we will only input valid parameters and all the inputs will always 
 * be a power of 2.
 * 
 * @param _block_size is the block size in bytes
 * @param _cache_size is the cache size in bytes
 * @param _ways is the associativity
 */
void cachesim_init(int _block_size, int _cache_size, int _ways) {
    // Set cache parameters to global variables
    printf("Initializing cache simulator with: \n"); //print init parameters
    block_size = _block_size;
    cache_size = _cache_size;
    ways = _ways;

    ////////////////////////////////////////////////////////////////////
    //  TODO: Write the rest of the code needed to initialize your cache
    //  simulator. Some of the things you may want to do are:
    //      - Calculate any values you need such as number of index bits.
    //      - Allocate any data structures you need. 
    ////////////////////////////////////////////////////////////////////
    //Ashan's change
    printf("Seperating bits \n");
    num_sets = cache_size/(block_size*ways); //calculate the number of sets
    num_offset_bits = simple_log_2(block_size); //calculate the offset bits
    num_index_bits = simple_log_2(num_sets); // calculate the index bit 
    

    printf("number of offset bits %d\n",num_offset_bits);
    printf("number of index bits %d\n",num_index_bits);
    printf("Number of Sets %d\n",num_sets);

    cache = (cache_set_t*)malloc(sizeof(cache_set_t)*num_sets); //allocate memory for cache set array
    printf("Initialized cache and numset - %d\n",num_sets);
    for (int i=0; i<num_sets; i++){ //initialize each set
        //printf("Initialized set %d\n", i);
        cache[i].blocks = (cache_block_t*)malloc(sizeof(cache_block_t)*block_size); //allocate memory for blocks in each set
        cache[i].blocks->tag = 0; //initialize tag of each block
        cache[i].blocks->valid = 0; //initialize valid of each block
        cache[i].blocks->dirty = 0; //initialize dirty of each block
        cache[i].size = ways; //set size of each set
        //printf("initialized set\n");
        init_lru_stack(ways); //initialize lru stack
    }
    printf("ending initializtion of cache\n");
    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////
}

/**
 * Function to perform a SINGLE memory access to your cache. In this function, 
 * you will need to update the required statistics (accesses, hits, misses, writebacks)
 * and update your cache data structure with any changes necessary.
 * 
 * @param physical_addr is the address to use for the memory access. 
 * @param access_type is the type of access - 0 (data read), 1 (data write) or 
 *      2 (instruction read). We have provided macros (MEMREAD, MEMWRITE, IFETCH)
 *      to reflect these values in cachesim.h so you can make your code more readable.
 */
void cachesim_access(addr_t physical_addr, int access_type) {
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write the code needed to perform a cache access on your
    //  cache simulator. Some things to remember:
    //      - When it is a cache hit, you SHOULD NOT bring another cache 
    //        block in.
    //      - When it is a cache miss, you should bring a new cache block
    //        in. If the set is full, evict the LRU block.
    //      - Remember to update all the necessary statistics as necessary
    //      - Remember to correctly update your valid and dirty bits.  
    ////////////////////////////////////////////////////////////////////
    //Ashan's change
    //Seperate address into index and offset
    printf("Accessing cache with address %llu\n",physical_addr);
    int set_offset = (int)(physical_addr & ((1ULL << num_offset_bits) - 1));
    int set_index = (int)((physical_addr >> num_offset_bits) & ((1ULL << num_index_bits) - 1));
    int set_tag = (int)(physical_addr >> (num_offset_bits + num_index_bits));

    // printf("physical address: %llu\n", physical_addr);
    // printf("index bit: %d\n", set_index);
    // printf("offset bit: %d\n", set_offset);
    // printf("Tag bit : %d\n",set_tag);
    // printf("cache size %d\n", cache_size);
    //Check if hit or miss
    if (set_index < cache_size) {
        accesses++;
        printf("Accesses - %llu\n",accesses);
        int i = 0;
        while (i < ways) {
            printf("Checking valid bit: %d\n",cache[set_index].blocks[i].valid);
            if (cache[set_index].blocks[i].valid == 1) {
                printf("physical address: %llu\n", physical_addr);
                printf("index bit: %d\n", set_index);
                printf("offset bit: %d\n", set_offset);
                printf("Tag bit : %d\n",set_tag);
                if (cache[set_index].blocks[i].tag == set_tag) {
                    hits++; //read
                    break;
                }
            }
            i++;
        }
        if (i == ways) {
            misses++;
            //printf("Miss\n");
            i = 0;
            while (i < ways) {
                if (cache[set_index].blocks[i].valid == 0) {
                    cache[set_index].blocks[i].valid = 1;
                    cache[set_index].blocks[i].tag = set_tag;
                    break;
                }
                i++;
            }
            //printf("Set tag - %d\n",set_tag);
            if (i==ways) {
             i=lru_stack_get_lru(cache[set_index].stack);
             cache[set_index].blocks[i].valid = 1;
             cache[set_index].blocks[i].tag = set_tag;
             //printf("lru accessed");
            }
            //printf("Set index - %d\n",set_index);
        } 

        switch (access_type) {
        case 0: //data read
            //printf("Access type is data read.\n");
            break;
        case 1: //data write
            //printf("Access type is write.\n");
            cache[set_index].blocks[i].dirty = 1; //set dirty bit
            writebacks++;
            break;
        case 2: // instruction read
            //printf("Access type is instruction read.\n");
            break;
        default:
            printf("Invalid access type: %d\n", access_type);
            break;
    }
    }
    
    

    // 0 (data read), 1 (data write) or  2 (instruction read).
    //read and write and just change bit values
    //

    //use ValGrind to use memory leaks
    // write check dirty bits and update write back
    

    return;
    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////
}

/**
 * Function to free up any dynamically allocated memory you allocated
 */
void cachesim_cleanup() {
    ////////////////////////////////////////////////////////////////////
    //  TODO: Write the code to do any heap allocation cleanup
    ////////////////////////////////////////////////////////////////////
    // Free memory for cache blocks in each cache set
    for (int i = 0; i < num_sets; i++) {
        free(cache[i].blocks);
        lru_stack_cleanup(cache[i].stack);
    }
    // Free memory for the array of cache sets
    free(cache);
    ////////////////////////////////////////////////////////////////////
    //  End of your code   
    ////////////////////////////////////////////////////////////////////
}

/**
 * Function to print cache statistics
 * DO NOT update what this prints.
 * //outputs
 */
void cachesim_print_stats() {
    printf("%llu, %llu, %llu, %llu\n", accesses, hits, misses, writebacks);  
}

/**
 * Function to open the trace file
 * You do not need to update this function. 
 */
FILE *open_trace(const char *filename) {
    return fopen(filename, "r");
}

/**
 * Read in next line of the trace
 * 
 * @param trace is the file handler for the trace
 * @return 0 when error or EOF and 1 otherwise. 
 */
int next_line(FILE* trace) {
    if (feof(trace) || ferror(trace)) return 0;
    else {
        int t;
        unsigned long long address, instr;
        fscanf(trace, "%d %llx %llx\n", &t, &address, &instr);
        cachesim_access(address, t);
    }
    return 1;
}

/**
 * Main function. See error message for usage. 
 * 
 * @param argc number of arguments
 * @param argv Argument values
 * @returns 0 on success. 
 */
int main(int argc, char **argv) {
    FILE *input;

    if (argc != 5) {
        fprintf(stderr, "Usage:\n  %s <trace> <block size(bytes)>"
                        " <cache size(bytes)> <ways>\n", argv[0]);
        return 1;
    }
    
    input = open_trace(argv[1]);
    cachesim_init(atol(argv[2]), atol(argv[3]), atol(argv[4]));
    printf("main -Access Type, Address, Instruction\n"); //Ashan's change
    while (next_line(input));
    //printf("In main while loop\n");
    cachesim_print_stats();
    cachesim_cleanup();
    fclose(input);
    return 0;
}

