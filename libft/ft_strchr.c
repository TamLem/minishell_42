/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/19 16:02:13 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/02 16:10:23 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;
	int	len;

	if (s == NULL)
		return (NULL);
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return ((char *)&(s[i]));
		i++;
	}
	return (NULL);
}

int	ft_strchr_pos(const char *s, int c)
{
	int	i;
	int	len;

	if (s == NULL)
		return (-1);
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			return (i);
		i++;
	}
	return (-1);
}
