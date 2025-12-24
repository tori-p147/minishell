/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 22:04:37 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:33:36 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char *))
{
	char	*start;

	if (!s || !f)
		return ;
	start = s;
	while (*s)
	{
		f((unsigned int)(s - start), s);
		s++;
	}
}

// static void	ft_upstring(unsigned int i, char *c)
// {
// 	if (*c >= 'a' && *c <= 'z')
// 		*c = *c - 32;
// }

// int	main(void)
// {
// 	char str[] = "abcd";

// 	ft_striteri(str, ft_upstring);
// 	printf("%s", str);
// 	return (0);
// }