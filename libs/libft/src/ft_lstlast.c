/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:09:57 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:37:11 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

// 	t_list *last = ft_lstlast(head);
// 	printf("last element content = %s\n", (char *)last->content);
// 	return (0);
// }