/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:19:40 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/12/21 22:55:50 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	sum_len;
	size_t	s1_len;
	size_t	s2_len;
	char	*dest;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	sum_len = s1_len + s2_len;
	dest = malloc(sum_len + 1);
	if (!dest)
		return (NULL);
	ft_memcpy(dest, s1, s1_len);
	ft_memcpy(dest + s1_len, s2, s2_len + 1);
	return (dest);
}

// int	main(void)
// {
// 	char s1[9] = "ABCDE";
// 	char s2[9] = "FGHJ";
// 	char *p;

// 	p = ft_strjoin(s1, s2);
// 	printf("%s\n", p);
// 	return (0);
// }