/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:35 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/16 20:19:26 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

/*
how shell start programm:
case 1: if command has / (abs path) -> execve()
case 2: if ./ ../ (relative path) ->
*/

int	check_exec_path(char *path, char *cmd_name)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		printf("%s: command not found\n", cmd_name);
		return (CMD_NOT_FOUND);
	}
	else if (S_ISDIR(st.st_mode))
	{
		printf("minishell: %s: Is a directory\n", cmd_name);
		return (IS_DIRECTORY);
	}
	else if (access(path, X_OK) == -1)
	{
		printf("minishell: %s: Permission denied\n", cmd_name);
		return (PERMISSION_DENIED);
	}
	return (0);
}

char	*resolve_path(char *arg0, t_tokenizer_ctx *ctx)
{
	char	*path_to_bin;
	char	*path_env;
	char	**path_dirs;
	size_t	i;

	if (ft_strchr(arg0, '/'))
		return (ft_strdup(arg0));
	path_env = get_value_by_key(ctx->shell->env, "PATH");
	if (!path_env)
		return (NULL);
	path_dirs = ft_split(path_env, ':');
	if (!path_dirs)
	{
		printf("%s: command not found\n", arg0);
		return (NULL);
	}
	i = 0;
	while (path_dirs[i])
	{
		//NEED FIX RESOLVE CMD BIN
		path_to_bin = ft_strjoin(path_dirs[i], arg0);
		printf("path to bin is %s\n", path_to_bin);
		if (!path_to_bin)
		{
			free(path_dirs);
			free_ctx(ctx, EXIT_FAILURE);
		}
		if (access(path_to_bin, X_OK) == 0)
		{
			printf("path is OK\n");
			free_array(path_dirs);
			return (path_to_bin);
		}
		free(path_to_bin);
		i++;
	}
	printf("path not found\n");
	free(path_dirs);
	return (NULL);
}

char	**convert_envp(t_env *env)
{
	char	**envp;
	size_t	counter;
	t_env	*curr;
	size_t	i;

	curr = env;
	while (env->next)
	{
		counter++;
		env = env->next;
	}
	envp = malloc(sizeof(char *) * (counter + 1));
	if (!envp)
		return (NULL);
	curr = env;
	i = 0;
	while (curr)
	{
		envp[i] = ft_double_strjoin(curr->key, "=", curr->value);
		if (!envp[i])
		{
			while (i--)
				free(envp[i]);
			free(envp);
			return (NULL);
		}
		i++;
		env = env->next;
	}
	envp[i] = NULL;
	return (envp);
}

int	exec_external(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	char		*path;
	char		**envp;
	pid_t		pid;
	int			exit_code;

	path = resolve_path(cmd->argv[0], ctx);
	if (!path)
	{
		printf("%s: command not found\n", cmd->argv[0]);
		return (CMD_NOT_FOUND);
	}
	printf("path %s\n", path);
	exit_code = check_exec_path(path, cmd->argv[0]);
	if (exit_code != 0)
		return (exit_code);
	// create child proccess
	pid = fork();
	if (!pid)
	{
		// apply_redirect();
		envp = convert_envp(ctx->shell->env);
		execve(path, cmd->argv, envp);
	}
	return (SUCCESS);
}

int	execute(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	if (cmd->builtin == BI_EXPORT)
		return (builtin_export(cmd, ctx));
	else if (cmd->builtin == BI_UNSET)
		return (builtin_unset(cmd, ctx));
	else if (cmd->builtin == BI_PWD)
		return (builtin_pwd(ctx));
	else if (cmd->builtin == BI_EXIT)
		return (builtin_exit(cmd, ctx));
	else if (cmd->builtin == BI_ECHO)
		return (builtin_echo(cmd));
	else if (cmd->builtin == BI_NONE)
		return (exec_external(cmd, ctx));
	return (SUCCESS);
}
