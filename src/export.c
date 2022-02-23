/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:32:47 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/23 18:38:09 by tlemma           ###   ########.fr       */
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

void	print_env_lst()
{
	t_env_list	*env_new;

	env_new	= g_data.env_list;
	while (env_new != NULL)
	{
		printf("%s=\"%s\"\n", env_new->name, env_new->value);
		env_new = env_new->next;
	}
}

int	ft_export(int argc, char *argv[], char *envp[])
{
	int			i;
	int			len;
	char		**env_arr;
	t_env_list	*env_lst;

	env_lst	= g_data.env_list;
	len = 0;
	i = 0;
	// if (argc == 1)
	// {
	// 	print_env();
	// 	return (0);
	// }
	while(env_lst && ++len)
		env_lst = env_lst->next;
	env_lst = g_data.env_list;
	env_arr = malloc(sizeof(char *) * (len + 1));
	env_arr[len] = NULL;
	while(i < len)
	{
		char	*temp;
		temp = ft_strjoin(env_lst->name, "=");
		env_arr[i] = ft_strjoin(temp, env_lst->value);
		free(temp);
		env_lst = env_lst->next;
		i++;
	}
	order_env(env_arr);
	while (*env_arr)
	{
		printf("declare -x %s\n", *env_arr);
		env_arr++;
	}
	free_dp(env_arr);
	return (0);
}
