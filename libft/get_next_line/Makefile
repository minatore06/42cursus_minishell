CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=getnextline.a

FILES=get_next_line.c get_next_line_utils.c
OBJECTS=$(FILES:.c=.o)

BONUS=get_next_line_bonus.c get_next_line_utils_bonus.c
BONUS_OBJECTS=$(FILES:.c=.o)

LIBFT=../

all: $(NAME)

$(NAME): $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

bonus: $(BONUS_OBJECTS)
	ar rcs $(NAME) $(BONUS_OBJECTS)

clean:
	rm -f $(OBJECTS) $(BONUS_OBJECTS)

fclean: clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re
