/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:32:47 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/24 12:25:19 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	order_env(char **env)
{
	char	*tmp;
	int		i;
	int		j;

	i = 0;
	while (env[i])
	{
		j = 0;
		while (env[j])
		{
			if (ft_strcmp(env[i], env[j]) < 0)
			{
				tmp = env[i];
				env[i] = env[j];
				env[j] = tmp;
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
    if (ft_strcmp(cmd, "env"))
    {
        while (tmp_env != NULL)
        {
			if (tmp_env->is_env)
            	printf("%s=%s", tmp_env->name, tmp_env->value);
            tmp_env = tmp_env->next;
        }
    }
    else
    {
        order_env(env_arr);
		while (*env_arr)
		{
			printf("declare -x %s\n", *env_arr);
			env_arr++;
		}
		free_dp(env_arr);
    }
}

int	env(int argc, char *argv[], char *envp[])
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

int	add_env_args(int argc, char *argv[], char *envp[])
{
    t_env_list  *tmp_env;
    int			i;
	char		*assign;

    i = 0;
    tmp_env = g_data.env_list;
	while(tmp_env && tmp_env->next)
		tmp_env = tmp_env->next;
	while (*argv)
	{
		assign = ft_strchr(*argv, '=');
		if (**argv)
		{
   	 		tmp_env->next = malloc(sizeof(t_env_list));
			tmp_env = tmp_env->next;
			if (assign)
			{
				tmp_env->name = ft_substr(*argv, 0, assign - *argv - 1);
				tmp_env->value = ft_substr(*argv, assign + 1, ft_strlen(assign + 1));
				tmp_env->is_env = true;
			}
			else
			{
				tmp_env->name = ft_strdup(*envp);
				tmp_env->is_env = false;
			}
			tmp_env->next = NULL;
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

	env_lst	= g_data.env_list;
	len = 0;
	i = 0;
	while (env_lst)
	{
		if (env_lst->is_env)
			len++;
		env_lst = env_lst->next;
	}
	env_lst = g_data.env_list;
	env_arr = malloc(sizeof(char *) * (len + 1));
	env_arr[len] = NULL;
	while (i < len)
	{
		if (env_lst->is_env)
		{
			temp = ft_strjoin(env_lst->name, "=\"");
			env_arr[i] = ft_strjoin(temp, env_lst->value);
			env_arr[i] = ft_append_char(env_arr[i], '"');
			free(temp);
			i++;
		}
		env_lst = env_lst->next;
	}
	return (env_arr);
}

int	ft_export(int argc, char *argv[], char *envp[])
{
	char	**env_arr;

	if (argc > 1)
		return (add_env_args(argc, argv, envp));
	env_arr = env_to_arr();
	print_env_or_export("export", env_arr);
	return (0);
}
