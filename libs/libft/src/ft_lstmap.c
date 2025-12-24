/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmatsuda <vmatsuda@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 21:35:00 by vmatsuda          #+#    #+#             */
/*   Updated: 2025/05/06 18:09:24 by vmatsuda         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// static void	free_content(void *content)
// {
// 	free(content);
// }

// static void	*change_content(void *content)
// {
// 	char	*c;
// 	char	*copy;

// 	c = (char *)content;
// 	copy = malloc(1);
// 	if (!copy)
// 		return (NULL);
// 	*copy = *c;
// 	if (*copy >= 'a' && *copy <= 'z')
// 		*copy = *copy - 32;
// 	return ((void *)copy);
// }

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_node;
	t_list	*new_list;
	void	*new_content;

	new_node = NULL;
	new_list = NULL;
	while (lst)
	{
		new_content = f(lst->content);
		new_node = ft_lstnew(new_content);
		if (!new_node)
		{
			del(new_content);
			ft_lstclear(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back(&new_list, new_node);
		lst = lst->next;
	}
	return (new_list);
}

// void	*add_one(void *p)
// {
// 	void	*r;

// 	r = malloc(sizeof(int));
// 	*(int *)r = *(int *)p + 1;
// 	return (r);
// }

// int	main(void)
// {
// 	int tab[] = {0, 1, 2, 3};
// 	t_list *l = ft_lstnew(tab);
// 	for (int i = 1; i < 0000004; ++i)
// 		ft_lstadd_back(&l, ft_lstnew(tab + i));
// 	t_list *m = ft_lstmap(l, add_one, free_content);
// 	t_list *tmp = l;
// 	printf("Original: \n");
// 	/* 1 2 3 4 */ for (int i = 0; i < 4; ++i)
// 	{
// 		printf("%d\n", *(int *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	tmp = m;
// 	printf("Mapped  : ");
// 	/* 5 6 7 8 */ for (int i = 0; i < 4; ++i)
// 	{
// 		printf("%d\n", *(int *)tmp->content);
// 		tmp = tmp->next;
// 	}
// 	printf("\n");
// 	return (0);
// }
