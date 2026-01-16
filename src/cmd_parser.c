/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:59:21 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/16 16:15:31 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_builtin	get_builtin_type(char *token)
{
	if (!ft_strcmp(token, "export"))
		return (BI_EXPORT);
	else if (!ft_strcmp(token, "unset"))
		return (BI_UNSET);
	else if (!ft_strcmp(token, "pwd"))
		return (BI_PWD);
	else if (!ft_strcmp(token, "exit"))
		return (BI_EXIT);
	else if (!ft_strcmp(token, "echo"))
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
	ft_memset(cmd->argv, 0, sizeof(char *) * (argv_count + 1));
	return (cmd);
}

t_redir	*add_redir(char *token, char *next_token, t_cmd *cmd)
{
	t_redir	*new_redir;
	t_redir	*last;

	new_redir = malloc(sizeof(t_redir));
	if (!new_redir)
		return (NULL);
	new_redir->type = get_redir_type(token);
	new_redir->file = ft_strdup(next_token);
	new_redir->next = NULL;
	if (!cmd->redirs)
	{
		cmd->redirs = new_redir;
		printf("added new %d\n", new_redir->type);
		return (cmd->redirs);
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = new_redir;
	printf("added %d\n", new_redir->type);
	return (cmd->redirs);
}

char	*add_argv(char *token, t_tokenizer_ctx *ctx, t_cmd *cmd)
{
	char	*new_argv;

	new_argv = ft_strdup(token);
	if (!new_argv)
	{
		free_cmd(cmd);
		free_ctx(ctx, EXIT_FAILURE);
	}
	return (new_argv);
}

t_cmd	*parse_cmd(t_tokenizer_ctx *ctx, t_cmd *cmd)
{
	size_t	i;

	cmd = alloc_cmd(ctx, cmd);
	cmd->builtin = get_builtin_type(ctx->tokens[0]);
	i = -1;
	while (ctx->tokens[++i])
	{
		if (is_redir_token(ctx->tokens[i]))
		{
			if (!check_next_token(ctx->tokens[i + 1]))
			{
				free_cmd(cmd);
				ctx->shell->status = 2;
				return (NULL);
			}
			cmd->redirs = add_redir(ctx->tokens[i], ctx->tokens[i + 1], cmd);
			print_redirs(cmd->redirs);
			if (!cmd->redirs)
				free_ctx(ctx, EXIT_FAILURE);
			i++;
			continue ;
		}
		cmd->argv[i] = add_argv(ctx->tokens[i], ctx, cmd);
	}
	cmd->argv[i] = NULL;
	print_argv(cmd->argv);
	return (cmd);
}
