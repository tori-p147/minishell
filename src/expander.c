/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 16:09:21 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/04 15:18:58 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shell.h"
#include "libft.h"

char	*get_by_key(t_tokenizer_ctx *ctx, char *key)
{
	char	*val;
	t_env	*curr;

	val = NULL;
	curr = ctx->shell->env;
	while (curr->next)
	{
		if (ft_strncmp(key, curr->key, ft_strlen(key)))
			return (curr->value);
		curr = curr->next;
	}
	return (val);
}

size_t	expand_variable(t_tokenizer_ctx *ctx, size_t i)
{
	size_t	start;
	char	*name;

	start = i;
	i++;
	// case if $ next symbol not valid
	if (!is_var_char(ctx->line[i]))
		return (i - 1);
	while (is_var_char(ctx->line[i]))
		i++;
	name = ft_substr(ctx->line, start, i - start);
	ctx->token = get_by_key(ctx, name);
	free(name);
	return (i - 1);
}
