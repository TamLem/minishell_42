/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:32:47 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/26 18:43:35 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"
#include "minishell.h"

void	order_env(char ***env)
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

void    print_env_or_export(char *cmd, char **env_arr)
{
    t_env_list  *tmp_env;

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

t_env_list *ft_getenv_list(char *name)
{
	t_env_list *tmp_env;

	tmp_env = g_data.env_list;
	while (tmp_env != NULL)
	{
		if ((ft_strcmp(name, tmp_env->name)) == 0)
			return (tmp_env);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

char	*ft_getenv_value(char *name)
{
	t_env_list *tmp_env;

	tmp_env = ft_getenv_list(name);
	if (tmp_env)
		return (tmp_env->value);
	return (NULL);
}

int	ft_env(int argc, char *argv[], char *envp[])
{
	if (argc == 1)
	{
		print_env_or_export("env", NULL);
		return (0);
	}
	return (1);
}

void	print_export(char **exports)
{

}

int	add_env(char *name, char *value)
{
	t_env_list 	*new;
	t_env_list	*existing;

	existing = ft_getenv_list(name);
	if (existing && value)
	{
		free(existing->value);
		existing->value = value;
		existing->is_env = true;
	}
	else if (!existing)
	{
		new = g_data.env_list;
		while (new && new->next)
			new = new->next;
		new->next = malloc(sizeof(t_env_list));
		if (new->next == NULL) 
			return (4);
		new = new->next;
		new->name = name;
		new->value = value;
		if (value)
			new->is_env = true;
		else
			new->is_env = false;
		new->next = NULL;
	}
	return (0);
}

/* Check for invalid chars in assignment */
int	update_env(int argc, char *argv[], char *envp[])
{
	char		*assign;
	char		*name;
	char		*value;

	argv++;
	value = NULL;
	while (*argv && **argv)
	{
		if (**argv)
		{
			assign = ft_strchr(*argv, '=');
			if (assign)
			{
				name = ft_substr(*argv, 0, assign - *argv);
				value = ft_substr(*argv, ft_strlen(*argv) - ft_strlen(assign) + 1, ft_strlen(assign + 1));
			}
			else
				name = *argv;
			add_env(name, value);
		}
		argv++;
	}
	return (0);
}

char **env_to_arr()
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
	env_arr = malloc(sizeof(char *) * (len + 1));
	env_arr[len] = NULL;
	while (i < len)
	{
		if (env_lst->value)
		{
			env_arr[i] = ft_strjoin(env_lst->name, "=\"");
			temp = env_arr[i];
			env_arr[i] = ft_strjoin(temp, env_lst->value);
			env_arr[i] = ft_append_char(env_arr[i], '"');
			free(temp);
		}	
		else
			env_arr[i] = ft_strdup(env_lst->name);
		env_lst = env_lst->next;
		i++;
	}
	return (env_arr);
}

int	ft_export(int argc, char *argv[], char *envp[])
{
	char	**env_arr;

	if (argc > 1)
		return (update_env(argc, argv, envp));
	else
	{
		env_arr = env_to_arr();
		print_env_or_export("export", env_arr);
	}
	return (0);
}
