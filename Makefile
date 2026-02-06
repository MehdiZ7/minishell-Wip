# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 11:34:03 by mzouhir           #+#    #+#              #
#    Updated: 2026/02/06 14:11:42 by mzouhir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell
SRCS= 	main.c lexer/lexer.c lexer/lexer_utils.c lexer/handle_word.c lexer/handle_separator.c \
		env_parsing/env.c env_parsing/env_utils.c expansion/expansion.c main_utils.c \
		expansion/expansion_utils.c quotes_parsing/quotes.c ast_parsing/parser.c \
		ast_parsing/parser_utils.c
SRCS+= testing/check_token.c testing/check_ast.c
OBJS= ${addprefix ${OBJS_DIR}, ${SRCS:.c=.o}}
OBJS_DIR= Objs/
LIBFT_DIR = Libft
LIBFT= ${LIBFT_DIR}/libft.a
CC= cc
CFLAGS= -Wall -Werror -Wextra -g3
LINKERS= -lreadline
INCLUDES= -I includes -I ${LIBFT_DIR}

all: ${LIBFT} ${NAME}

${LIBFT}:
	${MAKE} -C ${LIBFT_DIR}

${NAME}: ${OBJS}
	${CC} ${CFLAGS} ${OBJS} ${LIBFT} ${LINKERS} -o ${NAME}

${OBJS_DIR}%.o: %.c
	mkdir -p ${@D}
	${CC} ${CFLAGS} ${INCLUDES} -c $< -o $@

clean:
	-rm -rf ${OBJS_DIR}
	${MAKE} -C ${LIBFT_DIR} clean
fclean: clean
	-rm -f ${NAME}
	${MAKE} -C ${LIBFT_DIR} fclean
re: fclean all

.PHONY: all clean fclean re
