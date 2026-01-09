/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:59:21 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/09 14:09:45 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_builtin	get_builtin_type(char *token)
{
	size_t	token_len;

	token_len = ft_strlen(token);
	if (!ft_strncmp(token, "export", token_len))
		return (BI_EXPORT);
	else if (!ft_strncmp(token, "unset", token_len))
		return (BI_UNSET);
	else if (!ft_strncmp(token, "pwd", token_len))
		return (BI_PWD);
	else if (!ft_strncmp(token, "exit", token_len))
		return (BI_EXIT);
	else if (!ft_strncmp(token, "echo", token_len))
		return (BI_ECHO);
	return (BI_NONE);
}

t_cmd	*alloc_cmd(t_tokenizer_ctx *ctx, t_cmd *cmd)
{
	size_t	argv_count;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		free_ctx(ctx, EXIT_FAILURE);
	argv_count = 0;
	while (ctx->tokens[argv_count])
		argv_count++;
	cmd->argv = malloc(sizeof(char *) * (argv_count + 1));
	if (!cmd->argv)
	{
		free_cmd(cmd);
		free_ctx(ctx, EXIT_FAILURE);
	}
	return (cmd);
}

t_cmd	*parse_cmd_list(t_tokenizer_ctx *ctx, t_cmd *cmd)
{
	size_t	i;

	cmd = alloc_cmd(ctx, cmd);
	cmd->builtin = get_builtin_type(ctx->tokens[0]);
	i = 0;
	while (ctx->tokens[i])
	{
		cmd->argv[i] = ft_strdup(ctx->tokens[i]);
		if (!cmd->argv[i])
		{
			free_cmd(cmd);
			free_ctx(ctx, EXIT_FAILURE);
		}
		i++;
	}
	cmd->argv[i] = NULL;
	return (cmd);
}
