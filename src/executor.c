/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:35 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/09 15:54:00 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

/*
how shell start programm:
case 1: if command has / (abs path) -> execve()
case 2: if ./ ../ (relative path) ->
*/

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
	return (SUCCESS);
}
