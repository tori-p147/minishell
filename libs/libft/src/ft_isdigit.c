/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 21:02:16 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 20:05:06 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isdigit(int c)
{
	if ('0' <= c && c <= '9')
		return (TRUE);
	return (FALSE);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isdigit('9'));
// 	printf("%d\n", ft_isdigit('0'));
// 	return (0);
// }