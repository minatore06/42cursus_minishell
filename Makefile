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

SRCS = \

OBJS = ${SRCS:.c=.o}

CC = gcc

RM = rm -f

FLAGS = -Wall -Werror -Wextra

LIBFT = libft

LIBFTNAME = libft.a
	
%.o: %.c
	${CC} ${FLAGS} -g -c $< -o ${<:.c=.o}

$(NAME): ${OBJS}
	make bonus -C ${LIBFT}
	mv ${LIBFT}/${LIBFTNAME} ${NAME}
	${CC} ${FLAGS} ${OBJS} ${NAME} -o ${OUT}

all: ${NAME}

bonus:	${OBJS}
	make bonus -C ${LIBFT}
	mv ${LIBFT}/${LIBFTNAME} ${NAME}
	${CC} ${FLAGS} ${OBJS} ${NAME} -o ${OUT}

clean: 
	${RM} ${OBJS}
	make clean -C ${LIBFT}

fclean: clean 
	${RM} ${NAME}
	make fclean -C ${LIBFT}

re: fclean all
