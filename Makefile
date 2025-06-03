##
## EPITECH PROJECT, 2024
## MAKEFILE
## File description:
## FILEMAKE
##

CC	?=	gcc

SRC 	=	src/file_to_word_array.c	\
			src/lingo.c					\
			src/main.c					\
			src/my_strsplt.c			\
			src/nfree.c					\
			src/prompt.c

NAME	=	lingo

VPATH	=	./include

CFLAGS	+=	-Wall -Wextra -pedantic -std=c2x -D_POSIX_C_SOURCE=202311L

CPPFLAGS	+=	-iquote $(VPATH)

OBJ	= $(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ) $(LDFLAGS)

clean:
	$(RM) $(OBJ)

fclean: clean
	$(RM) $(NAME)

re: fclean all

debug: CFLAGS += -g3
debug: re

.PHONY: all clean fclean re debug
