/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:35 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/29 18:38:12 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	apply_redirection(t_cmd *cmd)
{
	int		fd;
	t_redir	*curr;

	print_redirs(cmd->redirs);
	curr = cmd->redirs;
	while (curr)
	{
		if (curr->type == R_IN || curr->type == R_HEREDOC)
		{
			fd = open(curr->file, O_RDONLY);
			dup2(fd, STDIN_FILENO);
		}
		else if (curr->type == R_OUT)
		{
			fd = open(curr->file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		else if (curr->type == R_APPEND)
		{
			fd = open(curr->file, O_WRONLY | O_CREAT | O_APPEND, 0644);
			dup2(fd, STDOUT_FILENO);
		}
		close(fd);
		curr = curr->next;
	}
}

/*
Builtin commands are executed without fork() because they
must modify the shell state
Redirect change shell`s fd, before that need save fd for restore
*/
int	builtin(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	int	fd_in;
	int	fd_out;
	int	state;

	fd_in = dup(STDIN_FILENO);
	fd_out = dup(STDOUT_FILENO);
	state = 0;
	apply_redirection(cmd);
	if (cmd->builtin == BI_EXPORT)
		state = builtin_export(cmd, ctx);
	else if (cmd->builtin == BI_UNSET)
		state = (builtin_unset(cmd, ctx));
	else if (cmd->builtin == BI_PWD)
		state = (builtin_pwd(ctx));
	else if (cmd->builtin == BI_EXIT)
		state = (builtin_exit(cmd, ctx));
	else if (cmd->builtin == BI_ECHO)
		state = (builtin_echo(cmd));
	dup2(fd_in, STDIN_FILENO);
	dup2(fd_out, STDOUT_FILENO);
	close(fd_in);
	close(fd_out);
	return (state);
}
/*
external -> exec by bin/cmd (in child/ with fork)
builtin -> exec by shell (in parent/ no fork)
*/
int	execute(t_cmd *cmd, t_tokenizer_ctx *ctx)
{
	if (cmd->builtin == BI_NONE)
		return (external(cmd, ctx));
	else
		return (builtin(cmd, ctx));
	return (SUCCESS);
}
