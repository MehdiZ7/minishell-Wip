/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:53:07 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/05 17:52:16 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <signal.h>

typedef enum e_token_type
{
	WORD,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	AND,
	OR,
	PAREN_OPEN,
	PAREN_CLOSE,
	WILDCARD
}t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;

}t_token;

typedef enum e_node_type
{
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD
}t_node_type;

typedef struct s_node
{
	t_node_type		type;
	struct s_node	*left;
	struct s_node	*right;
	char			**args;
}t_node;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}t_env;

typedef struct s_minishell
{
	t_env	*env;
	t_token	*tokens;
	t_node	*ast;
	int		exit_status;
}t_minishell;

//main utils
t_minishell	*init_minishell(char **envp);
int			shell_loop(t_minishell *data);

//lexer utils
void		free_token(t_token *list);
int			ft_isoperator(const char c);
int			skip_quotes(char *input, int i);

//lexer
t_token		*lexer(char	*input);
t_token		*create_token(char *value, t_token_type type);
void		token_add_back(t_token *new, t_token **list);
int			handle_word(char *input, t_token **list);
int			handle_separator(char *input, t_token **list);

//env parsing
t_env		*init_env(char **envp);

//env utils
void		free_env(t_env *env);

//expansion
int			get_expansion(t_minishell *data);
int			replace_var(t_token *token, char *key,
				int index, t_minishell *data);

//Parsing the quotes
int			remove_quote(t_minishell *data);

//Only for testing ! Don't forger to clear this
void		print_list(t_token *list);
void		print_env(t_env	*list);

#endif
