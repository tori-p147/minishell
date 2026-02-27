/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/03 19:54:44 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/22 20:40:13 by vmatsuda         ###   ########.fr       */
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

int	is_export_valid(t_cmds *cmd)
{
	size_t	i;
	size_t	j;
	char	c;

	i = 1;
	while (cmd->argv[i])
	{
		j = -1;
		while (++j < ft_strlen(cmd->argv[i]))
		{
			c = cmd->argv[i][j];
			printf("curr: %c\n", c);
			if (c == '=')
				continue ;
			else if ((j == 0 && (!ft_isalpha(c) || c == '_'))
				|| !is_var_char(c))
			{
				printf("export: not an identifier: %s\n", cmd->argv[i]);
				return (0);
			}
		}
		i++;
	}
	return (1);
}
