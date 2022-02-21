/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/25 11:40:03 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/26 13:32:10 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*tmp;
	t_list	*new;

	tmp = *lst;
	if (!lst || !del)
		return ;
	while (tmp)
	{
		new = tmp->next;
		del(tmp->content);
		free (tmp);
		tmp = new;
	}
	*lst = NULL;
}
