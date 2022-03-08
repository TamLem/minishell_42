/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:46:04 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/08 16:17:15 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

int	init_args(t_simple_cmd *simple_cmd, char ***p_arg_array)
{
	int		i;
	int		len;
	t_args	*args;
	char	**arg_array;

	i = 0;
	len = 0;
	args = simple_cmd->args;
	while (args && ++len)
		args = args->next;
	*p_arg_array = ft_malloc(sizeof(char *) * (len + 1));
	if (*p_arg_array == NULL)
		return (4);
	arg_array = *p_arg_array;
	arg_array[len] = NULL;
	args = simple_cmd->args;
	while (i < len)
	{
		arg_array[i] = args->value;
		args = args->next;
		i++;
	}
	return (len);
}

char	**ft_getpath(char *cmd)
{
	int		i;
	char	*keypair;
	char	**path;

	i = 0;
	keypair = NULL;
	path = ft_split(ft_getenv("PATH"), ':');
	i = 0;
	if (path == NULL)
	{
		path = malloc(sizeof(char *) * 2);
		path[0] = cmd;
		path[1] = NULL;
	}
	else
	{
		while (path && path[i])
		{
			path[i] = ft_strjoin(path[i], "/");
			path[i] = ft_strjoin(path[i], cmd);
			i++;
		}
	}
	return (path);
}

bool	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export")
		|| !ft_strcmp(cmd, "exit"))
		return (true);
	return (false);
}

bool	check_cmds(char	*cmd)
{
	int		i;
	bool	res;
	char	**path;

	i = 0;
	res = false;
	path = ft_getpath(cmd);
	while (path && path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
			res = true;
		i++;
	}
	if (is_builtin(cmd))
		res = false;
	if (path != NULL)
		free_dp(path);
	return (res);
}
