/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:20:28 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/27 21:48:31 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*uc1;
	unsigned char	*uc2;
	size_t			i;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	i = 0;
	if ((ft_strlen(s1) == 0 && ft_strlen(s2) == 0) || n == 0)
		return (0);
	if (ft_strlen(s1) == 0)
		return (-1);
	if (ft_strlen(s2) == 0)
		return (1);
	while ((i <= n && uc1[i] != '\0') || uc2[i] != '\0')
	{
		if ((uc1[i] == uc2[i] && i == n) || i == n)
			return (0);
		if (uc1[i] > uc2[i])
			return (1);
		if (uc1[i] < uc2[i])
			return (-1);
		i++;
	}
	return (0);
}
