/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/01 20:01:28 by tlemma            #+#    #+#             */
/*   Updated: 2021/09/02 16:16:38 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_pow(int nb, int power)
{
	int	i;
	int	result;

	i = 0;
	result = 1;
	if (power < 0)
		return (0);
	while (i < power)
	{
		result *= nb;
		i++;
	}
	return (result);
}

char	*get_min(char *s)
{
	char	*intmin;

	intmin = "-2147483648";
	s = malloc(sizeof(char) * 12);
	if (s)
		while (*intmin)
			*s++ = *intmin++;
	*s = '\0';
	return (s);
}

char	*getstr(long num, int len, int nstart)
{
	char	*s;
	int		n;

	n = 0;
	s = malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	s[len] = '\0';
	n = len - 1;
	while (n >= nstart)
	{
		s[n] = (num % 10 + 48);
		num /= 10;
		n--;
	}
	if (nstart)
		s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	long	num;
	int		len;
	int		nstart;

	len = 1;
	num = (long) n;
	n /= 10;
	while (n)
	{
		n /= 10;
		len++;
	}
	nstart = 0;
	if (num < 0)
	{
		nstart++;
		num *= -1;
		len++;
	}
	return (getstr(num, len, nstart));
}
