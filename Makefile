# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fracerba <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/31 10:31:08 by fracerba          #+#    #+#              #
#    Updated: 2023/01/31 10:31:11 by fracerba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell.a

OUT = minishell

SRCS = builtins.c \
		builtins_2.c \
		builtins_utils.c \
		enviroment.c \
		error.c \
		exec_cmds.c \
		executor.c \
		executor2.c \
		expander.c \
		expander2.c \
		export_builtin.c \
		lexer.c \
		matrix.c \
		mini_utils.c \
		mini_utils2.c \
		minishell.c \
		parser.c \
		parser2.c \
		parser3.c \
		split_and_trim.c \

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Werror -Wextra

LINKS = -lreadline

LIBFT = libft

LIBFTNAME = libft.a
	
%.o: %.c
	${CC} ${FLAGS} -g -c $< -o ${<:.c=.o} ${LINKS}

$(NAME): ${OBJS}
	make bonus -C ${LIBFT}
	mv ${LIBFT}/${LIBFTNAME} ${NAME}
	${CC} ${FLAGS} ${OBJS} ${NAME} -o ${OUT} ${LINKS}

all: ${NAME}

bonus:	${OBJS}
	make bonus -C ${LIBFT}
	mv ${LIBFT}/${LIBFTNAME} ${NAME}
	${CC} ${FLAGS} ${OBJS} ${NAME} -o ${OUT} ${LINKS}

clean: 
	${RM} ${OBJS}
	make clean -C ${LIBFT}

fclean: clean 
	${RM} ${NAME}
	make fclean -C ${LIBFT}

re: fclean all
