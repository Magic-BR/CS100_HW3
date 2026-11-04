/* CS100 Fall 2026 - HW3 Problem 4: Memory Leak Checker
 *
 * Implement a tiny memory-leak / invalid-free detector. This file is
 * #included by the course driver (like a header): it must define
 * recorded_malloc / recorded_calloc / recorded_free, the check_leak
 * destructor, and the malloc/calloc/free macros, exactly as described in
 * the handout. Do NOT write a main function here. Do not rename this file.
 */
#ifndef CS100_MEMCHECK_H
#define CS100_MEMCHECK_H 1

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_RECORDS 1000

struct Record {
    void *ptr;              /* address of the allocated memory */
    size_t size;            /* size of the allocated memory */
    int line_no;            /* line number of the malloc/calloc call */
    const char *file_name;  /* file in which the call happens */
};

static struct Record records[MAX_RECORDS];

static void add_record(void *p, size_t sz, int line, const char *fname)
{
    for (int i = 0; i < MAX_RECORDS; ++i)
    {
        if (records[i].ptr == NULL)
        {
            records[i].ptr = p;
            records[i].size = sz;
            records[i].line_no = line;
            records[i].file_name = fname;
            break;
        }
    }
}

void *recorded_malloc(size_t size, int line, const char *file)
{
    void *ptr = malloc(size);
    if (ptr != NULL)
    {
        add_record(ptr, size, line, file);
    }
    return ptr;
}

void *recorded_calloc(size_t cnt, size_t each_size, int line, const char *file)
{
    void *ptr = calloc(cnt, each_size);
    if (ptr != NULL)
    {
        add_record(ptr, cnt * each_size, line, file);
    }
    return ptr;
}

void recorded_free(void *ptr, int line, const char *file)
{
    if (ptr == NULL)
    {
        free(ptr);
        return;
    }
    int found = 0;
    for (int i = 0; i < MAX_RECORDS; ++i)
    {
        if (records[i].ptr == ptr)
        {
            records[i].ptr = NULL;
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Invalid free in file %s, line %d\n", file, line);
    }
    free(ptr);
}

void check_leak(void) __attribute__((destructor));
void check_leak(void)
{
    size_t leak_bytes = 0;
    int leak_cnt = 0;
    printf("Summary:\n");
    for (int i = 0; i < MAX_RECORDS; ++i)
    {
        if (records[i].ptr != NULL)
        {
            printf("%zu bytes memory not freed (allocated in file %s, line %d)\n",
                   records[i].size, records[i].file_name, records[i].line_no);
            leak_bytes += records[i].size;
            leak_cnt++;
        }
    }
    if (leak_cnt == 0)
    {
        printf("All allocations have been freed.\n");
    }
    else
    {
        printf("%d allocation records not freed (%zu bytes in total).\n", leak_cnt, leak_bytes);
    }
}
/* TODO: the records array, recorded_malloc / recorded_calloc /
 * recorded_free, and check_leak, then the three macros below. */

#define malloc(SIZE) recorded_malloc(SIZE, __LINE__, __FILE__)
#define calloc(CNT, EACH_SIZE) recorded_calloc(CNT, EACH_SIZE, __LINE__, __FILE__)
#define free(PTR) recorded_free(PTR, __LINE__, __FILE__)

#endif /* CS100_MEMCHECK_H */
