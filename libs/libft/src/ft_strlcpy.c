/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 22:25:14 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 23:23:06 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	size_t	src_len;

	src_len = ft_strlen(src);
	if (size == 0)
		return (src_len);
	while (--size && *src)
		*(dest++) = *(src++);
	*dest = '\0';
	return (src_len);
}

// int	main(void)
// {
// 	char	src[] = "abcd";
// 	char	dest[10];

// 	memset(dest, 'A', 10);
// 	printf("%zu\n", ft_strlcpy(dest, src, 0));
// 	printf("%zu\n", ft_strlcpy(dest, src, 1));
// 	printf("%zu\n", ft_strlcpy(dest, src, 2));
// 	printf("%zu\n", ft_strlcpy(dest, src, -1));
// 	printf("%zu\n", ft_strlcpy(dest, "", 42));
// 	printf("%zu\n", ft_strlcpy(dest, "1", 42));
// 	return (0);
// }
