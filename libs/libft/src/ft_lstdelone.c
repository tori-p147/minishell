/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstdelone.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/30 22:53:18 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/04 17:58:43 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	free_content(void *content)
// {
// 	free(content);
// }

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!lst || !del)
		return ;
	del(lst->content);
	free(lst);
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

// 	head->next = third;
// 	ft_lstdelone(second, free_content);

// 	t_list *tmp = head;
// 	while (tmp != NULL)
// 	{
// 		printf("node.content = %s\n", (char *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	return (0);
// }