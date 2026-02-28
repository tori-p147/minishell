/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipeline_service.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 10:56:34 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/28 16:03:47 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	external_no_fork(t_cmds *cmd, t_tokenizer_ctx *ctx)
{
	char	*path;
	char	**envp;

	envp = convert_envp(ctx->shell->env);
	if (!envp)
		return (FAIL);
	path = resolve_path(cmd->argv[0], ctx);
	if (!path)
	{
		printf("%s: command not found\n", cmd->argv[0]);
		return (CMD_NOT_FOUND);
	}
	execve(path, cmd->argv, envp);
	printf("minishell: %s: %s\n", cmd->argv[0], strerror(errno));
	free_array(envp);
	if (errno == ENOENT)
		return (127);
	else if (errno == EACCES)
		return (126);
	return (FAIL);
}

pid_t	do_fork_pipe(int *prev_fd, int pipe_fd[2], t_cmds *curr,
		t_tokenizer_ctx *ctx)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		perror("minishell: fork");
		return (FAIL);
	}
	// child proc
	else if (pid == 0)
	{
		if (*prev_fd != -1)
		{
			dup2(*prev_fd, STDIN_FILENO);
			close(*prev_fd);
		}
		if (curr->next)
		{
			dup2(pipe_fd[1], STDOUT_FILENO);
			close(pipe_fd[0]);
			close(pipe_fd[1]);
		}
		apply_redirection(curr);
		if (curr->builtin == BI_NONE)
			exit(external_no_fork(curr, ctx));
		else
			exit(builtin(curr, ctx, 0));
	}
	// parent
	else
	{
		if (*prev_fd != -1)
			close(*prev_fd);
		if (curr->next)
		{
			close(pipe_fd[1]);
			*prev_fd = pipe_fd[0];
		}
	}
	return (pid);
}

int	wait_pipeline(pid_t last_pid)
{
	int		status;
	int		exit_code;
	pid_t	pid;

	exit_code = 0;
	while ((pid = wait(&status)) > 0)
	{
		if (pid == last_pid)
		{
			if (WIFEXITED(status))
				exit_code = WEXITSTATUS(status);
			else if (WIFSIGNALED(status))
				exit_code = 128 + WTERMSIG(status);
		}
	}
	return (exit_code);
}

int	apply_pipeline(t_cmds *cmd, t_tokenizer_ctx *ctx)
{
	int		pipe_fd[2];
	int		prev_fd;
	t_cmds	*curr;
	int		last_pid;

	prev_fd = -1;
	curr = cmd;
	while (curr)
	{
		if (curr->next)
			pipe(pipe_fd);
		last_pid = do_fork_pipe(&prev_fd, pipe_fd, curr, ctx);
		curr = curr->next;
	}
	return (wait_pipeline(last_pid));
}
