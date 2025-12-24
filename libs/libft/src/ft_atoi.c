/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/26 16:09:43 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 20:02:13 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int	sign;
	int	result;

	sign = 1;
	result = 0;
	while (*str == '\f' || *str == '\n' || *str == '\r' || *str == '\t'
		|| *str == '\v' || *str == ' ')
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = ((result * 10) + (*str - '0'));
		str++;
	}
	return (result * sign);
}

// int	main(void)
// {
// 	printf("%d\n", ft_atoi("-2147483647"));
// 	printf("%d\n", ft_atoi("a7"));
// 	printf("%d\n", ft_atoi("\t\n\v\f\r--1")); // 0
// 	printf("%d\n", ft_atoi("\t\n\v\f\r++1")); // 0
// 	return (0);
// }