/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/13 20:18:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/24 22:36:43 by vmatsuda         ###   ########.fr       */
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
}		t_parser_state;

typedef enum exit_status
{
	EXIT_SYNTAX_ERROR = 2
}		t_exit_status;

/*
signal_handler.c
*/
void	setup_signals_shell(void);
void	sigint_handler(int sig);

/*
parser.c
*/
void	print_error(t_exit_status status);
char	**copy_tokens(char **tokens, size_t i);
char	**add_token(char **tokens, char *current);
char	**parse(char *in_line);

/*
free_utils.c
*/
void free_and_exit(char *in_line, char *current, int status);

void	read_input(void);

#endif