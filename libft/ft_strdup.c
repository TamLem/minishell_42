/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:25:13 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/02 14:38:41 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*p;

	p = NULL;
	len = ft_strlen(s);
	p = malloc(len * sizeof(char) + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s, (len + 1));
	return (p);
}
