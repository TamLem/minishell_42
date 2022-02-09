/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/17 10:20:36 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/17 20:13:02 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	ch;
	int		i;
	char	*x;

	ch = (char)c;
	i = 0;
	x = 0;
	while (s[i] != '\0')
	{
		if (s[i] == ch)
			x = (char *)&s[i];
		s++;
	}
	if (s[i] == ch)
		x = (char *)&s[i];
	return (x);
}
