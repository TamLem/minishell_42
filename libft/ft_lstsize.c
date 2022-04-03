/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:10:45 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/02 20:18:40 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int		size;
	t_list	*list;

	if (!lst)
		return (0);
	size = 1;
	list = lst;
	while (list->next)
	{
		list = list->next;
		size++;
	}
	return (size);
}
