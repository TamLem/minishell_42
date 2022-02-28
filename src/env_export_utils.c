/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_export_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 17:48:19 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/28 20:42:06 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	init_env(int argc, char **argv, char **envp)
{	
	char		**split;
	t_env_list	*tmp_env;

	g_data.env_list = ft_malloc(sizeof(t_env_list));
	if (!g_data.env_list)
		return (4);
	tmp_env = g_data.env_list;
	while (*envp)
	{
		split = ft_split(*envp, '=');
		tmp_env->name = split[0];
		tmp_env->value = split[1];
		tmp_env->is_env = true;
		tmp_env->next = ft_malloc(sizeof(t_env_list));
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

static void	order_env(char ***env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while ((*env)[i])
	{
		j = 0;
		while ((*env)[j])
		{
			if (ft_strcmp((*env)[i], (*env)[j]) < 0)
			{
				tmp = (*env)[i];
				(*env)[i] = (*env)[j];
				(*env)[j] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	print_env_or_export(char *cmd, char **env_arr)
{
    t_env_list	*tmp_env;

    tmp_env = g_data.env_list;
    if (ft_strcmp(cmd, "env") == 0)
    {
        while (tmp_env != NULL)
        {
			if (tmp_env->is_env)
            	dprintf(2, "%s=%s\n", tmp_env->name, tmp_env->value);
            tmp_env = tmp_env->next;
        }
    }
    else
    {
        order_env(&env_arr);
		while (*env_arr)
		{
			dprintf(2, "declare -x %s\n", *env_arr);
			env_arr++;
		}
		free_dp(env_arr);
    }
}

t_env_list	*ft_getenv_list(char *name)
{
	t_env_list	*tmp_env;

	tmp_env = g_data.env_list;
	while (tmp_env != NULL)
	{
		if ((ft_strcmp(name, tmp_env->name)) == 0)
			return (tmp_env);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char **env_to_arr(void)
{
	int			i;
	int			len;
	char		**env_arr;
	t_env_list	*env_lst;
	char		*temp;

	len = 0;
	i = 0;
	env_lst	= g_data.env_list;
	while (env_lst)
	{
		len++;
		env_lst = env_lst->next;
	}
	env_lst = g_data.env_list;
	env_arr = ft_malloc(sizeof(char *) * (len + 1));
	env_arr[len] = NULL;
	while (i < len)
	{
		if (env_lst->value)
		{
			env_arr[i] = ft_strjoin(env_lst->name, "=");
			temp = env_arr[i];
			env_arr[i] = ft_strjoin(temp, env_lst->value);
			// env_arr[i] = ft_append_char(env_arr[i], '"');
		}	
		else
			env_arr[i] = ft_strdup(env_lst->name);
		env_lst = env_lst->next;
		i++;
	}
	return (env_arr);
}