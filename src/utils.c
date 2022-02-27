/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/03 17:53:52 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/27 20:03:15 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_mem_alloc
{
	long	address;
	struct 	s_mem_alloc *next;
}				t_mem_alloc;

void	free_dp(char **i)
{
	while (*i)
	{
		free(*i);
		i++;
	}
}

char	*ft_append_char(char *s1, char c)
{
	size_t	i;
	size_t	len;
	char	*ret;

	if (c == '\0')
		return (s1);
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

void	*ft_malloc(size_t size)
{
	void	*ret;

	ret = NULL;
	if (g_data.malloc_count == 0)
		g_data.mem_alloced = malloc(sizeof(void *) * 100);
	if (g_data.malloc_count % 100 == 0 && g_data.malloc_count != 0)
	{
		g_data.mem_alloced = 
			ft_realloc_more(g_data.mem_alloced, sizeof(void *) * g_data.malloc_count, 
				sizeof(void *) * (g_data.malloc_count + 100)) ;
	}
	if (g_data.mem_alloced == NULL)
		return (NULL);
	ret = malloc(size);
	if (ret == NULL)
		return (NULL);
	else
	{
		((void **)g_data.mem_alloced)[g_data.malloc_count] = ret;
		g_data.malloc_count++;
	}
	dprintf(2, "mem alloced %d\n", g_data.malloc_count);
	return (ret);
}

void mem_free_all()
{
	int	i;

	i = 0;
	while (i <= g_data.malloc_count)
	{
		free(((void **)g_data.mem_alloced)[i]);
		i++;
	}
	free(g_data.mem_alloced);
}