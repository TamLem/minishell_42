/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:19:35 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/02 17:19:37 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	get_start(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i])
		i++;
	return (i);
}

int	get_end(char const *s1, char const *set)
{
	int	len;

	len = ft_strlen(s1);
	while (ft_strchr(set, s1[len - 1]) && s1[len - 1])
		len--;
	return (len);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		i;
	int		start;
	int		len;
	char	*cpy;

	if (!s1)
		return (NULL);
	i = 0;
	start = get_start(s1, set);
	len = ft_strlen(s1);
	if (start != len)
		len = get_end(s1, set);
	cpy = malloc(sizeof(char) * ((len - start) + 1));
	if (!cpy)
		return (NULL);
	if (start == len)
		return ("");
	while (start < len)
	{
		cpy[i] = s1[start];
		start++;
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

/* line 53, malloc not used might fail */