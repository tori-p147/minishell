/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 21:48:50 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 20:04:04 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if (ft_isalpha(c) || ft_isdigit(c))
		return (TRUE);
	return (FALSE);
}

// int	main(void)
// {
// 	printf("%d\n", ft_isanum('a'));
// 	printf("%d\n", ft_isanum(1));
// 	printf("%d\n", ft_isanum('!'));
// 	return (0);
// }