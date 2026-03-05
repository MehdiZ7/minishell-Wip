# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/01/27 11:34:03 by mzouhir           #+#    #+#              #
#    Updated: 2026/03/04 18:58:55 by mzouhir          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


NAME=minishell
SRCS= 	main.c main_utils.c \
		lexer/lexer.c lexer/lexer_utils.c lexer/lexer_copy.c\
		lexer_helper/ft_append_str_to_tab_str.c \
		lexer_helper/ft_grow_tab_str.c   lexer_helper/ft_printf_tab_str.c \
		lexer_helper/ft_split_like_shell_utils.c \
		lexer_helper/ft_complete_string_treatment.c  lexer_helper/ft_in_quotes.c \
		lexer_helper/ft_remove_quotes.c lexer_helper/ft_strlen_env.c\
		lexer_helper/ft_free_tab_str.c  lexer_helper/ft_next_env_not_in_simple_quote.c \
		lexer_helper/ft_replace_env.c lexer_helper/ft_grow_last_str_of_tab_str.c  \
		lexer_helper/ft_not_special_str.c  lexer_helper/ft_split_like_shell.c\
		env_parsing/env.c env_parsing/env_utils.c \
		expansion/expansion.c  expansion/expansion_utils.c\
		expansion/wildcards_utils.c expansion/wildcards.c \
		expansion/remove_wildcard_quote.c \
		ast_parsing/parser.c  ast_parsing/parser_utils.c ast_parsing/print_parser.c ast_parsing/parser_infix_topostfix.c \
		ast_parsing/parser_create_ast_command.c ast_parsing/parser_infix_helper.c\
		ast_parsing/parser_infix_parenclose.c \
		ast_parsing/parser_create_ast_loop.c \
		execution/master_execution.c execution/pipe_exec.c \
		execution/cmd_exec.c execution/get_path.c execution/heredoc.c execution/handle_redir.c \
		execution/get_path_utils.c execution/get_path_utils2.c\
		built_in/built_dispacher.c built_in/ft_echo.c built_in/ft_pwd.c built_in/ft_env.c built_in/ft_exit.c built_in/ft_cd.c \
		built_in/modify_env.c built_in/ft_export.c built_in/ft_unset.c \
		signals/signals.c signals/terminal.c \
		syntax_validation/ft_correct_input.c \
		syntax_validation/syntax_validation_utils.c

OBJS= ${addprefix ${OBJS_DIR}, ${SRCS:.c=.o}}
OBJS_DIR= Objs/
LIBFT_DIR = Libft
LIBFT= ${LIBFT_DIR}/libft.a
CC= cc
#SAN=-fsanitize=address,undefined
#CBUG= -O0 -ggdb
#COPT= -g3
CFLAGS= -Wall -Wextra -Werror
LINKERS= -lreadline -lcurses
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

bonus: all

.PHONY: all clean fclean re bonus
