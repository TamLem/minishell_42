/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:32:47 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/28 18:01:33 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"
#include "env.h"
#include "minishell.h"

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
		new->next = ft_malloc(sizeof(t_env_list));
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

static int	update_env(int argc, char *argv[], char *envp[])
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
			if (!is_valid_name(name))
				err_handle(2, name);
			else
				add_env(name, value);
		}
		argv++;
	}
	return (0);
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
