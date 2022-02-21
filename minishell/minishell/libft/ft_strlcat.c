/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:20:16 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/29 16:09:12 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	size_t	dstlen;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	dstlen = ft_strlen(dest);
	if (size == 0)
		return (ft_strlen(src));
	while (i < size && i < dstlen)
		i++;
	if (i >= size)
		return (ft_strlen(src) + i);
	while (n < size - dstlen - 1 && src[n] != '\0')
	{
		dest[i + n] = src[n];
		n++;
	}
	dest[i + n] = '\0';
	return (i + ft_strlen(src));
}
