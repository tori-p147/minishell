/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:14:03 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/08 20:30:26 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy from -> to n-bytes
void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*pdest;
	const unsigned char	*psrc;

	if (!dest && !src)
		return (NULL);
	pdest = dest;
	psrc = src;
	while (n--)
		*(pdest++) = *(psrc++);
	return (dest);
}

// int	main(void)
// {
// 	char str[5] = "HELLO";
// 	char *dest[SIZE];
// 	void *p = ft_memcpy(NULL, NULL, 3);
// 	printf("%p\n", p);
// 	printf("%s\n", str);
// 	printf("%s\n", str);
// 	printf("%s\n", str + 1);
// 	return (0);
// }