/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/29 13:40:02 by vmatsuda         ###   ########.fr       */
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

typedef enum parser_state
{
	NORMAL = 0,
	IN_SINGLE_QUOTE = 1,
	IN_DOUBLE_QUOTE = 2
}					t_parser_state;

typedef enum exit_status
{
	EXIT_SYNTAX_ERROR = 2
}					t_exit_status;

typedef struct tokenizer_ctx
{
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
parser.c
*/
void	print_tokens(char **tkns);
char	*strjoin_char(t_tokenizer_ctx *ctx);
void				error_exit(t_tokenizer_ctx *ctx, t_exit_status status);
void				copy_tokens(t_tokenizer_ctx *ctx, size_t i);
void				add_token(t_tokenizer_ctx *ctx);
char				**parse(t_tokenizer_ctx *ctx);

/*
free_utils.c
*/
void	free_tokens(char **tokens);
void				free_ctx(t_tokenizer_ctx *ctx);
void				free_and_exit(t_tokenizer_ctx *ctx, int status);

void				read_input(t_tokenizer_ctx *ctx);

#endif