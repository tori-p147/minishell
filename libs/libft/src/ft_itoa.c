/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/27 20:03:40 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 20:06:06 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	convert_int_to_char(int nbr, char *buff)
{
	int	i;

	i = 0;
	while (nbr > 0)
	{
		buff[i] = nbr % 10 + '0';
		nbr /= 10;
		i++;
	}
	return (i);
}

static void	reverse_buffer(char *buff, int last)
{
	int		first;
	char	tmp;

	first = 0;
	while (first < last)
	{
		tmp = buff[first];
		buff[first] = buff[last];
		buff[last] = tmp;
		first++;
		last--;
	}
}

static char	*create_itoa(char *buff, int is_negative, int size)
{
	char	*itoa;

	itoa = (char *)malloc(size + is_negative + 1);
	if (!itoa)
		return (NULL);
	if (is_negative)
	{
		itoa[0] = '-';
		ft_memcpy(itoa + 1, buff, size);
	}
	else
		ft_memcpy(itoa, buff, size);
	itoa[size + is_negative] = '\0';
	return (itoa);
}

char	*ft_itoa(int nbr)
{
	char	buff[SIZE];
	int		size;
	int		is_negative;

	if (nbr == 0)
		return (ft_strdup("0"));
	if (nbr == INT_MIN)
		return (ft_strdup("-2147483648"));
	size = 0;
	is_negative = 0;
	if (nbr < 0)
	{
		nbr = -nbr;
		is_negative = 1;
	}
	size = convert_int_to_char(nbr, buff);
	reverse_buffer(buff, size - 1);
	return (create_itoa(buff, is_negative, size));
}

// int	main(void)
// {
// 	printf("%s\n", ft_itoa(INT_MAX));
// 	printf("%s\n", ft_itoa(INT_MIN));
// 	printf("%s\n", ft_itoa(0));
// 	return (0);
// }
