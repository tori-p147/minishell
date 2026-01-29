/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:23:13 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/29 18:46:05 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	is_redir_token(char *token)
{
	printf("is redir token = %s\n", token);
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
