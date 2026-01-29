/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/29 13:38:11 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/29 12:16:39 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

size_t is_operator(t_tokenizer_ctx *ctx, size_t i)
{
	if (ctx->c == '<' || ctx->c == '>')
		return (1);
	else if (!ft_strncmp(&ctx->line[i], "<<", 2) || !ft_strncmp(&ctx->line[i], ">>", 2))
		return (1);
	return (0);
}

size_t split_operator(t_tokenizer_ctx *ctx, size_t i)
{
	if (!ft_strncmp(&ctx->line[i], "<<", 2))
	{
		ctx->token = ft_strdup("<<");
		i = i + 1;
	}
	else if (!ft_strncmp(&ctx->line[i], ">>", 2))
	{
		ctx->token = ft_strdup(">>");
		i = i + 1;
	}
	else if (ctx->c == '>')
		ctx->token = ft_strdup(">");
	else if (ctx->c == '<')
		ctx->token = ft_strdup("<");
	add_token(ctx);
	ctx->token = NULL;
	return (i);
}

void	copy_tokens(t_tokenizer_ctx *ctx, size_t i)
{
	char	**new;
	size_t	j;

	new = malloc(sizeof(char *) * (i + 2));
	if (!new)
		free_ctx(ctx, EXIT_FAILURE);
	j = -1;
	while (++j < i)
		new[j] = ctx->tokens[j];
	free(ctx->tokens);
	new[i] = NULL;
	ctx->tokens = new;
}

void	add_token(t_tokenizer_ctx *ctx)
{
	size_t	i;

	i = 0;
	if (!ctx->token)
		return ;
	if (!ctx->tokens)
	{
		ctx->tokens = malloc(sizeof(char *) * (2));
		if (!ctx->tokens)
			free_ctx(ctx, EXIT_FAILURE);
		ctx->tokens[0] = ctx->token;
		ctx->tokens[1] = NULL;
	}
	else
	{
		while (ctx->tokens[i])
			i++;
		copy_tokens(ctx, i);
		ctx->tokens[i] = ctx->token;
		ctx->tokens[i + 1] = NULL;
	}
}

char	*strjoin_char(t_tokenizer_ctx *ctx)
{
	char	*new;
	size_t	token_len;

	new = NULL;
	if (!ctx->token)
	{
		ctx->token = malloc(sizeof(char) * 2);
		if (!ctx->token)
			free_ctx(ctx, EXIT_FAILURE);
		ctx->token[0] = ctx->c;
		ctx->token[1] = 0;
		return (ctx->token);
	}
	token_len = ft_strlen(ctx->token);
	new = malloc(sizeof(char) * (token_len + 2));
	if (!new)
		free_ctx(ctx, EXIT_FAILURE);
	ft_memcpy(new, ctx->token, token_len);
	free(ctx->token);
	ctx->token = new;
	ctx->token[token_len] = ctx->c;
	ctx->token[token_len + 1] = 0;
	return (ctx->token);
}
