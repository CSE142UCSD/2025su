#include <stdint.h>
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
void (*swap_array)(uint64_t* a, uint64_t* b, uint64_t size);

void inline swap(uint64_t* a, uint64_t* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
} 

void swap_array_1(uint64_t *a, uint64_t *b, uint64_t size)
{
    for (uint64_t i = 0; i < size; ++i) {
        swap(&a[i],&b[i]);
    }

}
void swap_array_2(uint64_t *a, uint64_t *b, uint64_t size)
{
    for (uint64_t i = 0; i < size; i++) {
        swap(&a[i],&b[i]);
        i++;
        swap(&a[i],&b[i]);
    }
}

void __attribute__((optimize("unroll-loops")))swap_array_3(uint64_t *a, uint64_t *b, uint64_t size)
{
    uint64_t real_size = size / 4;
    for (uint64_t i = 0; i < real_size*4; ++i) {
        swap(&a[i],&b[i]);
    }
}




int main(int argc, char **argv)
{
    unsigned array_size = 131072;
    uint64_t *data_a, *data_b;
    struct timeval time_start, time_end;
    array_size = (unsigned)atoi(argv[1]);
    if(argc > 2 && atoi(argv[2])==1)
        swap_array = swap_array_2;
    else if(argc > 2 && atoi(argv[2])==2)
        swap_array = swap_array_3;
    else
        swap_array = swap_array_1;
    data_a = (uint64_t *)malloc(sizeof(uint64_t)*array_size);
    data_b = (uint64_t *)malloc(sizeof(uint64_t)*array_size);
    for (unsigned i = 0; i < array_size; ++i)
        data_a[i] = rand();
    for (unsigned i = 0; i < array_size; ++i)
        data_b[i] = rand();
   gettimeofday(&time_start, NULL);
    swap_array(data_a,data_b,array_size);
   gettimeofday(&time_end, NULL);
   fprintf(stderr, "data_a[array_size/2] = %lu\t", data_a[rand()%131072]);
   fprintf(stderr, "swapped %lf seconds\n",((time_end.tv_sec * 1000000 + time_end.tv_usec) - (time_start.tv_sec * 1000000 + time_start.tv_usec))/1000000.0);
   return 0;
}
