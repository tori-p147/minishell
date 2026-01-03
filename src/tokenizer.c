/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:37 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/03 19:35:53 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

static size_t	normal_process(t_tokenizer_ctx *ctx, size_t i)
{
	if (ctx->c == '\'')
		ctx->state = IN_SINGLE_QUOTE;
	else if (ctx->c == '\"')
		ctx->state = IN_DOUBLE_QUOTE;
	else if (ctx->c == '$')
		i = expand_variable(ctx, i);
	else if ((ctx->c == ' ' || ctx->c == '\t'))
	{
		add_token(ctx);
		ctx->token = NULL;
	}
	else
	{
		ctx->token = strjoin_char(ctx);
		printf("current %s\n", ctx->token);
	}
	return (i);
}

static void	single_quote_process(t_tokenizer_ctx *ctx)
{
	if (ctx->c == '\'')
		ctx->state = NORMAL;
	else
		ctx->token = strjoin_char(ctx);
}

static size_t	double_quote_process(t_tokenizer_ctx *ctx, size_t i)
{
	if (ctx->c == '\"')
		ctx->state = NORMAL;
	else if (ctx->c == '$')
		i = expand_variable(ctx, i);
	else
		ctx->token = strjoin_char(ctx);
	return (i);
}

char	**tokenize(t_tokenizer_ctx *ctx)
{
	size_t	i;

	i = -1;
	ctx->line_len = ft_strlen(ctx->line);
	while (++i < ctx->line_len)
	{
		ctx->c = ctx->line[i];
		if (ctx->state == NORMAL)
			i = normal_process(ctx, i);
		else if (ctx->state == IN_SINGLE_QUOTE)
			single_quote_process(ctx);
		else if (ctx->state == IN_DOUBLE_QUOTE)
			i = double_quote_process(ctx, i);
	}
	if (ctx->state != NORMAL)
		error_exit(ctx, EXIT_SYNTAX_ERROR);
	if (ctx->token)
	{
		add_token(ctx);
		ctx->token = NULL;
	}
	print_tokens(ctx->tokens);
	return (ctx->tokens);
}
