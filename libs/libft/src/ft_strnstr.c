/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 15:16:37 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/08 20:54:42 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *find, size_t len)
{
	size_t	i;
	size_t	find_len;

	if (find[0] == 0)
		return ((char *)src);
	find_len = ft_strlen(find);
	if (find_len == 0)
		return ((char *)src);
	i = 0;
	while (src[i] && i + find_len <= len)
	{
		if (ft_strncmp(src + i, find, find_len) == 0)
			return ((char *)src + i);
		i++;
	}
	return (NULL);
}

// int	main(void)
// {
// 	printf("%s\n", ft_strnstr("abcd", "cd", 4));
// 	printf("%s\n", ft_strnstr("abcd", "cd", 2));
// 	printf("%s\n", ft_strnstr("abcd", "", 3));
// 	printf("%s\n", ft_strnstr("", "", -1));
// 	printf("%s\n", ft_strnstr("", "", 0));
// 	printf("%s\n", ft_strnstr("sss", "ddd", 2));
// 	return (0);
// }