/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 20:07:56 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 22:11:19 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

// int	main(void)
// {
// 	char str[100] = "HELLO";
// 	printf("%s\n", str);
// 	ft_bzero(str, 42);
// 	printf("%s\n", str);
// 	printf("%s\n", str +1);
// 	return (0);
// }