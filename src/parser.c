/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 19:48:37 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/21 23:19:45 by vmatsuda         ###   ########.fr       */
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

	new = malloc(sizeof(char) * (i + 1));
	if (!new)
	{
		free(tokens);
		return (NULL);
	}
	j = -1;
	while (++j < i)
		new[j] = tokens[j];
	free(tokens);
	return (new);
}

char	**add_token(char **tokens, char *current)
{
	char	**new;
	size_t	i;

	i = 0;
	if (!tokens)
	{
		tokens = malloc(sizeof(char) * 2);
		if (!tokens)
			return (NULL);
		tokens[i] = current;
		tokens[i + 1] = NULL;
		return (tokens);
	}
	else
	{
		while (tokens[i])
			i++;
		new = copy_tokens(tokens, i);
		if (!new)
			return (NULL);
		new[i] = current;
		new[i + 1] = NULL;
	}
	return (new);
}

char	*strjoin_char(char *str, char c)
{
	char	*new;
	size_t	str_len;

	new = NULL;
	if (!str)
	{
		str_len = 1;
		str = malloc(sizeof(char) * (str_len + 1));
		*str = c;
		str[str_len] = 0;
		return (str);
	}
	str_len = ft_strlen(str);
	new = malloc(sizeof(char) * (str_len + 2));
	new = ft_memcpy(new, str, str_len);
	new[str_len] = c;
	new[str_len + 1] = 0;
	return (new);
}

char	**parse(char *in_line)
{
	size_t			i;
	size_t			line_len;
	char			c;
	char			**tokens;
	char			*current;
	t_parser_state	state;
	size_t			j;

	i = -1;
	c = 0;
	tokens = NULL;
	current = NULL;
	j = 0;
	state = 0;
	line_len = ft_strlen(in_line);
	// 1) space / '\t' / '' / "" not found -> 1 token
	// 2)'' or "" not found -> tokens by space or '\t'
	// 3) one ' / " -> syntax error: unexpected end of file and return prompt
	// (return shell-state: exit_status 2, must show $? - command result)
	// 4) space only -> new prompt / not save in history
	// 5) '...' / "..." -> parse line within quote (without save quote)
	while (++i < line_len)
	{
		c = in_line[i];
		if (state == NORMAL)
		{
			printf("state %d current %s c %c\n", state, current, c);
			if (c == '\'')
				state = IN_SINGLE_QUOTE;
			else if (c == '\"')
				state = IN_DOUBLE_QUOTE;
			else if ((c == ' ' || c == '\t') && current)
			{
				tokens = add_token(tokens, current);
				if (!tokens)
					free_and_exit(in_line, current, EXIT_FAILURE);
				current = NULL;
			}
			else
			{
				current = strjoin_char(current, c);
				printf("current %s\n", current);
			}
		}
		else if (state == IN_SINGLE_QUOTE)
		{
			printf("state %d current %s c %c\n", state, current, c);
			if (c == '\'')
				state = NORMAL;
			else if (c == '\"')
				state = IN_DOUBLE_QUOTE;
			else
				current = strjoin_char(current, c);
		}
		else if (state == IN_DOUBLE_QUOTE)
		{
			printf("state %d current %s c %c\n", state, current, c);
			if (c == '\"')
				state = NORMAL;
			else if (c == '\'')
				state = IN_SINGLE_QUOTE;
			else
				current = strjoin_char(current, c);
		}
	}
	if (state != NORMAL)
	{
		printf("state %d current %s c %c\n", state, current, c);
		print_error(EXIT_SYNTAX_ERROR);
		return (NULL);
	}
	if (current)
	{
		tokens = add_token(tokens, current);
		if (!tokens)
			free_and_exit(in_line, current, EXIT_FAILURE);
	}
	size_t k = 0;
	while (tokens[k])
	{
		printf("token[%zu] = %s\n", k, tokens[k]);
		k++;
	}
	return (tokens);
}
