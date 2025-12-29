/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 20:23:12 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/29 12:42:54 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"

void	free_tokens(char **tokens)
{
	int	i;

	i = 0;
	while (tokens[i])
		free(tokens[i++]);
	free(tokens);
}

void	free_ctx(t_tokenizer_ctx *ctx)
{
	free(ctx->line);
	free(ctx->token);
	free_tokens(ctx->tokens);
}

void	free_and_exit(t_tokenizer_ctx *ctx, int status)
{
	free_ctx(ctx);
	exit(status);
}
