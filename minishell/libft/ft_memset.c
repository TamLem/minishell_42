/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:20:05 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/17 21:42:26 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ufc;
	unsigned char	uc;

	uc = c;
	ufc = s;
	while (n--)
	{
		*ufc = uc;
		ufc++;
	}
	return (s);
}
