#include "header.h"

double generate_num();

int main(int argc, char *argv[]) 
{
    if (argc != 3) 
    {
        fprintf(stderr, "USE NEXT PATTERN: %s INDEX_SIZE FILENAME\n", argv[0]);
        return EXIT_FAILURE;
    }

    int recs = (int) strtol(argv[1], NULL, 10);
    if (recs % 256 != 0) 
    {
        fprintf(stderr, "INDEX_SIZE SHOULD BE DIVISIBLE BY 256!!!\n");
        return EXIT_FAILURE;
    }

    int pagesize = getpagesize();
    if (recs < pagesize || recs % pagesize) 
    {
        fprintf(stderr, "INDEX_SIZE SHOULD BE BIGGER THAN PAGESIZE!!!\n");
        return EXIT_FAILURE;
    }

    index_hdr_s head;
    head.records = recs;
    char *filename = argv[2];
    FILE *f = fopen(filename, "wb");

    fwrite(&head, sizeof(index_hdr_s), 1, f); 

    srandom(time(NULL));
    for (int i = 0; i < recs; ++i)
    {
        index_s record;
        record.time_mark = generate_num();
        record.recno = i + 1;
        fwrite(&record, sizeof(struct index_s), 1, f);
    }
    fclose(f);
    
    print(filename, 0);
    printf("%s CREATED AND FILLED WITH DATA\n\n", filename);

    return 0;
}

double generate_num()
{
    long maxnum = 15020;
    time_t curtime = time(NULL);
    time_t yesterday = curtime / (24 * 60 * 60) - 1;
    long rand_int = maxnum + random() % (yesterday - maxnum + 1);
    
    double rand_double = (double) random() / ((double) RAND_MAX + 1 / 2.0f) + 0.5;
    
    double finalnum = (double) rand_int + rand_double;

    return finalnum;
}