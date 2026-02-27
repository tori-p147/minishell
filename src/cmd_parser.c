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

t_cmds	*alloc_cmd(t_tokenizer_ctx *ctx)
{
	t_cmds	*cmd;

	cmd = malloc(sizeof(t_cmds));
	if (!cmd)
		free_ctx(ctx, EXIT_FAILURE);
	cmd->builtin = BI_NONE;
	cmd->argv = NULL;
	cmd->argc = 0;
	cmd->redirs = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_redir	*add_redir(char *token, char *next_token, t_cmds *cmd)
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

void	add_argv(char *token, t_tokenizer_ctx *ctx, t_cmds *cmd)
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

int	validate_redir_pos(t_tokenizer_ctx *ctx, t_cmds *head, t_cmds *curr,
		size_t i)
{
	if (!ctx->tokens[i + 1] || !check_next_token(ctx->tokens[i + 1]))
	{
		free_cmd(head);
		ctx->shell->status = SYNTAX_ERROR;
		return (0);
	}
	curr->redirs = add_redir(ctx->tokens[i], ctx->tokens[i + 1], curr);
	if (!curr->redirs)
	{
		free_cmd(head);
		free_ctx(ctx, EXIT_FAILURE);
	}
	return (1);
}

t_cmds	*parse_cmd(t_tokenizer_ctx *ctx)
{
	size_t	i;
	t_cmds	*head;
	t_cmds	*curr;

	head = alloc_cmd(ctx);
	i = 0;
	curr = head;
	while (ctx->tokens[i])
	{
		if (is_redir_token(ctx->tokens[i]))
		{
			if (!validate_redir_pos(ctx, head, curr, i))
				return (NULL);
			i += 2;
		}
		else if (!ft_strcmp(ctx->tokens[i], "|"))
		{
			curr->next = alloc_cmd(ctx);
			curr = curr->next;
			i++;
		}
		else
			add_argv(ctx->tokens[i++], ctx, curr);
	}
	return (head);
}
