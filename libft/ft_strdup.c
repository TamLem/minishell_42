/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/23 15:25:13 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/09 18:43:54 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "../include/minishell.h"

char	*ft_strdup(const char *s)
{
	int		len;
	char	*p;

	if (s == NULL)
		return (NULL);
	p = NULL;
	len = ft_strlen(s);
	p = ft_malloc(len * sizeof(char) + 1);
	if (!p)
		return (NULL);
	ft_strlcpy(p, s, (len + 1));
	return (p);
}
