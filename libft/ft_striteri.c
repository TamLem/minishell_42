/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/31 19:11:27 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/01 15:19:25 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	int		len;
	int		i;

	i = 0;
	if (s && f)
	{
		len = ft_strlen(s);
		while (s[i])
		{
			(*f)(i, &s[i]);
			i++;
		}
	}
}
