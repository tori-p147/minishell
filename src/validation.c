/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:54:44 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/22 20:40:13 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

size_t	is_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	is_export_valid(t_cmds *cmd)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 1;
	while (cmd->argv[i])
	{
		j = -1;
		while (++j < ft_strlen(cmd->argv[i]))
		{
			c = cmd->argv[i][j];
			printf("curr: %c\n", c);
			if (c == '=')
				continue ;
			else if ((j == 0 && (!ft_isalpha(c) || c == '_'))
				|| !is_var_char(c))
			{
				printf("export: not an identifier: %s\n", cmd->argv[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}

//validate_tokes.c追加
static int	is_pipe_token(char *t)
{
	return (t && !ft_strcmp(t, "|"));
}

static int	is_or_token(char *t)
{
	return (t && !ft_strcmp(t, "||"));
}

static int	syntax_error_token(char *token)
{
	char	*msg;

	msg = "syntax error near unexpected token";
	if (!token)
		printf("minishell: %s 'newline'\n", msg);
	else
		printf("minishell: %s '%s'\n", msg, token);
	return (0);
}

int	validate_tokens(char **t)
{
	size_t	i;

	if (!t || !t[0])
		return (1);
	if (is_pipe_token(t[0]))
		return (syntax_error_token("|"));
	i = 0;
	while (t[i])
	{
		if (is_or_token(t[i]))
			return (syntax_error_token("||"));
		if (is_redir_token(t[i]))
		{
			if (!t[i + 1])
				return (syntax_error_token(NULL));
			if (is_redir_token(t[i + 1]) || is_pipe_token(t[i + 1]) || is_or_token(t[i + 1]))
				return (syntax_error_token(t[i + 1]));
		}
		if (is_pipe_token(t[i]))
		{
			if (!t[i + 1])
				return (syntax_error_token(NULL));
			if (is_pipe_token(t[i + 1]) || is_redir_token(t[i + 1]) || is_or_token(t[i + 1]))
				return (syntax_error_token(t[i + 1]));
			if (i > 0 && is_redir_token(t[i - 1]))
				return (syntax_error_token("|"));
		}
		i++;
	}
	return (1);
}
