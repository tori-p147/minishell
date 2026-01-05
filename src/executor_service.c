/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:00 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/05 18:21:25 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_env	*find_env(t_env *env, char *key)
{
	t_env	*curr;
	t_env	*curr;

	curr = env;
	while (curr)
	curr = env;
	while (curr)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(key)) == 0)
			return (curr);
		curr = curr->next;
		if (ft_strncmp(key, curr->key, ft_strlen(key)) == 0)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

void	env_unset(t_shell_ctx *sh_ctx, char *key)
{
	t_env	*delete;
	t_env	*prev;
	t_env	*next;

	delete = NULL;
	prev = NULL;
	next = NULL;
	prev = sh_ctx->env;
	while (prev->next)
	{
		if (ft_strncmp(key, prev->next->key, ft_strlen(key)) == 0)
		{
			delete = prev->next;
			next = prev->next->next;
			free(delete->key);
			free(delete->value);
			prev->next = next;
			free(delete);
			return ;
		}
		prev = prev->next;
	}
}

void	env_unset(t_shell_ctx *sh_ctx, char *key)
{
	t_env	*delete;
	t_env	*prev;
	t_env	*next;

	delete = NULL;
	prev = NULL;
	next = NULL;
	prev = sh_ctx->env;
	while (prev->next)
	{
		if (ft_strncmp(key, prev->next->key, ft_strlen(key)) == 0)
		{
			delete = prev->next;
			next = prev->next->next;
			free(delete->key);
			free(delete->value);
			prev->next = next;
			free(delete);
			return ;
		}
		prev = prev->next;
	}
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
		print_envs(ctx);
		printf("new added\n");
	}
	else
	{
		free(found_env->value);
		found_env->value = NULL;
		if (env_entry[1])
			found_env->value = ft_strdup(env_entry[1]);
		print_envs(ctx);
		printf("updated\n");
		print_envs(ctx);
		printf("updated\n");
	}
	free_array(env_entry);
	free_array(env_entry);
}

int	builtin_export(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	if (!is_export_valid(cmd))
		return (1);
	i = 1;
	while (cmd->argv[i])
		env_set(ctx->shell, cmd->argv[i++]);
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	i = 1;
	while (cmd->argv[i])
		env_unset(ctx->shell, cmd->argv[i++]);
	return (0);
}

int	builtin_unset(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	i = 1;
	while (cmd->argv[i])
		env_unset(ctx->shell, cmd->argv[i++]);
	return (0);
}
