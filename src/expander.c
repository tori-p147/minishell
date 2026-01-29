/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:09:21 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/29 11:50:27 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*get_value_by_key(t_env *env, char *key)
{
	t_env	*found_env;

	found_env = find_env(env, key);
	if (!found_env)
		return (NULL);
	// printf("found env VALUE = %s\n", found_env->value);
	return (found_env->value);
}

size_t	expand_variable(t_tokenizer_ctx *ctx, size_t i)
{
	size_t	start;
	char	*var_name;
	char	*value;
	char	*tmp;

	start = ++i;
	if (ctx->line[start] == '?')
	{
		printf("EXPAND STATUS %d\n", ctx->shell->status);
		value = ft_itoa(ctx->shell->status);
		i = start + 1;
	}
	else
	{
		if (!is_var_char(ctx->line[i]))
			return (start - 1);
		while (is_var_char(ctx->line[i]))
			i++;
		var_name = ft_substr(ctx->line, start, i - start);
		printf("expand var name = %s\n", var_name);
		value = get_value_by_key(ctx->shell->env, var_name);
		free(var_name);
		if (!value)
			ctx->token = NULL;
	}
	if (!ctx->token)
		ctx->token = ft_strdup(value);
	else
	{
		tmp = ft_strjoin(ctx->token, value);
		free(ctx->token);
		ctx->token = tmp;
		printf("ctx->token = %s\n", ctx->token);
	}
	if (ctx->line[start] == '?')
		free(value);
	printf("i - 1 = %ld\n", i - 1);
	return (i - 1);
}
