/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:37:37 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/20 09:48:50 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*sj;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	sj = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (sj == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		sj[i] = s1[i];
		i++;
	}
	while (s2[x] != '\0')
	{
		sj[i] = s2[x];
		i++;
		x++;
	}
	sj[i] = '\0';
	return (sj);
}
