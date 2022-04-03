/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:52:57 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/02 20:18:25 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstclear(t_list	**lst, void (*del)(void *))
{
	if ((*lst)->next)
		ft_lstclear((&((*lst)->next)), del);
	(*del)((*lst)->content);
	free(*lst);
	*lst = NULL;
}

/* *lst - lst is  pointer to the list 								*/
/* **lst - lst is an address of the pointer (pointer to the list) 	*/