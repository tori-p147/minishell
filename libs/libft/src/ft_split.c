/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 17:55:25 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 20:53:32 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**free_copies(char **copies)
{
	char	**pcopies;

	pcopies = copies;
	while (*pcopies)
		free(*(pcopies++));
	free(copies);
	return (NULL);
}

// 1. while find char -> skip
// 2. if found word -> count +1 and skip length of word
static int	count_words(const char *str, char c)
{
	int	count;
	int	i;

	count = 0;
	i = 0;
	while (str[i])
	{
		while (str[i] && str[i] == c)
			i++;
		if (str[i])
		{
			count++;
			while (str[i] && str[i] != c)
				i++;
		}
	}
	return (count);
}

// 0. count words in str
// 1. start read str
// 2. skip char symbols in str
// 3. if find start of word ->
// incrementing start while not found a charset symbol
// 4. start > 0 = new word found
// 5. add strings to copies array by substr
// 6. move pointer str to next word or charset symbol

char	**ft_split(char const *str, char c)
{
	int		i;
	char	**copies;
	int		start;

	copies = (char **)malloc(sizeof(char *) * (count_words(str, c) + 1));
	if (!copies || !str)
		return (NULL);
	i = 0;
	while (*str)
	{
		while (*str && *str == c)
			str++;
		start = 0;
		while (str[start] && str[start] != c)
			start++;
		if (start > 0)
		{
			copies[i] = ft_substr(str, 0, start);
			if (!copies[i++])
				return (free_copies(copies));
			str += start;
		}
	}
	copies[i] = NULL;
	return (copies);
}

// int	main(void)
// {
// 	char *str;
// 	char c;
// 	char **ar;
// 	int i;

// 	str = "^^^1^^2a,^^^^3^^^^--h^^^^";
// 	c = '^';
// 	ar = ft_split(str, c);
// 	i = 0;
// 	while (ar[i] != NULL)
// 	{
// 		printf("ar[%d] = %s\n", i, ar[i]);
// 		i++;
// 	}
// 	return (0);
// }