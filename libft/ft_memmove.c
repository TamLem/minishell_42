/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:16:07 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/02 18:46:28 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	int	i;

	i = 0;
	if ((src == NULL && dest == NULL) || dest == src)
		return (dest);
	if (dest > src)
	{
		i = n - 1;
		while (i >= 0)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i--;
		}
		return (dest);
	}
	if (dest < src)
	{
		while (i < (int)n)
		{
			((char *)dest)[i] = ((char *)src)[i];
			i++;
		}
		return (dest);
	}
	return (dest);
}
