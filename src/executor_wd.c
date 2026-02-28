/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_wd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/28 15:19:26 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/28 15:41:17 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	try_chdir(t_cmds *cmd, char *target)
{
	if (chdir(target) != 0)
	{
		printf("minishell: %s: %s: %s\n", cmd->argv[0], cmd->argv[0],
			strerror(errno));
		return (FAIL);
	}
	return (SUCCESS);
}

int	builtin_cd(t_cmds *cmd, t_tokenizer_ctx *ctx)
{
	char	*old_wd;
	char	*target;
	char	*new_wd;

	old_wd = getcwd(NULL, 0);
	if (!old_wd)
		return (FAIL);
	if (!cmd->argv[1] || !ft_strcmp(cmd->argv[1], "~"))
		target = find_env(ctx->shell->env, "HOME")->value;
	else if (!ft_strcmp(cmd->argv[1], "-"))
		target = find_env(ctx->shell->env, "OLDPWD")->value;
	else
		target = cmd->argv[1];
	if (try_chdir(cmd, target))
	{
		free(old_wd);
		return (FAIL);
	}
	new_wd = getcwd(NULL, 0);
	add_or_update_env(ctx->shell, ft_strjoin("OLDPWD=", old_wd));
	add_or_update_env(ctx->shell, ft_strjoin("PWD=", new_wd));
	free(old_wd);
	free(new_wd);
	return (SUCCESS);
}

int	builtin_pwd(t_tokenizer_ctx *ctx)
{
	char	*cwd_path;
	char	**env_entry;

	env_entry = malloc(sizeof(char *) * 3);
	if (!env_entry)
		free_ctx(ctx, EXIT_FAILURE);
	cwd_path = getcwd(NULL, 0);
	if (!cwd_path)
		return (FAIL);
	env_entry[0] = ft_strdup("PWD");
	env_entry[1] = ft_strdup(cwd_path);
	env_entry[2] = NULL;
	set_env(ctx->shell, env_entry);
	printf("%s\n", cwd_path);
	free_array(env_entry);
	free(cwd_path);
	return (SUCCESS);
}
