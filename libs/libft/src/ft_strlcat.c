/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 14:24:24 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/06 21:23:49 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// dest len >= size ? max size
// copy_len > 0 - how match symbols can add not over limit size
// dst[dest_len + i] copy at end of dest
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dest_len;
	size_t	src_len;
	size_t	copy_len;
	size_t	i;

	dest_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dest_len >= size)
		return (size + src_len);
	copy_len = size - dest_len - 1;
	i = 0;
	if (copy_len > 0)
	{
		while (i < copy_len && src[i])
		{
			dst[dest_len + i] = src[i];
			i++;
		}
		dst[dest_len + i] = '\0';
	}
	return (dest_len + src_len);
}

// int	main(void)
// {
// 	char	dst[30];
// 	ft_memset(dst, 0, 30);
// 	char	*src = (char *)"AAAAAAAAA";

// 	printf("%zu\n", ft_strlcat(dst, src, 6)); //13 but 9
// 	printf("%zu\n", ft_strlcat(dst, src, -1)); //14 ++
// 	printf("%zu\n", ft_strlcat(dst, src, 17)); //24 but 9
// 	printf("%zu\n", ft_strlcat(dst, src, 1)); //9 ++
// 	printf("%zu\n", ft_strlcat(dst, "123", 1)); //3
// 	printf("%zu\n", ft_strlcat(dst, "123", 2)); //3
// 	printf("%zu\n", ft_strlcat(dst, "123", 3)); //3
// 	printf("%zu\n", ft_strlcat(dst, "123", 4)); //3
// 	return (0);
// }
