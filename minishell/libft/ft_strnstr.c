/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:20:32 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/20 09:31:19 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *h, const char *n, size_t len)
{
	size_t	i;
	size_t	x;

	i = 0;
	if (n == NULL && h == NULL)
		return (NULL);
	if (ft_strlen(n) == 0)
		return ((char *)h);
	while (i < len && h[i] != '\0')
	{
		x = 0;
		while (n[x] == h[i + x] && i + x < len)
		{
			if (n[x + 1] == '\0')
				return ((char *)(h + i));
			x++;
		}	
		i++;
	}
	return (0);
}
