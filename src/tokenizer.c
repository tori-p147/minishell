/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:37 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/03 18:39:49 by vmatsuda         ###   ########.fr       */
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
	else if (is_operator(ctx, i))
	{
		if (ctx->token)
			add_token(ctx);
		i = split_operator(ctx, i);
	}
	else if ((ctx->c == ' ' || ctx->c == '\t'))
		add_token(ctx);
	else
		ctx->token = strjoin_char(ctx);
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
	{
		printf("minishell: syntax error: unexpected end of file\n");
		ctx->shell->status = SYNTAX_ERROR;
	}
	if (ctx->token)
	{
		add_token(ctx);
		ctx->token = NULL;
	}
	// print_tokens(ctx->tokens);
	return (ctx->tokens);
}
