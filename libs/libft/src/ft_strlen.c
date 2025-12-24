/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:15:10 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:41:24 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlen(const char *str)
{
	const char	*p;

	p = str;
	while (*p)
		p++;
	return (p - str);
}

// int	main(void)
// {
// 	printf("%zu", ft_strlen("abcd"));
// 	return (0);
// }