/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:14:04 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:23:54 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*ps1;
	unsigned char	*ps2;

	ps1 = (unsigned char *)s1;
	ps2 = (unsigned char *)s2;
	i = -1;
	while (++i < n)
	{
		if (ps1[i] != ps2[i])
			return (ps1[i] - ps2[i]);
	}
	return (0);
}

// int main()
// {
// 	char s2[] = {0, 0, 127, 0};
// 	char s3[] = {0, 0, 42, 0};

// 	int result = ft_memcmp(s2, s3, 4);
// 	printf("Result of ft_memcmp: %d\n", result);
// 	return (0);
// }