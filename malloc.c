
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>
#include "malloc.h"

t_block_header		*hashtab[32];

static void		move_head_hashtab(t_block_header *ptr, int power)
{
  if (ptr->used == NOTUSED)
    ptr->used = USED;
  else if (ptr->used == USED)
    printf("ERROR 2 CHAMP USED ??? \n");
  else
    printf("in malloc : ERROR CHAMP USED != de 42 et 24 ??? \n");
  hashtab[power] = ptr->next;
}

void			*malloc(size_t size)
{
  int			power;
  t_block_header	*ptr;
  int			sizeblock;

  if (size > INT_MAX)
    return (NULL);
  sizeblock = size + sizeof(t_block_header);
  power = get_power(sizeblock);
  if ((ptr = hashtab[power]) == NULL)
    ptr = find_or_make_block(power);
  else
    move_head_hashtab(ptr, power);
  return ((char*)ptr + sizeof(t_block_header));
}
