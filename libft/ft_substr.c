/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:13:12 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/08 14:19:05 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		j;
	char	*subs;

	j = 0;
	subs = ft_malloc(sizeof(char) * (len + 1));
	if (subs != NULL)
	{
		while ((j < (int)len) && (start < ft_strlen(s)))
		{
			subs[j] = s[start];
			start++;
			j++;
		}
		subs[j] = '\0';
	}
	return (subs);
}
