/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export env struct.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 20:40:30 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/24 11:44:49 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "../include/minishell.h"
#include <stdlib.h>
#include <stdbool.h>

t_data	g_data;

typedef struct s_data
{
	char			**env;
	t_env_list		*env_list;
}   t_data;

typedef struct s_env_list
{
    char                *name;
    char                *value;
    bool                env_and_export;
    struct t_env_list  *next;
}       t_env_list;


void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (dst == NULL && src == NULL)
		return (NULL);
	while (i < n)
	{
		((char *)dst)[i] = ((char *)src)[i];
		i++;
	}
	return (dst);
}

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

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		s++;
		len++;
	}
	return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		j;
	char	*subs;

	j = 0;
	subs = malloc(sizeof(char) * (len + 1));
	if (subs != NULL)
	{
		while ((j < (int)len) && (start < ft_strlen(s)))
		{
			subs[j] = s[start];
			start++;
			j++;
		}
		subs[j] = '\0';
	}
	return (subs);
}

void init_env(char **envp)
{
    char 		**split;
    char        *tmp;
	t_env_list 	*tmp_env;

	g_data.env_list = malloc(sizeof(t_env_list));
	if (!g_data.env_list)
		return(4);
	tmp_env = g_data.env_list;
	while(*envp)
	{
		split = ft_split(*envp, '=');
        tmp_env->name = split[0];
		tmp_env->value = split[1];
		tmp_env->next = malloc(sizeof(t_env_list));
		if (!tmp_env->next)
			return (4);
		if (*(envp + 1) == NULL)
			tmp_env->next = NULL;
		else
			tmp_env = tmp_env->next;
		envp++;
	}
	return (0);
}

void    print_env_or_export(int argc, char **argv)
{
    t_env_list  *tmp_env;

    tmp_env = g_data.env_list;
    if (argc == 2 && argv[1] == "env")
    {
        while (tmp_env != NULL)
        {
            printf("%s=%s", tmp_env->name, tmp_env->value);
            tmp_env = tmp_env->next;
        }
    }
    else if (argc == 2 && argv[1] == "export")
    {
        order_env();
        while (tmp_env != NULL)
        {
            printf("declare -x %s=\"%s\"", tmp_env->name, tmp_env->value);
            tmp_env = tmp_env->next;
        }
    }
}

void	ft_lstadd_back(t_env_list **lst, t_env_list *new)
{
	t_env_list	*list;

	if (*lst)
	{
		list = *lst;
		while (list->next)
		{
			list = list->next;
		}
		list->next = new;
	}
	else
		*lst = new;
}



int main(int argc, char **argv, char **envp)
{
    init_env(envp);
    while (1)
    {
        printf_env_or_export(argc, argv);
        
    }
    // if (argc == 2 && argv[1] == "env")
    //     print_env();
    // if (argc == 2 && argv[1] == "export")
    //     print_export();
    if (argc == 3 && argv[1] == "export")
        add_everything_to_env_list();
    
    return (0);
}

Ok, I will make that the arguments of export are getting added to env and export.

And get env with env put it into a structure and update the structure.
