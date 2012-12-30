
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "malloc.h"

void			free(void *ptr)
{
  t_block_header	*p;
  int			power;

  if (!ptr)
    return ;
  p = (t_block_header*)((char*)ptr - sizeof(t_block_header));
  if (p->used == NOTUSED)
    {
      printf("error: free: junk ptr.\n");
      return ;
    }
  power = p->power;
  p->used = NOTUSED;
  p->next = hashtab[power];
  hashtab[power] = p;
}
