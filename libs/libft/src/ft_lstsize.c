/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 21:49:13 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/08 21:03:59 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	count;

	if (!lst)
		return (0);
	count = 0;
	while (lst)
	{
		count++;
		lst = lst->next;
	}
	return (count);
}

// int	main(void)
// {
// 	t_list *head = NULL;
// 	t_list *second = NULL;
// 	t_list *third = NULL;

// 	head = (t_list *)malloc(sizeof(t_list));
// 	second = (t_list *)malloc(sizeof(t_list));
// 	third = (t_list *)malloc(sizeof(t_list));

// 	head->content = "1";
// 	head->next = second;

// 	second->content = "2";
// 	second->next = third;

// 	third->content = "3";
// 	third->next = NULL;

// 	printf("list size = %d\n", ft_lstsize(head));

// 	while (head != NULL)
// 	{
// 		printf("node.content = %s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	return (0);
// }