/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:19:28 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/02 17:19:30 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int		i;
	int		len;
	char	*p;

	p = NULL;
	i = 0;
	len = ft_strlen(s);
	while (i <= len)
	{
		if (s[i] == c)
			p = (char *)&(s[i]);
		i++;
	}
	return (p);
}
