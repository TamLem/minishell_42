/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 12:35:32 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/10 15:54:27 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s, int n)
{
	char	*p;
	int		len;

	p = NULL;
	len = ft_strlen(s);
	if (n < len)
		len = n;
	p = malloc(len * sizeof(char) + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s, (len + 1));
	return (p);
}
