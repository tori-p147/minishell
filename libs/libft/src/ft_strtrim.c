/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 15:37:31 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/06 21:27:52 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in_charset(char c, char const *set)
{
	while (*set)
	{
		if (c == *set)
			return (1);
		set++;
	}
	return (0);
}

static char	*create_str(const char *s1, int start, size_t len)
{
	size_t	i;
	char	*trimmed;

	trimmed = ft_calloc(len + 1, 1);
	if (!trimmed)
		return (NULL);
	i = 0;
	while (i < len)
	{
		trimmed[i] = s1[start + i];
		i++;
	}
	return (trimmed);
}

// cut symbols in set from s1
char	*ft_strtrim(char const *s1, char const *set)
{
	int	start;
	int	last;

	if (!s1 || !set)
		return (NULL);
	start = 0;
	last = ft_strlen(s1) - 1;
	while (s1[start] && is_in_charset(s1[start], set))
		start++;
	while (last > start && is_in_charset(s1[last], set))
		last--;
	return (create_str(s1, start, last - start + 1));
}

// int	main(void)
// {
// 	char s1[] = "ababaaaMy name is Simonbbaaabba";
// 	char set[] = "ab"; // trim result "My name is Simon"

// 	char *p = ft_strtrim(s1, set);
// 	printf("%s\n", p);
// 	return (0);
// }