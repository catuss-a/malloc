
#ifndef _MALLOC_H_
# define _MALLOC_H_

# define USED 42
# define NOTUSED 24

typedef struct s_block_header t_block_header;

struct			s_block_header
{
  unsigned int		power;
  int			used;
  struct s_block_header	*next;
};

extern t_block_header	*hashtab[32];

t_block_header		*find_or_make_block(int power);
int                     get_power(size_t size);
int			getpagesize(void);
int			brk(void *addr);
void			free(void *ptr);
void			*calloc(size_t nmemb, size_t size);
void			*realloc(void *ptr, size_t size);

#endif /* !_MALLOC_H_ */
