/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:52:36 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/08 12:22:08 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// void	cd_in(char **input)
// {
// 	if (input == "cd NAMEofFILE/" || input == "cd NAMEofFILE")
// 		open FILE;
// }

// void	cd_out(char **input)
// {
// 	if (input == "cd .." || input == "cd ../")
// 		get one back in directory;
// }
void	check(char **input)
{
	if (input == "/" || input == "." || input == "NAMEofFILE/" || input == "NAMEofFILE")
		go directly to path;
	else
		if (input == ".." || input == "../")
			go out into path;
}

void	cd(char **input)
{
	if (input == "cd")
		check(input);
}

int	main(int argc, char **argv)
{
	
}
