/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalpha.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:53:14 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 20:04:38 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalpha(int c)
{
	if (('A' <= c && c <= 'Z') || ('a' <= c && c <= 'z'))
		return (TRUE);
	return (FALSE);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isalpha('a'));
// 	printf("%d\n", ft_isalpha(-1));
// 	return (0);
// }
