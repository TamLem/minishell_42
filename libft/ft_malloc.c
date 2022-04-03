/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 11:28:12 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/08 16:20:51 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>
#include <errno.h>

void	*ft_malloc(size_t size)
{
	void		*ret;
	static int	i = 0;
	static void	*mem_alloced;

	ret = NULL;
	if (i == 0)
		mem_alloced = malloc(sizeof(void *) * 100);
	if (i % 100 == 0 && i != 0)
	{
		mem_alloced
			= ft_realloc_more(mem_alloced, sizeof(void *) * i,
				sizeof(void *) * (i + 100));
	}
	if (mem_alloced == NULL)
		return (NULL);
	ret = malloc(size);
	if (ret == NULL)
		return (NULL);
	else
	{
		((void **)mem_alloced)[i] = ret;
		i++;
	}
	return (ret);
}
