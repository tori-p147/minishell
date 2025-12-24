/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstiter.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:17:17 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/04 17:58:46 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	change_content(void *content)
// {
// 	char	*c;

// 	c = (char *)content;
// 	if (*c >= 'a' && *c <= 'z')
// 		*c = *c - 32;
// }

void	ft_lstiter(t_list *lst, void (*f)(void *))
{
	if (!lst || !f)
		return ;
	while (lst)
	{
		f(lst->content);
		lst = lst->next;
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

// 	head->content = strdup("a");
// 	head->next = second;

// 	second->content = strdup("b");
// 	second->next = third;

// 	third->content = strdup("c");
// 	third->next = NULL;

// 	ft_lstiter(head, change_content);

// 	t_list *tmp = head;
// 	while (tmp != NULL)
// 	{
// 		printf("node.content = %s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }