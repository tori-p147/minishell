/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 20:55:39 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/07 21:46:29 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	free_content(void *content)
// {
// 	free(content);
// }

void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	if (!lst || !*lst || !del)
		return ;
	if ((*lst)->next)
		ft_lstclear(&((*lst)->next), del);
	ft_lstdelone(*lst, del);
	*lst = NULL;
}

// int	main(void)
// {
// 	t_list *head = NULL;
// 	t_list *second = NULL;
// 	t_list *third = NULL;

// 	head = (t_list *)malloc(sizeof(t_list));
// 	second = (t_list *)malloc(sizeof(t_list));
// 	third = (t_list *)malloc(sizeof(t_list));

// 	head->content = strdup("1");
// 	head->next = second;

// 	second->content = strdup("2");
// 	second->next = third;

// 	third->content = strdup("3");
// 	third->next = NULL;

// 	t_list **lst = &head;

// 	ft_lstclear(lst, free_content);

// 	if (head == NULL)
// 		printf("List is cleared: head == NULL\n");

// 	return (0);
// }