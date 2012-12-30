
CC		=	gcc

NAME		=	libmy_malloc.so

SRCS		=	malloc.c		\
			free.c			\
			calloc.c		\
			find_or_make_block.c	\
			realloc.c		\
			get_power.c		

OBJS		=	$(SRCS:.c=.o)

CFLAGS		+=	-W -Wall -lm -g

RM		=	rm -f
ECHO		=	@echo

$(NAME)		:	$(OBJS)
			$(CC) -shared -o $(NAME) $(OBJS) $(CFLAGS)
			$(ECHO) ""
			$(ECHO) "[ SUCCESS ]"

all		:	$(NAME)

.c.o		:
			$(CC) -fPIC -c -o $@ $< $(CFLAGS)

clean		:
			$(RM) $(OBJS)
			$(RM) *~

fclean		:	clean
			$(RM) $(NAME)

re		:	fclean all

.PHONY		:	clean fclean re
