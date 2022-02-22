/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xecutor.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tlemma <tlemma@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 16:13:15 by tlemma            #+#    #+#             */
/*   Updated: 2022/02/20 17:26:46 by tlemma           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef XECUTOR_H
# define XECUTOR_H

int 	xecute(void);
char	**ft_getpath(char *keypairs[], char *cmd);
int	check_cmds(char	*cmd);


#endif