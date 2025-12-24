/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:25:12 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/06 15:12:45 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (!lst || !new)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		last = ft_lstlast(*lst);
		last->next = new;
	}
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

// 	t_list **lst = (t_list **)malloc(sizeof(t_list) * 3);

// 	t_list *new = (t_list *)malloc(sizeof(t_list));

// 	new->content = (char *)"new_node";
// 	new->next = NULL;

// 	ft_lstadd_back(lst, new);
// 	head = *lst;

// 	while (head != NULL)
// 	{
// 		printf("after_node.content = %s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	return (0);
// }