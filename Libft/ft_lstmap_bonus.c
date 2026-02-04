/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzouhir <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 13:12:39 by mzouhir           #+#    #+#             */
/*   Updated: 2025/11/13 14:26:36 by mzouhir          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*tmp;
	void	*newcontent;

	if (!lst || !f || !del)
		return (NULL);
	new = NULL;
	while (lst)
	{
		newcontent = f(lst->content);
		tmp = ft_lstnew(newcontent);
		if (!tmp)
		{
			if (newcontent)
				del(newcontent);
			ft_lstclear(&new, del);
			new = NULL;
			break ;
		}
		ft_lstadd_back(&new, tmp);
		lst = lst->next;
	}
	return (new);
}
