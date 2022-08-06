/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:15:24 by tlemma            #+#    #+#             */
/*   Updated: 2021/12/23 01:35:53 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	isvalidstr(const char *s)
{
	int	i;
	int	foundnum;

	i = 0;
	foundnum = 0;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			foundnum = 1;
		if (!(s[i] == ' ' || s[i] == '\n' || s[i] == '\t'
				|| s[i] == '\v' || s[i] == '\f' || s[i] == '\r'
				|| s[i] == '+' || s[i] == '-'))
			if (!foundnum)
				return (0);
		if ((s[i] == '+' || s[i] == '-') && !ft_isdigit(s[i + 1]))
			return (0);
		i++;
	}
	return (1);
}

long	ft_atoi(const char *str)
{
	int				i;
	long			num;
	long			sign;
	unsigned int	digit;

	i = 0;
	num = 0;
	sign = -1;
	if (!isvalidstr(str))
		return (0);
	while (str[i] != '\0')
	{
		if (!ft_isdigit(str[i]) && num)
			break ;
		if (ft_isdigit(str[i]))
		{
			digit = (str[i] - 48);
			num = 10 * num - digit;
		}
		if (str[i] == '-')
			sign = 1;
		i++;
	}
	return (sign * num);
}
