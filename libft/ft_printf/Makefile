CC=gcc
CFLAGS=-Wall -Wextra -Werror
NAME=libftprintf.a

FILES=ft_printf.c ft_printf_manage_flags1.c ft_printf_manage_flags2.c ft_printf_manage_flags_master.c ft_printf_manage_flags_general.c ft_printf_manage_nbr.c ft_printf_manage_ptr.c ft_printf_put.c ft_printf_utils.c
OBJECTS=$(FILES:.c=.o)

GETNEXTLINE=../get_next_line/
GETNEXTLINENAME=getnextline.a

all: $(NAME)



$(NAME): $(OBJECTS)
	$(MAKE) -C $(GETNEXTLINE)
	mv $(GETNEXTLINE)$(GETNEXTLINENAME) $(NAME)
	ar rcs $(NAME) $(OBJECTS)

bonus: $(OBJECTS)
	$(MAKE) bonus -C $(GETNEXTLINE)
	mv $(GETNEXTLINE)$(GETNEXTLINENAME) $(NAME)
	ar rcs $(NAME) $(OBJECTS)

clean:
	rm -f $(OBJECTS)
	$(MAKE) clean -C $(GETNEXTLINE)

fclean: clean
	rm -f $(NAME)
	rm -f $(GETNEXTLINE)$(GETNEXTLINENAME)

re:	fclean all

.PHONY:	all clean fclean re
