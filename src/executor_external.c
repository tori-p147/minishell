/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_external.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/19 17:09:47 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/29 13:27:07 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	**convert_envp(t_env *env)
{
	char	**envp;
	size_t	counter;
	size_t	i;

	counter = count_envs_size(env);
	envp = malloc(sizeof(char *) * (counter + 1));
	if (!envp)
		return (NULL);
	i = -1;
	while (env && ++i < counter)
	{
		if (!env->value)
			envp[i] = ft_strjoin(env->key, ft_strdup("="));
		else
			envp[i] = ft_double_strjoin(env->key, ft_strdup("="), env->value);
		if (!envp[i])
		{
			free_array_n(envp, i);
			printf("FAILED\n");
			return (NULL);
		}
		env = env->next;
	}
	envp[counter] = NULL;
	return (envp);
}

void	child_proc(t_cmd *cmd, t_tokenizer_ctx *ctx, char *path)
{
	char	**envp;

	envp = convert_envp(ctx->shell->env);
	if (!envp)
	{
		free(path);
		free_cmd(cmd);
		free_ctx(ctx, EXIT_FAILURE);
	}
	apply_redirection(cmd);
	execve(path, cmd->argv, envp);
	perror("minishell");
	free(path);
	exit(1);
}

int	parent_proc(pid_t pid)
{
	int	st;
	int	exit_st;

	waitpid(pid, &st, 0);
	if (WIFEXITED(st))
		exit_st = WEXITSTATUS(st);
	else if (WIFSIGNALED(st))
		exit_st = 128 + WTERMSIG(st);
	return (exit_st);
}

/*
how	fork(void) working:
1. error
2. !pid == 0 -> child process
3. pid > 0 -> parent process
*/
int	do_fork(t_cmd *cmd, t_tokenizer_ctx *ctx, char *path)
{
	pid_t	pid;
	int		exit_code;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit_code = FAIL;
	}
	else if (pid == 0)
		child_proc(cmd, ctx, path);
	else
		exit_code = parent_proc(pid);
	return (exit_code);
}

int	external(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	char	*path;
	int		exit_code;

	printf("argv %s\n", cmd->argv[0]);
	path = resolve_path(cmd->argv[0], ctx);
	if (!path)
	{
		printf("%s: command not found\n", cmd->argv[0]);
		return (CMD_NOT_FOUND);
	}
	exit_code = validate_path(path, cmd->argv[0]);
	if (exit_code != 0)
	{
		free(path);
		return (exit_code);
	}
	exit_code = do_fork(cmd, ctx, path);
	free(path);
	return (exit_code);
}
