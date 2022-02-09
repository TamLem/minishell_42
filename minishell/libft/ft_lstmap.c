/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 11:40:15 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/28 18:57:26 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*part;

	new = NULL;
	while (lst != NULL)
	{
		part = ft_lstnew((*f)(lst->content));
		if (part == NULL)
		{
			ft_lstclear(&new, (*del));
			return (NULL);
		}
		ft_lstadd_back(&new, part);
		lst = lst->next;
	}
	return (new);
}
