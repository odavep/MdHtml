#include "../includes/array.h"
#include <malloc.h>

void array_init(array_t **arr)
{
  (*arr) = malloc(sizeof(*arr));
  (*arr)->sz_used = 0;
  (*arr)->sz_allocated = 8;
  (*arr)->data = malloc((*arr)->sz_allocated);
}

void array_append(array_t *arr, void *data)
{
  if (arr->sz_allocated == arr->sz_used)
  {
    arr->sz_allocated *= 2;
    arr->data = realloc(arr->data, arr->sz_allocated);
  }
  arr->data[arr->sz_used] = data;
  ++arr->sz_used;
}

void *array_read(array_t *arr, int index)
{
  if (index > arr->sz_used)
    return NULL;
  return arr->data[index];
}
