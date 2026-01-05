/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:35 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/05 18:06:46 by vmatsuda         ###   ########.fr       */
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
	size_t	i;

	i = 0;
	(void)ctx;
	if (cmd->builtin == BI_EXPORT)
		return (builtin_export(cmd, ctx));
	if (cmd->builtin == BI_UNSET)
		return (builtin_unset(cmd, ctx));
	return (0);
}
