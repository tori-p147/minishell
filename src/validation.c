/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:54:44 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/04 17:33:23 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

size_t	is_var_char(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (1);
	return (0);
}

int	is_export_valid(t_cmd *cmd)
{
	size_t	i;
	size_t	j;
	size_t	len;
	char	c;

	i = 1;
	while (cmd->argv[i])
	{
		j = -1;
		len = ft_strlen(cmd->argv[i]);
		while (++j < len)
		{
			c = cmd->argv[i][j];
			printf("curr: %c\n", c);
			if (c == '=')
				continue ;
			else if ((j == 0 && (!ft_isalpha(c) || c == '_')) || !is_var_char(c))
			{
				printf("export: not an identifier: %s\n", cmd->argv[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
