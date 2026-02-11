/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/27 13:53:07 by mzouhir           #+#    #+#             */
/*   Updated: 2026/02/11 16:05:58 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
# include <fcntl.h>

typedef enum e_token_type
{
	UNRECOGNIZED,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
	PIPE,
	REDIR_IN,
	REDIR_OUT,
	HEREDOC,
	APPEND,
	AND,
	OR,
	PAREN_OPEN,
	PAREN_CLOSE,
	WILDCARD,
	ENV,
	CMD_OR_ARG
}							t_token_type;

typedef struct s_token
{
	char					*value;
	t_token_type			type;
	struct s_token			*next;

}							t_token;

typedef enum e_node_type
{
	NODE_NULL,
	NODE_PIPE,
	NODE_AND,
	NODE_OR,
	NODE_CMD
}							t_node_type;

typedef enum e_redir_type
{
	REDIR_IN_FILE,
	REDIR_OUT_FILE,
	REDIR_APPEND,
	REDIR_HEREDOC
}							t_redir_type;

typedef struct s_redir_node
{
	t_redir_type			type;
	char					*filename;
	struct s_redir_node		*next;
}							t_redir_node;

typedef struct s_env	t_env;

typedef struct s_command
{
	int						argc;
	char					**argv;
	t_env					*env;
	t_redir_node			*redir;
}							t_command;

typedef struct s_node	t_node;

typedef struct s_and_command
{
	t_node				*first;
	t_node				*second;
}							t_and_command;

typedef struct s_or_command
{
	t_node				*first;
	t_node				*second;
}							t_or_command;

typedef struct s_pipe_command
{
	t_node				*first;
	t_node				*second;
}							t_pipe_command;

typedef struct s_node
{
	t_node_type				node_type;
	union
	{
		t_command			command;
		t_and_command		and_command;
		t_or_command		or_command;
		t_pipe_command		pipe_command;
	};
}							t_node;

typedef struct s_env
{
	char					*key;
	char					*value;
	struct s_env			*next;
}							t_env;

typedef struct s_minishell
{
	t_env					*env;
	t_token					*tokens;
	t_node					*ast;
	int						exit_status;
}							t_minishell;

// main utils
t_minishell				*init_minishell(char **envp);
int						shell_loop(t_minishell *data);

// lexer utils
void					free_token(t_token *list);
int						ft_isseparator(const char c);
int						ft_strlen_without_quotes(char *input, int i);
char					ft_first_char_not_ingroup(char *str, size_t start,
							char *grp);

// lexer
t_token					*lexer(char *input);
t_token					*create_token(char *value, t_token_type type);
void					token_add_back(t_token *new, t_token **list);
int						handle_quotes(char *input, t_token **list);
int						handle_separator(char *input, t_token **list);
int						handle_cmd_or_arg(char *input, t_token **list);

// env parsing
t_env					*init_env(char **envp);

// env utils
void					free_env(t_env *env);
void					env_add_back(t_env *new, t_env **list);

// expansion
int						get_expansion(t_minishell *data);
int						replace_var(t_token *token, char *key, int index,
							t_minishell *data);

// Parsing the quotes
int						remove_quote(t_minishell *data);

// Parsing for the abstract syntax tree
t_node					*create_ast_node(t_node_type type);

// Parsing AST utils
void					free_ast_node(t_node *ast);
void					free_redir_node(t_redir_node *node);
void					free_args(char **argv);

//Execution
int						executor(t_node *node, t_minishell *data);

//Execution utils
int						exec_pipe(t_node *node, t_minishell *data);
int						exec_cmd(t_node *node, t_minishell *data);
char					*find_path(char *cmd, t_env *env);
char					**list_to_tab(t_env *env);

//Heredoc processor
int						process_heredoc(t_node *node);

//built_in dispacher
int						check_for_built_in(t_node *node);
int						built_in_exec(t_node *node, t_minishell *data);
int						ft_echo(t_node *node, t_minishell *data);
int						ft_pwd(t_minishell *data);
int						ft_env(t_minishell *data);
int						ft_exit(t_node *node, t_minishell *data);
int						create_new(char *key, char *value, t_minishell *data);
int						update_env(char *key, char *value, t_minishell *data);
int						ft_cd(t_node *node, t_minishell *data);

// Only for testing ! Don't forger to clear this
void					print_list(t_token *list);
void					print_env(t_env *list);
void					test_exec(t_minishell *data);
void					test_pipe_exec(t_minishell *data);
void					check_heredoc(t_minishell *data);
void					test_builtins(t_minishell *data);




#endif
