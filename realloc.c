
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "malloc.h"

static void		*realloc_cpy(t_block_header *header,
				     size_t size, int power,
				     t_block_header *ptr)
{
  char			*new;
  unsigned int		oldsize;

  new = malloc(size);
  if (power > (int)header->power)
    oldsize = pow(2, header->power) - sizeof(t_block_header);
  else
    oldsize = size;
  if (oldsize > 0)
    memcpy(new, ptr, oldsize);
  free(ptr);
  return (new);
}

void			*realloc(void *ptr, size_t size)
{
  int			power;
  t_block_header	*header;

  if (ptr == NULL)
    return (malloc(size));
  if (size == 0)
    {
      free(ptr);
      return (NULL);
    }
  if ((power = get_power(size + sizeof(t_block_header))) == -1)
    return (NULL);
  header = (t_block_header*)((char*)ptr - sizeof(t_block_header));
  if ((header->used != USED && header->used != NOTUSED) ||
      (int)header->power < 0)
    {
      printf("error: realloc: invalid pointer.\n");
      return (NULL);
    }
  if (power == (int)header->power)
    return (ptr);
  return (realloc_cpy(header, size, power, ptr));
}
