/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zfeng <zfeng@student.42.us.org>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/07 00:27:14 by zfeng             #+#    #+#             */
/*   Updated: 2018/03/07 11:25:20 by zfeng            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*head;
	t_list	*tmp;

	if (!lst)
		return (NULL);
	tmp = (*f)(lst);
	new = ft_lstnew(tmp->content, tmp->content_size);
	head = new;
	while (lst->next)
	{
		lst = lst->next;
		tmp = (*f)(lst);
		new->next = ft_lstnew(tmp->content, tmp->content_size);
		new = new->next;
	}
	return (head);
}
