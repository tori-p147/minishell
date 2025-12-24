/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 19:19:31 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:24:10 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
//search from "s" pointer first chr "c" in "n" bytes
void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	size_t			i;
	unsigned char	uc;

	str = (unsigned char *)s;
	uc = (unsigned char)c;
	i = -1;
	while (++i < n)
	{
		if (str[i] == uc)
			return ((void *)str + i);
	}
	return (NULL);
}

// int	main(void)
// {
// 	char	str[5] = "ABCD";
// 	char	*p;

// 	p = ft_memchr(str, 77, 2);
// 	printf("%p\n", (void *)p);
// 	p = ft_memchr(str, 66, 2);
// 	printf("%c\n", *p);
// 	return (0);
// }
