/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_more.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:28:47 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/27 19:11:00 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc_more(void *ptr, size_t init_size, size_t size)
{
    void *new;

	new = NULL;
    if (!ptr)
	{
        new = malloc(size);
		if (!new)
			return (NULL); 
	}
    else 
	{
		if (init_size < size) 
		{
			new = malloc(size);
			if (!new)
				return (NULL);
			ft_memcpy(new, ptr, init_size);
			free(ptr);
		}
		else 
            new = ptr;
    }
	return new;
}
