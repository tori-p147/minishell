/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 20:05:36 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/08 20:33:59 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*p;
	size_t	nbytes;

	if (size != 0 && nmemb > SIZE_MAX / size)
		return (NULL);
	nbytes = nmemb * size;
	p = malloc(nbytes);
	if (!p)
		return (NULL);
	ft_bzero(p, nbytes);
	return (p);
}

// int	main(void)
// {
// 	char	*p;

// 	p = ft_calloc(__SIZE_MAX__, __SIZE_MAX__);
// 	if (p == NULL)
// 		printf("calloc(MAX, MAX) return NULL \n");
// 	p = ft_calloc(0, 0);
// 	if (p != NULL)
//     	printf("calloc(0, 0) return pointer \n");
// 	p = ft_calloc(0, 5);
// 	if (p != NULL)
// 		printf("ft_calloc(0, 5): return pointer\n");
// 	p = ft_calloc(5, 0);
// 	if (p != NULL)
// 		printf("ft_calloc(5, 0): return pointer\n");
// 	p = ft_calloc(0, -5);
// 	if (p)
//     	printf("calloc(0, -5) ポインタを返しました（ただし、参照解除はできません）\n");
// 	p = ft_calloc(-5, 0);
// 	if (p)
//     	printf("calloc(-5, 0) ポインタを返しました（ただし、参照解除はできません）\n");
// 	return (0);
// }
