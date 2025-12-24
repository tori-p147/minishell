/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:57:53 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 20:05:20 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (32 <= c && c <= 126)
		return (TRUE);
	return (FALSE);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isprint(' '));
// 	printf("%d\n", ft_isprint('\0'));
// 	return (0);
// }
