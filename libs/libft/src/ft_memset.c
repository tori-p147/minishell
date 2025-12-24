/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:06:32 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/08 20:31:25 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// *s - dest for copy "n" bytes of c char
void	*ft_memset(void *dest, int c, size_t n)
{
	unsigned char	*pdest;

	pdest = dest;
	while (n--)
		*(pdest++) = (unsigned char)c;
	return (dest);
}

// int	main(void)
// {
// 	void *mem;
// 	int arg;

// 	if (!(mem = malloc(sizeof(*mem) * 15)))
// 		return (0);
// 	memset(mem, 'c', 14);

// 	if (mem != ft_memset(mem, 'c', 5))
// 		write(1, "mem's adress was not returned\n", 30);
// 	write(1, mem, 15);

// if (mem != ft_memset(mem, 'c', 14))
//	write(1, "mem's adress was not returned\n", 30);
// write(1, mem, 15
// if (mem != ft_memset(mem, '\n', 6))
//	write(1, "mem's adress was not returned\n", 30);
// write(1, mem, 15
// if (mem != ft_memset(mem, '\0', 1))
//	write(1, "mem's adress was not returned\n", 30);
// write(1, mem, 15);
// 	return (0);
// }