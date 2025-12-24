/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:05:57 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:35:25 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//dup of string
char	*ft_strdup(const char *s)
{
	int		len;
	char	*mem;

	len = ft_strlen(s);
	mem = malloc(len + 1);
	if (!mem)
		return (NULL);
	ft_memcpy(mem, s, len);
	mem[len] = '\0';
	return (mem);
}

// int	main(void)
// {
// 	char str[20] = "abcd";
// 	char *p;
// 	p = ft_strdup(str);
// 	printf("%s", p);
// 	return (0);
// }