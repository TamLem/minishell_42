/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:38:31 by nlenoch           #+#    #+#             */
/*   Updated: 2021/09/23 13:52:32 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	index;
	size_t	extract;
	char	*substr;

	index = 0;
	while (index < start)
	{
		if (s[index] == '\0')
			return (ft_strdup(""));
		index++;
	}
	extract = ft_strlen(s + index);
	if (len < extract)
		extract = len;
	substr = malloc(sizeof(char) * (extract + 1));
	i = 0;
	while (i < extract)
	{
		substr[i] = s[index + i];
		i++;
	}
	substr[i] = '\0';
	return (substr);
}

/*
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	mallen;

	sub = 0;
	i = 0;
	mallen = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (ft_calloc(1, 1));
	if (len - start > ft_strlen(s))
		while (s[mallen] != '\0' && mallen < len - start)
			mallen++;
	else
		mallen = len;
	sub = (char *)ft_calloc(mallen + 1, sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		sub[i] = s[i + start];
		i++;
	}
	return (sub);
}
*/

/* 
	char	*sub;
	size_t	i;

	sub = 0;
	i = 0;
	if (s == NULL)
		return (NULL);
	if (start > ft_strlen(s))
		return (NULL);
	sub = (char *)malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		sub[i] = s[i + start];
		i++;
	}
	sub[i] = '\0';
	return (sub);
*/