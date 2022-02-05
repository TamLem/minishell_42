/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:53:52 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/03 18:28:25 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*ft_append_char(char *s1, char c)
{
	size_t	i;
	size_t	len;
	char	*ret;

	if (c == '\0')
		return (NULL);
	i = 0;
	ret = NULL;
	if (s1 != NULL)
		len = ft_strlen(s1);
	else
		len = 0;
	ret = malloc(sizeof(char) * (int)len + 2);
	if (!ret)
		return (NULL);
	while (i < len)
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = c;
	ret[i + 1] = '\0';
	free(s1);
	return (ret);
}
