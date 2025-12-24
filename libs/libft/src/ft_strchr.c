/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:14:36 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:40:14 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (unsigned char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

// int	main(void)
// {
// 	char str[5] = "ABCD";
// 	char *p;

// 	printf("%p\n", (void *)str);
// 	p = ft_strchr(str, 0);
// 	printf("%p\n", (void *)p);
// 	p = ft_strchr(str, 66);
// 	printf("%c\n", *p);
// 	p = ft_strchr(str, '\0');
// 	printf("%c\n", *p);
// 	return (0);
// }