/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:59:21 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/04 19:10:31 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_builtin	get_builtin_type(char *argv0)
{
	if (!ft_strcmp(argv0, "export"))
		return (BI_EXPORT);
	else if (!ft_strcmp(argv0, "unset"))
		return (BI_UNSET);
	else if (!ft_strcmp(argv0, "pwd"))
		return (BI_PWD);
	else if (!ft_strcmp(argv0, "exit"))
		return (BI_EXIT);
	else if (!ft_strcmp(argv0, "echo"))
		return (BI_ECHO);
	return (BI_NONE);
}

t_cmd	*alloc_cmd(t_tokenizer_ctx *ctx, t_cmd *cmd)
{
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		free_ctx(ctx, EXIT_FAILURE);
	cmd->builtin = BI_NONE;
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
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
		return (cmd->redirs);
	}
	last = cmd->redirs;
	while (last->next)
		last = last->next;
	last->next = new_redir;
	return (cmd->redirs);
}

void	add_argv(char *token, t_tokenizer_ctx *ctx, t_cmd *cmd)
{
	char	*new_argv;
	char	**tmp;
	size_t	i;

	new_argv = ft_strdup(token);
	if (!new_argv)
	{
		free_cmd(cmd);
		free_ctx(ctx, EXIT_FAILURE);
	}
	tmp = malloc(sizeof(char *) * (cmd->argc + 2));
	if (!tmp)
	{
		free_cmd(cmd);
		free_ctx(ctx, EXIT_FAILURE);
	}
	i = -1;
	while (++i < cmd->argc)
		tmp[i] = cmd->argv[i];
	tmp[cmd->argc] = new_argv;
	tmp[cmd->argc + 1] = NULL;
	free(cmd->argv);
	cmd->argv = tmp;
	cmd->argc++;
}

t_cmd	*parse_cmd(t_tokenizer_ctx *ctx, t_cmd *cmd)
{
	size_t	i;

	cmd = alloc_cmd(ctx, cmd);
	i = 0;
	while (ctx->tokens[i])
	{
		if (is_redir_token(ctx->tokens[i]))
		{
			if (!ctx->tokens[i + 1] || !check_next_token(ctx->tokens[i + 1]))
			{
				free_cmd(cmd);
				ctx->shell->status = 2;
				return (NULL);
			}
			cmd->redirs = add_redir(ctx->tokens[i], ctx->tokens[i + 1], cmd);
			if (!cmd->redirs)
				free_ctx(ctx, EXIT_FAILURE);
			i += 2;
		}
		else
			add_argv(ctx->tokens[i++], ctx, cmd);
	}
	if (cmd->argv)
		cmd->builtin = get_builtin_type(cmd->argv[0]);
	return (cmd);
}
