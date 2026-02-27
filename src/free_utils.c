/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 20:23:12 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/29 17:18:38 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_input(t_tokenizer_ctx *ctx)
{
	free(ctx->line);
	free_array(ctx->tokens);
	free(ctx->token);
	ctx->tokens = NULL;
	ctx->token = NULL;
	ctx->line = NULL;
}

void	free_cmd(t_cmds *cmd)
{
	size_t	i;
	t_redir	*tmp_r;
	t_cmds	*tmp_cmd;

	tmp_cmd = cmd;
	if (!cmd)
		return ;
	while (cmd)
	{
		tmp_cmd = cmd->next;
		if (cmd->argv)
		{
			i = 0;
			while (cmd->argv[i])
				free(cmd->argv[i++]);
			free(cmd->argv);
		}
		while (cmd->redirs)
		{
			tmp_r = cmd->redirs->next;
			free(cmd->redirs->file);
			free(cmd->redirs);
			cmd->redirs = tmp_r;
		}
		free(cmd);
		cmd = tmp_cmd;
	}
}

void	free_array_n(char **array, size_t i)
{
	if (!array)
		return ;
	while (i--)
		free(array[i]);
	free(array);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
		free(array[i++]);
	free(array);
}

void	free_ctx(t_tokenizer_ctx *ctx, int status)
{
	free(ctx->line);
	free(ctx->token);
	free_array(ctx->tokens);
	free_sh_ctx(ctx->shell, status);
	exit(status);
}

void	free_sh_ctx(t_shell_ctx *sh_ctx, int status)
{
	t_env	*tmp;

	while (sh_ctx->env)
	{
		tmp = sh_ctx->env->next;
		free(sh_ctx->env->key);
		free(sh_ctx->env->value);
		free(sh_ctx->env);
		sh_ctx->env = tmp;
	}
	exit(status);
}
