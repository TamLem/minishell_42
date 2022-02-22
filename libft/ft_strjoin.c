/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 16:03:20 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/03 16:39:52 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	len;
	char	*ret;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	i = 0;
	ret = NULL;
	len = ft_strlen(s1) + ft_strlen(s2);
	ret = malloc(sizeof(char) * (int)len + 1);
	if (!ret)
		return (NULL);
	while (i < ft_strlen(s1))
	{
		ret[i] = s1[i];
		i++;
	}
	i = 0;
	while ((i + ft_strlen(s1)) < len && ft_strlen(s2))
	{
		ret[i + (int)ft_strlen(s1)] = s2[i];
		i++;
	}
	ret[len] = '\0';
	return (ret);
}
