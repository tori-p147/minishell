/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:35 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/03 18:01:53 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

/*
how shell start programm:
case 1: if command has / (abs path) -> execve()
case 2: if ./ ../ (relative path) ->
*/

t_env	*add_value(t_shell_ctx *sh_ctx, char **env_entry)
{
	t_env	*last;
	t_env	*new;

	last = NULL;
	new = malloc(sizeof(t_env));
	if (!new)
		free_sh_ctx(sh_ctx, EXIT_FAILURE);
	new->key = ft_strdup(env_entry[0]);
	if (env_entry[1] != NULL)
		new->value = ft_strdup(env_entry[1]);
	else
		new->value = NULL;
	new->next = NULL;
	free_array(env_entry);
	if (!sh_ctx->env)
		sh_ctx->env = new;
	else
	{
		last = sh_ctx->env;
		while (last->next)
			last = last->next;
		last->next = new;
	}
	return (sh_ctx->env);
}

int	execute(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	i = 0;
	(void)ctx;
	if (cmd->builtin == BI_EXPORT)
		return (0);
	// return (builtin_export(cmd, ctx));
	return (0);
}
