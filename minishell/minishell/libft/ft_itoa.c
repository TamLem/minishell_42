/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:36:10 by nlenoch           #+#    #+#             */
/*   Updated: 2021/07/22 13:13:32 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	minus(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

int	num(int n)
{
	int	numlen;

	numlen = 0;
	while (n != 0)
	{
		n = n / 10;
		numlen++;
	}
	return (numlen);
}

int	rnum(int n)
{
	while (n != 0)
	{
		n = n % 10;
		if (n < 0)
			n = n * -1;
		return (n);
	}
	return (n);
}

char	*ft_itoa(int n)
{
	char	*a;
	int		len;
	long	ln;

	ln = n;
	len = 0;
	if (minus(ln) == 1 || n == 0)
		len = 1;
	if (n == 0)
		return (ft_strdup("0"));
	len += num(ln);
	a = malloc(len + 1);
	if (a == NULL)
		return (NULL);
	a[len] = '\0';
	while (n != 0)
	{
		a[len - 1] = (rnum(n) + '0');
		n = n / 10;
		len--;
	}
	if (minus(ln) == 1)
		a[len - 1] = '-';
	return (a);
}
