/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 20:23:12 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/16 12:10:33 by vmatsuda         ###   ########.fr       */
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

void	free_cmd(t_cmd *cmd)
{
	size_t	i;

	i = 0;
	if (!cmd)
		return ;
	while (cmd->argv[i])
		free(cmd->argv[i++]);
	free(cmd->argv);
	free(cmd);
}

void	free_array(char **array)
{
	size_t	i;

	if (!array)
		return ;
	i = 0;
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
