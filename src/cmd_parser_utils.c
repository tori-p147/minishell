/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:23:13 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/28 16:13:01 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_builtin	get_cmd_type(char *argv0)
{
	if (!ft_strcmp(argv0, "export"))
		return (BI_EXPORT);
	else if (!ft_strcmp(argv0, "unset"))
		return (BI_UNSET);
	else if (!ft_strcmp(argv0, "pwd"))
		return (BI_PWD);
	else if (!ft_strcmp(argv0, "exit"))
		return (BI_EXIT);
	else if (!ft_strcmp(argv0, "cd"))
		return (BI_CD);
	else if (!ft_strcmp(argv0, "env"))
		return (BI_ENV);
	else if (!ft_strcmp(argv0, "echo"))
		return (BI_ECHO);
	return (BI_NONE);
}

void	set_cmd_type(t_cmds *cmds)
{
	t_cmds	*curr;

	curr = cmds;
	while (curr)
	{
		if (curr->argv)
			curr->builtin = get_cmd_type(curr->argv[0]);
		curr = curr->next;
	}
}

int	is_redir_token(char *token)
{
	if (!ft_strcmp(token, "<") || !ft_strcmp(token, ">") || !ft_strcmp(token,
			"<<") || !ft_strcmp(token, ">>"))
		return (1);
	return (0);
}

int	check_next_token(char *next_token)
{
	char	*msg;

	msg = "syntax error near unexpected token";
	if (!next_token)
	{
		printf("minishell: %s 'newline'\n", msg);
		return (0);
	}
	else if (is_redir_token(next_token))
	{
		printf("minishell: %s %s\n", msg, next_token);
		return (0);
	}
	return (1);
}

t_redir_type	get_redir_type(char *token)
{
	if (!ft_strcmp(token, "<"))
		return (R_IN);
	else if (!ft_strcmp(token, ">"))
		return (R_OUT);
	else if (!ft_strcmp(token, ">>"))
		return (R_APPEND);
	if (!ft_strcmp(token, "<<"))
		return (R_HEREDOC);
	printf("unknown type\n");
	return (R_HEREDOC);
}
