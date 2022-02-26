/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:52:36 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/26 17:21:06 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"
#include "minishell.h"

int	ft_cd(int argc, char **argv, char **envp)
{
	int			dir;
	char		*path;
	char		*oldpath;

	dir = 0;
	path = argv[1];
	oldpath = getcwd(NULL, 0);
	if (argc == 1)
		path = "~";
	if (!ft_strcmp(path, "~"))
	{
		path = getenv("HOME");
		dir = chdir(path);
	}
	else if (!ft_strcmp(path, "-"))
	{
		path = ft_getenv_value("OLDPWD");
		if(path && !chdir(path))
			printf("%s\n", path);
	}
	else
		dir = chdir(path);
	if (dir == -1)
			dprintf(2, "%s No such file or directory", path);
	else
		add_env("OLDPWD", oldpath);
	return (1);
}