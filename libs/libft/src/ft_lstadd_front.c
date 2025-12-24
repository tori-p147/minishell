/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 22:05:29 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/06 18:10:03 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	if (!lst || !new)
		return ;
	new->next = *lst;
	*lst = new;
}

// int	main(void)
// {
// 	t_list *old = (t_list *)malloc(sizeof(t_list));

// 	old->content = (char *)"old_node";
// 	old->next = NULL;

// 	t_list *new = (t_list *)malloc(sizeof(t_list));

// 	new->content = (char *)"new_node";
// 	new->next = NULL;

// 	t_list **lst = (t_list **)malloc(sizeof(t_list) * 2);
// 	lst = &old;
// 	t_list *head = *lst;
// 	while (head != NULL)
// 	{
// 		printf("before_node.content = %s\n", (char *)head->content);
// 		head = head->next;
// 	}

// 	ft_lstadd_front(lst, new);
// 	printf("\n");
// 	head = *lst;

// 	while (head != NULL)
// 	{
// 		printf("after_node.content = %s\n", (char *)head->content);
// 		head = head->next;
// 	}
// 	return (0);
// }