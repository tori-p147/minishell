/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:06:57 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/09 19:44:08 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (0 <= c && c <= 127)
		return (TRUE);
	return (FALSE);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isascii('a'));
// 	printf("%d\n", ft_isascii(256));
// 	return (0);
// }