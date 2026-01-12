/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:27:11 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/12 11:54:14 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	error_exit(t_tokenizer_ctx *ctx, t_exit_status status)
{
	if (status == EXIT_SYNTAX_ERROR)
		printf("syntax error\n");
	free_ctx(ctx, EXIT_FAILURE);
}


void	print_error(char *cmd_name, char *arg, t_error_type type)
{
	if (type == NO_SUCH_FILE_OR_DIR)
		printf("minishell: %s: %s: No such file or directory\n", cmd_name, arg);
}
