/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 13:46:14 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/05 20:38:22 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// copy string s from int start with len length
// if start index > length src => ""\0
// 
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	src_size;
	char			*substr;

	if (!s)
		return (NULL);
	src_size = ft_strlen(s);
	if (start > src_size)
		return (ft_strdup(""));
	if (src_size - start < len)
		len = src_size - start;
	substr = (char *)malloc(len + 1);
	if (!substr)
		return (NULL);
	ft_memcpy(substr, s + start, len);
	substr[len] = '\0';
	return (substr);
}

// int	main(void)
// {
// 	char	str[9] = "ABCDEFGHJ";
// 	char	*p;

// 	p = ft_substr(str, 2, 3);
// 	printf("%s\n", p);
// 	return (0);
// }
