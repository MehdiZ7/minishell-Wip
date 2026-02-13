# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lmilando <lmilando@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 11:34:03 by mzouhir           #+#    #+#              #
#    Updated: 2026/02/12 10:18:32 by lmilando         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell
SRCS= 	main.c lexer/lexer.c lexer/lexer_utils.c lexer/handle_word.c lexer/handle_separator.c \
		env_parsing/env.c env_parsing/env_utils.c expansion/expansion.c main_utils.c \
		expansion/expansion_utils.c quotes_parsing/quotes.c ast_parsing/parser.c \
		ast_parsing/parser_utils.c ast_parsing/print_parser.c ast_parsing/parser_infix_topostfix.c execution/master_execution.c execution/pipe_exec.c \
		execution/cmd_exec.c execution/get_path.c execution/heredoc.c built_in/built_dispacher.c \
		built_in/ft_echo.c built_in/ft_pwd.c built_in/ft_env.c built_in/ft_exit.c built_in/ft_cd.c \
		built_in/modify_env.c built_in/ft_export.c

SRCS+= testing/check_token.c testing/check_ast.c
OBJS= ${addprefix ${OBJS_DIR}, ${SRCS:.c=.o}}
OBJS_DIR= Objs/
LIBFT_DIR = Libft
LIBFT= ${LIBFT_DIR}/libft.a
CC= cc
SAN=-fsanitize=address,undefined
CFLAGS= -Wall -Werror -Wextra -g3 $(SAN)
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
