/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/04 19:01:17 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHELL_H
# define SHELL_H

# include <errno.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef enum e_parser_state
{
	NORMAL = 0,
	IN_SINGLE_QUOTE = 1,
	IN_DOUBLE_QUOTE = 2
}					t_parser_state;

typedef enum e_sh_status
{
	SUCCESS = 0,
	FAIL = 1,
	SYNTAX_ERROR = 2,
	PERMISSION_DENIED = 126,
	IS_DIRECTORY = 127,
	CMD_NOT_FOUND = 127
}					t_sh_status;

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
	BI_ECHO,
	// BI_CD,
	BI_PWD,
	BI_EXPORT,
	BI_UNSET,
	// BI_ENV,
	BI_EXIT
}					t_builtin;

typedef enum e_redir_type
{
	R_IN = 0,     // <
	R_OUT = 1,    // >
	R_APPEND = 2, // >>
	R_HEREDOC = 3 // <<
}					t_redir_type;

typedef struct s_redir
{
	t_redir_type	type;
	char			*file;
	struct s_redir	*next;
}					t_redir;

typedef struct s_cmds
{
	char			**argv;
	size_t			argc;
	t_redir			*redirs;
	t_builtin		builtin;
	struct s_cmds	*next;
}					t_cmds;

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
int					is_export_valid(t_cmds *cmd);

/*
tokenizer.c
*/
size_t				split_operator(t_tokenizer_ctx *ctx, size_t i);
size_t				is_operator(t_tokenizer_ctx *ctx, size_t i);
char				**tokenize(t_tokenizer_ctx *ctx);
size_t				expand_variable(t_tokenizer_ctx *ctx, size_t i);
void				print_tokens(char **tkns);
char				*strjoin_char(t_tokenizer_ctx *ctx);
void				copy_tokens(t_tokenizer_ctx *ctx, size_t i);
void				add_token(t_tokenizer_ctx *ctx);
char				**parse(t_tokenizer_ctx *ctx);

/*
cmd_parser.c
*/
t_cmds				*parse_cmd(t_tokenizer_ctx *ctx);

/*
cmd_parser_utils.c
*/
t_builtin			get_cmd_type(char *argv0);
void				set_cmd_type(t_cmds *cmd);
int					is_redir_token(char *token);
int					check_next_token(char *token);
t_redir_type		get_redir_type(char *token);

/*
expander.c
*/
char				*get_value_by_key(t_env *env, char *key);

/*
env_utils.c
*/
size_t				count_envs_size(t_env *env);
t_env				*find_env(t_env *env, char *key);
void				env_set(t_shell_ctx *ctx, char *env);
void				add_env(t_shell_ctx *sh_ctx, char **entry);
void				env_unset(t_shell_ctx *sh_ctx, char *key);

/*
executor.c
*/
char	**convert_envp(t_env *env);
int					apply_redirection(t_cmds *cmd);
int					external(t_cmds *cmd, t_tokenizer_ctx *ctx);
int					builtin(t_cmds *cmd, t_tokenizer_ctx *ctx, bool need_redir);
int					builtin_echo(t_cmds *cmd);
int					builtin_exit(t_cmds *cmd, t_tokenizer_ctx *ctx);
int					builtin_pwd(t_tokenizer_ctx *ctx);
int					builtin_unset(t_cmds *cmd, t_tokenizer_ctx *ctx);
int					builtin_pwd(t_tokenizer_ctx *ctx);
int					builtin_export(t_cmds *cmd, t_tokenizer_ctx *ctx);
int					execute(t_cmds *cmd, t_tokenizer_ctx *ctx);
int					run_simple_cmd(t_cmds *cmd, t_tokenizer_ctx *ctx);
char				*search_exists_path(char *arg0, t_tokenizer_ctx *ctx,
						char **path_dirs);
char				*resolve_path(char *arg0, t_tokenizer_ctx *ctx);

/*
pipeline.c
*/
int					apply_pipeline(t_cmds *cmd, t_tokenizer_ctx *ctx);

/*
free_utils.c
*/
void				free_array_n(char **array, size_t i);
void				free_input(t_tokenizer_ctx *ctx);
void				free_cmd(t_cmds *cmd);
void				free_sh_ctx(t_shell_ctx *sh_ctx, int status);
void				free_array(char **array);
void				free_ctx(t_tokenizer_ctx *ctx, int status);

/*
common_utils.c
*/
void				print_cmds(t_cmds *cmd);
char				*ft_double_strjoin(char *s1, char *s2, char *s3);
void				print_redirs(t_redir *redirs);
int					ft_strcmp(const char *s1, const char *s2);
void				print_argv(char **argv);

void				print_error(char *cmd_name, char *arg, int status);
void				print_envs(t_shell_ctx *sh_ctx);
void				init_shell_ctx(t_shell_ctx *sh_ctx, char **env);
void				read_input(t_tokenizer_ctx *ctx);

#endif