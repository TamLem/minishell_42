/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/22 14:37:28 by nlenoch           #+#    #+#             */
/*   Updated: 2021/08/11 13:44:27 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	wcount(const char *s, char c)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	if (s[i] == 0)
		return (0);
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i] != c && s[i] != '\0')
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	 return (count);
}

char	**wlen(const char *s, int wc, char c, char **s1)
{
	int	head;
	int	tail;
	int	i;

	tail = 0;
	head = 0;
	i = 0;
	while (i < wc)
	{
		while (s[head] == c && s[head])
			head++;
		tail = head;
		while (s[tail] && s[tail] != c)
			tail++;
		if (s[head] == '\0')
			break ;
		s1[i] = (char *)malloc(sizeof(char) * (tail - head + 1));
		ft_memcpy (s1[i], &((char *)s)[head], (tail - head));
		s1[i][tail - head] = '\0';
		i++;
		head = tail;
	}
	s1[i] = NULL;
	return (s1);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		wc;

	if (s == 0)
		return (NULL);
	wc = wcount(s, c);
	arr = (char **)malloc((wc + 1) * sizeof(char *));
	if (arr == NULL)
		return (NULL);
	return (wlen(s, wc, c, arr));
}
