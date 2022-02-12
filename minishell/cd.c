/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:52:36 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/10 21:52:39 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

with "cd" one can go directly to the path given with "cd"
with only a relative or absolute path. Handle both, absolute & relative path.

Cases to handle:
cd					-> does nothing
cd .				-> goes to the current directory
cd ./				-> goes to the current directory
cd ..				-> goes to the directory one before the current one
cd ../				-> goes to the directory one before the current one
cd / 				-> goes to root directory
cd NAMEofFILE/ 		-> goes to the directory specified
cd NAMEofFILE		-> goes to the directory specified

with multiple /../.. go up multiple directories till one reaches root
go directly to path NAMEofFILE/NAMEofFILE/NAMEofFILE

#include <unistd.h>

int	ft_cd(int argc, char **argv)
{
	if (chdir(*argv[0]) == " ")
		return (1);
	else if (chdir(*argv[0]) == "." || chdir(*argv[0]) == ".." || chdir(*argv[0]) == "/" 
		|| chdir(*argv[0]) == "./" || chdir(*argv[0]) == "../")
	return (0);
}

char	*getcwd(char *buf, size_t size);
returns a pointer pointing towards an char array where the path of the current working directory is stored in 

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
		go directly to path using: chdir() + const char *path;
	else
		if (input == ".." || input == "../")
			go out into path using: chdir() + const char *path;
}

void	cd(char **input)
{
	if (input == "cd")
		check(input);
}

int	main(int argc, char **argv)
{
	in input path should be checked
}
