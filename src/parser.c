/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:37 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/27 18:39:34 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

void	print_error(t_exit_status status)
{
	if (status == EXIT_SYNTAX_ERROR)
		printf("syntax error\n");
}

char	**copy_tokens(char **tokens, size_t i)
{
	char	**new;
	size_t	j;

	new = malloc(sizeof(char *) * (i + 1));
	if (!new)
	{
		free(tokens);
		return (NULL);
	}
	j = -1;
	while (++j < i)
		new[j] = tokens[j];
	free(tokens);
	new[i] = NULL;
	return (new);
}

char	**add_token(t_tokenizer_ctx *ctx)
{
	char	**new;
	size_t	i;

	i = 0;
	if (!ctx->token)
		return (ctx->tokens);
	if (!ctx->tokens)
	{
		ctx->tokens = malloc(sizeof(char *) * (2));
		if (!ctx->tokens)
			return (NULL);
	}
	else
	{
		while (ctx->tokens[i])
			i++;
		new = copy_tokens(ctx->tokens, i);
		if (!new)
			return (NULL);
		ctx->tokens = new;
	}
	ctx->tokens[i] = ctx->token;
	ctx->tokens[i + 1] = NULL;
	return (ctx->tokens);
}

char	*strjoin_char(t_tokenizer_ctx *ctx, char c)
{
	char	*new;
	size_t	token_len;

	new = NULL;
	if (!ctx->token)
	{
		ctx->token = malloc(sizeof(char) * 2);
		if (!ctx->token)
			free_and_exit(ctx, EXIT_FAILURE);
		ctx->token[0] = c;
		ctx->token[1] = 0;
		return (ctx->token);
	}
	token_len = ft_strlen(ctx->token);
	new = malloc(sizeof(char) * (token_len + 2));
	if (!new)
		free_and_exit(ctx, EXIT_FAILURE);
	ft_memcpy(new, ctx->token, token_len);
	free(ctx->token);
	ctx->token = new;
	ctx->token[token_len] = c;
	ctx->token[token_len + 1] = 0;
	return (ctx->token);
}

void print_tokens(char **tkns)
{
	size_t j = 0;
	while (tkns[j])
	{
		printf("tokens[%zu] = %s\n", j, tkns[j]);
		j++;
	}
}

char	**parse(t_tokenizer_ctx *ctx)
{
	size_t	i;
	char	c;
	size_t	j;

	i = -1;
	c = 0;
	j = 0;
	ctx->line_len = ft_strlen(ctx->line);
	while (++i < ctx->line_len)
	{
		c = ctx->line[i];
		if (ctx->state == NORMAL)
		{
			if (c == '\'')
				ctx->state = IN_SINGLE_QUOTE;
			else if (c == '\"')
				ctx->state = IN_DOUBLE_QUOTE;
			else if ((c == ' ' || c == '\t'))
			{
				ctx->tokens = add_token(ctx);
				if (!ctx->tokens)
					free_and_exit(ctx, EXIT_FAILURE);
				ctx->token = NULL;
			}
			else
			{
				ctx->token = strjoin_char(ctx, c);
				printf("current %s\n", ctx->token);
			}
		}
		else if (ctx->state == IN_SINGLE_QUOTE)
		{
			if (c == '\'')
				ctx->state = NORMAL;
			else
				ctx->token = strjoin_char(ctx, c);
		}
		else if (ctx->state == IN_DOUBLE_QUOTE)
		{
			if (c == '\"')
				ctx->state = NORMAL;
			else
				ctx->token = strjoin_char(ctx, c);
		}
	}
	if (ctx->state != NORMAL)
	{
		print_error(EXIT_SYNTAX_ERROR);
		return (NULL);
	}
	if (ctx->token)
	{
		ctx->tokens = add_token(ctx);
		if (!ctx->tokens)
			free_and_exit(ctx, EXIT_FAILURE);
		ctx->token = NULL;
	}
	print_tokens(ctx->tokens);
	return (ctx->tokens);
}
