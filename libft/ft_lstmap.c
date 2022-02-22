/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 12:45:17 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/03 12:52:11 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new;
	t_list	*temp1;
	t_list	*temp2;

	if (!lst)
		return (NULL);
	temp2 = malloc(sizeof(*lst));
	if (!temp2)
		return (NULL);
	temp2->content = f(lst->content);
	if (!temp2)
		ft_lstclear(&temp2, del);
	new = temp2;
	temp1 = lst;
	while (temp1->next)
	{
		temp1 = temp1->next;
		temp2->next = malloc(sizeof(*temp1));
		temp2->next->content = f(temp1->content);
		temp2 = temp2->next;
	}
	temp2->next = NULL;
	return (new);
}
