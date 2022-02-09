/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:32:47 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/08 18:36:01 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// set export attribute for shell variables
// marks each NAME for automatic export to the environment 
// of subsequently executed commands

void	export(char **input)
{
	if (input == "export")
		return (error_msg);
	else if (input == "export name=smth")
		change the value of name to smth in the env;
}


