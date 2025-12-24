/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 12:12:39 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:07:26 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = NULL;
	while (*s)
	{
		if (*s == (unsigned char)c)
			last = s;
		s++;
	}
	if ((char)c == 0)
		return ((char *)s);
	return ((char *)last);
}

// int	main(void)
// {
// 	char str[5] = "ABCD";
// 	char *p;

// 	p = ft_strrchr(str, 77);
// 	printf("%p\n", (void *)p);
// 	p = ft_strrchr(str, 66);
// 	printf("%c\n", *p);
// 	p = ft_strrchr(str, '\0');
// 	printf("%c\n", *p);
// 	return (0);
// }