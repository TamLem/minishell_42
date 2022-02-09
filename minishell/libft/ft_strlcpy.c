/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:20:21 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/23 15:59:58 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst)
		return (0);
	if (n == 0)
		return (ft_strlen(src));
	while (0 < n - 1 && src[i])
	{
		dst[i] = src[i];
		i++;
		n--;
	}
	dst[i] = 0;
	return (ft_strlen(src));
}
