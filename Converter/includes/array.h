#ifndef __ARRAY_H_
#define __ARRAY_H_

#include <stdlib.h>

typedef struct
{
  void **data;
  size_t sz_allocated;
  size_t sz_used;
} array_t;

void array_init(array_t *arr);
void array_append(array_t *arr, void *item);
void *array_read(array_t *arr, int index);

#endif // __ARRAY_H_
