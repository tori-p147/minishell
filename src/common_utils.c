/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   common_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/16 14:41:15 by vmatsuda          #+#    #+#             */
/*   Updated: 2026/01/16 16:38:49 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "shell.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while ((s1[i] || s2[i]))
	{
		if ((unsigned char)s1[i] != (unsigned char)s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

void	print_redirs(t_redir *redirs)
{
	t_redir	*curr;

	curr = redirs;
	while (curr)
	{
		printf("redir.type %d redir.file %s\n", curr->type, curr->file);
		curr = curr->next;
	}
}

void	print_argv(char **argv)
{
	size_t	j;

	j = 0;
	while (argv[j])
	{
		printf("argv[%zu] = %s\n", j, argv[j]);
		j++;
	}
}
