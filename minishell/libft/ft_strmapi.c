/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:38:08 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/17 20:07:45 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	int		i;
	char	*n;

	i = 0;
	if (s == NULL || f == NULL)
		return (NULL);
	n = malloc(ft_strlen(s) * sizeof(char) + 1);
	if (!n)
		return (NULL);
	while (s[i] != '\0')
	{
		n[i] = (f)(i, (s[i]));
		i++;
	}
	n[i] = '\0';
	return (n);
}
