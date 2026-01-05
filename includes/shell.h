/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/05 18:20:18 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>

typedef enum e_parser_state
{
	NORMAL = 0,
	IN_SINGLE_QUOTE = 1,
	IN_DOUBLE_QUOTE = 2
}					t_parser_state;

typedef enum e_exit_status
{
	EXIT_SYNTAX_ERROR = 2
}					t_exit_status;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_shell_ctx
{
	t_env			*env;
	int				status;
}					t_shell_ctx;

typedef enum e_builtin
{
	BI_NONE,
	// BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	BI_UNSET,
	// BI_ENV,
	// BI_EXIT
}					t_builtin;

// typedef enum e_redir_type

// typedef struct s_redir

typedef struct s_cmd
{
	char			**argv;
	// t_redir *redirs; release > < >> <<
	t_builtin		builtin;
	// struct s_cmd *next; releaze pipeline
}					t_cmd;

typedef struct tokenizer_ctx
{
	t_shell_ctx		*shell;
	t_parser_state	state;
	char			**tokens;
	char			*token;
	char			*line;
	char			c;
	size_t			line_len;
}					t_tokenizer_ctx;

/*
signal_handler.c
*/
void				setup_signals_shell(void);
void				sigint_handler(int sig);

/*
validation.c
*/
size_t				is_var_char(char c);
int					is_export_valid(t_cmd *cmd);

/*
tokenizer.c
*/
char				**tokenize(t_tokenizer_ctx *ctx);
size_t				expand_variable(t_tokenizer_ctx *ctx, size_t i);
void				print_tokens(char **tkns);
char				*strjoin_char(t_tokenizer_ctx *ctx);
void				error_exit(t_tokenizer_ctx *ctx, t_exit_status status);
void				copy_tokens(t_tokenizer_ctx *ctx, size_t i);
void				add_token(t_tokenizer_ctx *ctx);
char				**parse(t_tokenizer_ctx *ctx);

/*
parser.c
*/
t_cmd				*parse_cmd_list(t_tokenizer_ctx *ctx, t_cmd *cmd);

/*
expander.c
*/
char				*get_by_key(t_tokenizer_ctx *ctx, char *key);

/*
executor.c
*/
int					builtin_unset(t_cmd *cmd, t_tokenizer_ctx *ctx);
int					builtin_unset(t_cmd *cmd, t_tokenizer_ctx *ctx);
void				add_env(t_shell_ctx *sh_ctx, char **entry);
int					builtin_pwd(t_tokenizer_ctx *ctx);
int					builtin_export(t_cmd *cmd, t_tokenizer_ctx *ctx);
int					execute(t_cmd *cmd, t_tokenizer_ctx *ctx);

/*
free_utils.c
*/
void				free_cmd(t_cmd *cmd);
void				free_sh_ctx(t_shell_ctx *sh_ctx, int status);
void				free_array(char **array);
void				free_ctx(t_tokenizer_ctx *ctx, int status);

void				print_envs(t_shell_ctx *sh_ctx);
void				set_env(t_shell_ctx *sh_ctx, char **env);
void				read_input(t_tokenizer_ctx *ctx);

#endif