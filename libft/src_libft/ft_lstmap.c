/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jnenczak <jnenczak@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:45:40 by jnenczak          #+#    #+#             */
/*   Updated: 2024/02/03 15:45:40 by jnenczak         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static t_list	*ft_lstnew_map(void *content)
{
	t_list	*ret;

	ret = (t_list *)malloc(sizeof(t_list));
	if (ret == NULL)
		return (NULL);
	ret->content = content;
	ret->next = NULL;
	return (ret);
}

static void	ft_lstclear_map(t_list **lst, void (*del)(void *))
{
	t_list	*current;
	t_list	*temp;

	if (lst == NULL || del == NULL || (*lst) == NULL)
		return ;
	current = *lst;
	while (current->next)
	{
		temp = current;
		current = current->next;
		del(temp->content);
		free(temp);
	}
	del(current->content);
	free(current);
	*lst = NULL;
}

static void	ft_lstadd_back_map(t_list **lst, t_list *new_elem)
{
	t_list	*temp;

	if (lst == NULL || new_elem == NULL)
		return ;
	if (*lst == NULL)
	{
		*lst = new_elem;
		return ;
	}
	temp = *lst;
	while (temp->next)
		temp = temp->next;
	temp->next = new_elem;
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_list;
	t_list	*new_elem;

	if (!lst || !f || !del)
		return (NULL);
	new_list = NULL;
	while (lst)
	{
		new_elem = ft_lstnew_map((*f)(lst->content));
		if (new_elem == NULL)
		{
			ft_lstclear_map(&new_list, del);
			return (NULL);
		}
		ft_lstadd_back_map(&new_list, new_elem);
		lst = lst->next;
	}
	return (new_list);
}
