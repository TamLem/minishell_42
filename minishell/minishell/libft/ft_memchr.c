/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:19:40 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/17 19:37:48 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	uc;
	unsigned char	*ufc;
	size_t			i;

	uc = (unsigned char)c;
	ufc = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (uc == ufc[i])
		{
			return ((unsigned char *)s + i);
		}
		i++;
	}
	return (0);
}
