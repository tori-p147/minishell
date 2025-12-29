/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:27:11 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/29 13:28:14 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	error_exit(t_tokenizer_ctx *ctx, t_exit_status status)
{
	if (status == EXIT_SYNTAX_ERROR)
		printf("syntax error\n");
	free_and_exit(ctx, EXIT_FAILURE);
}
