/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:00 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/04 15:18:22 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_env	*find_env(t_env *env, char *key)
{
	t_env	*last;

	last = env;
	while (last->next)
	{
		if (ft_strncmp(key, last->key, ft_strlen(key) == 0))
			return (last);
		last = last->next;
	}
	return (NULL);
}

void	add_env(t_shell_ctx *sh_ctx, char **entry)
{
	t_env	*last;
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		free_sh_ctx(sh_ctx, EXIT_FAILURE);
	new->key = ft_strdup(entry[0]);
	new->value = NULL;
	if (entry[1])
		new->value = ft_strdup(entry[1]);
	new->next = NULL;
	if (!sh_ctx->env)
	{
		sh_ctx->env = new;
		return ;
	}
	last = sh_ctx->env;
	while (last->next)
		last = last->next;
	last->next = new;
}

void	env_set(t_shell_ctx *ctx, char *env)
{
	t_env	*found_env;
	char	**env_entry;

	env_entry = ft_split(env, '=');
	found_env = find_env(ctx->env, env_entry[0]);
	if (!found_env)
	{
		add_env(ctx, env_entry);
		free_array(env_entry);
		print_envs(ctx);
	}
	else
	{
		free(found_env->value);
		found_env->value = NULL;
		if (env_entry[1])
			found_env->value = ft_strdup(env_entry[1]);
	}
}

int	builtin_export(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	if (!is_export_valid(cmd))
		return (1);
	i = 1;
	while (cmd->argv[i])
		env_set(ctx->shell, cmd->argv[i++]);
	ctx->shell->status = 0;
	return (0);
}
