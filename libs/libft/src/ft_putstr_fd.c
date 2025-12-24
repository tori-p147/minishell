/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 15:19:14 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 22:07:29 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putstr_fd(char *s, int fd)
{
	write(fd, s, ft_strlen(s));
}

// int	main(void)
// {
// 	char s[6] = "123456";
// 	char buff[SIZE];
// 	size_t readBytes;
// 	int fd;
// 	fd = open("text.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
// 	if (fd == -1)
// 	{
// 		perror("file not opened");
// 		return (1);
// 	}
// 	ft_putstr_fd(s, fd);
// 	lseek(fd, 0, SEEK_SET);
// 	readBytes = read(fd, buff, sizeof(buff) - 1);
// 	buff[readBytes] = '\0';
// 	printf("%s", buff);
// 	close(fd);
// 	return (0);
// }