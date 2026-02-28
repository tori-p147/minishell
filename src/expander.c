/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:09:21 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/02/28 15:22:51 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

char	*get_value_by_key(t_env *env, char *key)
{
	t_env	*found_env;

	found_env = find_env(env, key);
	if (!found_env)
		return ("");
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
		value = get_value_by_key(ctx->shell->env, var_name);
		free(var_name);
	}
	if (!ctx->token)
		ctx->token = ft_strdup(value);
	else
	{
		tmp = ft_strjoin(ctx->token, value);
		free(ctx->token);
		ctx->token = tmp;
	}
	if (ctx->line[start] == '?')
		free(value);
	return (i - 1);
}
