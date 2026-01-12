/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/02 22:32:00 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/12 14:32:05 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

t_env	*find_env(t_env *env, char *key)
{
	t_env	*curr;

	curr = env;
	while (curr)
	{
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

void	set_env(t_shell_ctx *sh_ctx, char **entry)
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

void	add_or_update_env(t_shell_ctx *ctx, char *env)
{
	t_env	*found_env;
	char	**env_entry;

	env_entry = ft_split(env, '=');
	found_env = find_env(ctx->env, env_entry[0]);
	if (!found_env)
	{
		set_env(ctx, env_entry);
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
	}
	free_array(env_entry);
}

int	builtin_export(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	size_t	i;

	if (!is_export_valid(cmd))
		return (1);
	i = 1;
	while (cmd->argv[i])
		add_or_update_env(ctx->shell, cmd->argv[i++]);
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

int	builtin_pwd(t_tokenizer_ctx *ctx)
{
	char	*cur_dir_path;
	char	**env_entry;

	env_entry = malloc(sizeof(char *) * 3);
	if (!env_entry)
		free_ctx(ctx, EXIT_FAILURE);
	cur_dir_path = getcwd(NULL, 0);
	if (!cur_dir_path)
		return (1);
	env_entry[0] = ft_strdup("PWD");
	env_entry[1] = ft_strdup(cur_dir_path);
	env_entry[2] = NULL;
	set_env(ctx->shell, env_entry);
	printf("%s\n", cur_dir_path);
	free_array(env_entry);
	free(cur_dir_path);
	return (0);
}

int	cd_home(t_tokenizer_ctx *ctx)
{
	
}

int cd_oldpwd(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	
}

int cd_res_abs_path(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	
}

int	cd_res_abs_path(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	char	*oldpwd;
	char	*oldpwdenv;
	char	*newpwd;
	char	*newpwdenv;

	oldpwd = getcwd(NULL, 0);
	if (chdir(cmd->argv[1]) != 0)
	{
		print_error(cmd->argv[0], cmd->argv[1], NO_SUCH_FILE_OR_DIR);
		free(oldpwd);
		return (1);
	}
	printf("oldpwd %s\n", oldpwd);
	if (oldpwd)
	{
		oldpwdenv = ft_strjoin("OLDPWD=", oldpwd);
		if (!cmd->argv[1])
			add_or_update_env(ctx->shell, oldpwdenv);
		add_or_update_env(ctx->shell, oldpwdenv);
	}
	newpwd = getcwd(NULL, 0);
	printf("newpwd %s\n", newpwd);
	if (newpwd)
	{
		newpwdenv = ft_strjoin("PWD=", newpwd);
		add_or_update_env(ctx->shell, newpwdenv);
	}
	free(oldpwd);
	free(newpwd);
	return (0);
}

int	builtin_cd(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	if (!cmd->argv[1] 
		|| (ft_strlen(cmd->argv[1]) == 1 && cmd->argv[1][0] == '~') 
		|| (ft_strlen(cmd->argv[1]) == 2 && !ft_strncmp(cmd->argv[1], '~/', 2)))
	{
		return(cd_home(ctx));
	}
	else if (ft_strlen(cmd->argv[1]) == 1 && cmd->argv[1][0] == '-')
		return(cd_oldpwd());
	else if (ft_strlen(cmd->argv[1]) > 1 && (cmd->argv[1][0] == '/'
		|| ft_strncmp(cmd->argv[1], '..', 2)))
		return(cd_res_abs_path(cmd, ctx));
	return (0);
}

int	builtin_env(t_tokenizer_ctx *ctx)
{
	size_t	i;
	t_env	*curr;

	i = -1;
	curr = ctx->shell->env;
	while (curr)
	{
		printf("%s=%s\n", curr->key, curr->value);
		curr = curr->next;
	}
	return (0);
}
