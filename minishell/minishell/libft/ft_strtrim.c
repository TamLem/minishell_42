/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:38:26 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/20 12:50:51 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		j;

	i = 0;
	if (s1 == NULL || set == NULL)
		return (NULL);
	while (s1[i] != '\0' && ft_strchr(set, s1[i]))
	{
		i++;
		if (!ft_strchr(set, s1[i]))
			break ;
	}
	if (!s1[i])
		return (ft_strdup(""));
	j = ft_strlen(s1);
	while (j != 0 && ft_strchr(set, s1[j]))
	{
		j--;
		if (!ft_strchr(set, s1[j]))
			break ;
	}
	return (ft_substr(s1, i, j - i + 1));
}
