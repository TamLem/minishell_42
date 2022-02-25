/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:13:15 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/25 19:31:40 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XECUTOR_H
# define XECUTOR_H

int 	xecute(void);
char	**ft_getpath(char *keypairs[], char *cmd);
bool	check_cmds(char	*cmd);
bool	is_builtin(char	*cmd);
int		init_args(t_simple_cmd *simple_cmd, char ***arg_array);
int		ft_export(int argc, char *argv[], char *envp[]);
int		ft_env(int argc, char *argv[], char *envp[]);
int		ft_unset(int argc, char *argv[], char *envp[]);
int		ft_pwd(void);







enum FILE_DESCRIPTORS
{
	STDIN_INIT = 0,
	STDOUT_INIT = 1,
	IN = 2,
	OUT = 3,
};

#endif