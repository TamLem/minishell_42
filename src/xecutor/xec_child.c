/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xec_child.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/08 12:28:08 by tlemma            #+#    #+#             */
/*   Updated: 2022/03/11 15:49:14 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "xecutor.h"

void	child_exit(int signum)
{
	(void)signum;
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	exit(130);
}

int	exec_builtin(t_simple_cmd *simple_cmd)
{
	int		res;
	int		argc;
	char	**argv;
	char	**env;

	res = 0;
	argv = NULL;
	env = env_to_arr();
	argc = init_args(simple_cmd, &argv);
	if (ft_strcmp(argv[0], "cd") == 0)
		res = ft_cd(argc, argv, env);
	else if (ft_strcmp(argv[0], "echo") == 0)
		res = ft_echo(argc, argv);
	else if (ft_strcmp(argv[0], "env") == 0 && (ft_getenv("PATH")
			|| !err_handle(1, "", argv[0])))
		res = ft_env(argc, argv, env);
	else if (ft_strcmp(argv[0], "export") == 0)
		res = ft_export(argc, argv, env);
	else if (ft_strcmp(argv[0], "unset") == 0)
		res = ft_unset(argc, argv, env);
	else if (ft_strcmp(argv[0], "pwd") == 0)
		res = ft_pwd();
	else if (ft_strcmp(argv[0], "exit") == 0)
		res = ft_exit(argc, argv);
	return (res);
}

int	child_process(t_simple_cmd *simple_cmd)
{
	char	**path;
	char	**args;
	int		argc;
	int		res;
	char	**env;

	res = 0;
	args = NULL;
	env = env_to_arr();
	signal(SIGINT, child_exit);
	if (!check_cmds(simple_cmd->cmd))
	{
		err_handle(1, "", simple_cmd->cmd);
		exit (127);
	}
	path = ft_getpath(simple_cmd->cmd);
	argc = init_args(simple_cmd, &args);
	while (execve(*path, args, env) && *path)
		path++;
	free_dp(path);
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	return (res);
}
