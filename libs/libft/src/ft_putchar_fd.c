/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 14:41:20 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/04/29 16:20:52 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}

// int main()
// {
// 	int fd = open("text.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("file not opened");
// 		return (1);
// 	}
// 	ft_putchar_fd('1', fd);
// 	char buff[SIZE];
// 	lseek(fd, 0, SEEK_SET);
// 	size_t size = read(fd, buff, sizeof(buff) - 1);
// 	buff[size] = '\0';
// 	printf("%s", buff);
// 	close(fd);
// 	return (0);
// }
