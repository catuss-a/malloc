
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include "malloc.h"

static t_block_header	*get_ptr_gpower(int *i)
{
  t_block_header	*ptr;

  ptr = NULL;
  while (*i < 32)
    {
      if ((ptr = hashtab[*i]) != NULL)
	return (ptr);
      ++(*i);
    }
  return (ptr);
}

static void		block_fragmentation(t_block_header *ptr,
					     int nb_of_block,
					     int powersize,
					     int power)
{
  t_block_header	wrt;
  int			i;
  t_block_header	*next;
  t_block_header	*w;

  wrt.used = NOTUSED;
  wrt.power = power;
  i = 0;
  w = ptr;
  while (i < nb_of_block)
    {
      next = (t_block_header*)((char*)w + powersize);
      if (i == 1)
	hashtab[power] = w;
      if (i + 1 < nb_of_block)
	wrt.next = next;
      else
	wrt.next = NULL;
      memcpy(w, &wrt, sizeof(t_block_header));
      w = next;
      ++i;
    }
  ptr->used = USED;
}

static void		reinit_hashtab(t_block_header *ptr,
				       int *nb_of_block,
				       int powersize,
				       int i)
{
  if (ptr->used == USED)
    printf("ERROR 1 CHAMP USED ??? : at %p sbrk(0) = %p power = %d \n",
	   ptr, sbrk(0), ptr->power);
  else if (ptr->used != NOTUSED)
    printf("error :malloc dif de 42 et 24\n");
  hashtab[i] = hashtab[i]->next;
  *nb_of_block = pow(2, i) / powersize;
}

t_block_header		*find_or_make_block(int power)
{
  int			pagesize;
  int			allocsize;
  int			nb_of_block;
  int			i;
  int			powersize;
  t_block_header	*ptr;

  pagesize = getpagesize();
  powersize = (int)pow(2, power);
  i = power + 1;
  if (ptr = get_ptr_gpower(&i), ptr != NULL)
    reinit_hashtab(ptr, &nb_of_block, powersize, i);
  else
    {
      allocsize = ((powersize / pagesize)
		   + (powersize > pagesize ? 0 : 1)) * pagesize;
      if ((ptr = sbrk(allocsize)) == (void*)-1)
	{
	  printf("error: sbrk: an error has occured.\n");
	  return (NULL);
	}
      nb_of_block = allocsize / powersize;
    }
  block_fragmentation(ptr, nb_of_block, powersize, power);
  return (ptr);
}
