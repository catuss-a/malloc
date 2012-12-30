
#include <stdlib.h>
#include <string.h>
#include "malloc.h"

void			*calloc(size_t nmemb, size_t size)
{
  unsigned int		s;
  char			*ptr;

  s = nmemb * size;
  if ((ptr = malloc(s)) == NULL)
    return (NULL);
  memset(ptr, 0, s);
  return (ptr);
}
