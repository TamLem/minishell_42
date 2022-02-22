/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/02 17:18:37 by tlemma            #+#    #+#             */
/*   Updated: 2021/11/02 16:12:30 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	*substrlen(const char *s, char c, int n)
{
	int	i;
	int	*len;

	i = 0;
	len = malloc(sizeof(int) * n);
	if (!len)
		return (NULL);
	while (i < n)
		len[i++] = 0;
	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			len[i]++;
		}
		if (*s != c && *(s + 1) == c)
		{
			i++;
		}
		s++;
	}
	return (len);
}

static int	get_n(const char *s, char c)
{
	int	i;
	int	n;

	i = 0;
	n = 0;
	while (s[i])
	{
		if (s[i] != c && (s[i + 1] == c || s[i + 1] == '\0'))
			n++;
		i++;
	}
	return (n);
}

static char	**fill_substrs(const char *s, char c, int *len, char **substrs)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (*s)
	{
		if (*s != c)
		{
			substrs[i] = malloc(sizeof(char) * len[i] + 1);
			if (!substrs[i])
				return (NULL);
			while (j < len[i])
				substrs[i][j++] = *s++;
			substrs[i][j] = '\0';
			j = 0;
			i++;
			continue ;
		}
		s++;
	}
	return (substrs);
}

char	**ft_split(const char *s, char c)
{
	int		n;
	int		*len;
	char	**substrs;

	if (s == NULL)
		return (NULL);
	n = get_n(s, c);
	len = substrlen(s, c, n);
	substrs = malloc(sizeof(char *) * (n + 1));
	if (!substrs)
		return (NULL);
	substrs[n] = NULL;
	fill_substrs(s, c, len, substrs);
	free(len);
	return (substrs);
}
