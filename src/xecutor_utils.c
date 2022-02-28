/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 19:46:04 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/28 18:57:54 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "xecutor.h"

char	*ft_strjoin2(char *s1, char *s2)
{
	char	*ret;
	char	*cp_ret;
	char	*cp_s;

	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (s2);
	ret = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!ret)
		return (NULL);
	cp_ret = ret;
	cp_s = s1;
	while (*cp_s)
		*cp_ret++ = *cp_s++;
	cp_s = s2;
	while (*cp_s)
		*cp_ret++ = *cp_s++;
	*cp_ret = '\0';
	free(s1);
	return (ret);
}

char	**ft_getpath(char *keypairs[], char *cmd)
{
	int		i;
	char	*keypair;
	char	**path;

	i = 0;
	keypair = NULL;
	path = NULL;
	while (keypairs[i++])
	{
		keypair = ft_strnstr(keypairs[i], "PATH=/", 6);
		if (keypair != NULL)
		{
			keypair = ft_strnstr(keypair, "/", 6);
			path = ft_split(keypair, ':');
			break ;
		}
	}
	i = 0;
	while (path[i])
	{
		path[i] = ft_strjoin2(path[i], "/");
		path[i] = ft_strjoin2(path[i], cmd);
		i++;
	}
	return (path);
}

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

bool	is_builtin(char	*cmd)
{
	if (!ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "echo")
		|| !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd, "env")
		|| !ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset")
		|| !ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "export"))
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
	path = ft_getpath(g_data.env, cmd);
	while (path[i])
	{
		if (access(path[i], F_OK | X_OK) == 0)
			res = true;
		i++;
	}
	if (is_builtin(cmd))
		res = false;
	return (res);
}
