/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:22:50 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/08 20:20:42 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// if dest == src -> return dest
// dest > src overlap -> copy from end len--
// dest < src = copy from start
void	*ft_memmove(void *dest, const void *src, size_t n)
{
	char	*pdest;
	char	*psrc;

	if (dest == src && n == 0)
		return (dest);
	if (!dest && !src)
		return (NULL);
	pdest = (char *)dest;
	psrc = (char *)src;
	if (dest > src)
		while (n--)
			pdest[n] = psrc[n];
	else
	{
		while (n--)
			*(pdest++) = *(psrc++);
	}
	return (dest);
}

// int	main(void)
// {
// 	char str[SIZE] = "123456789";
// 	char *p;

// 	p = str + 1;
// 	ft_memmove(str, p, 2);
// 	printf("%s\n", str);
// 	return (0);
// }