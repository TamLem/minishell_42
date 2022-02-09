/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:19:44 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/17 19:39:48 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*sa;
	unsigned char	*sb;
	int				result;
	size_t			i;

	sa = (unsigned char *)s1;
	sb = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		result = sa[i] - sb[i];
		if (result != 0)
			return (result);
		i++;
	}
	return (0);
}
