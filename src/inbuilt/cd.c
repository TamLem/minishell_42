/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 18:52:36 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/18 15:43:24 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// with "cd" one can go directly to the path given with "cd"
// with only a relative or absolute path. Handle both, absolute & relative path.

// Cases to handle:
// cd					-> does nothing
// cd .				-> goes to the current directory
// cd ./				-> goes to the current directory
// cd ..				-> goes to the directory one before the current one
// cd ../				-> goes to the directory one before the current one
// cd / 				-> goes to root directory
// cd NAMEofFILE/ 		-> goes to the directory specified
// cd NAMEofFILE		-> goes to the directory specified

// with multiple /../.. go up multiple directories till one reaches root
// go directly to path NAMEofFILE/NAMEofFILE/NAMEofFILE


// int	ft_cd(int argc, char **argv)
// {
// 	if (chdir(*argv[0]) == " ")
// 		return (1);
// 	else if (chdir(*argv[0]) == "." || chdir(*argv[0]) == ".." || chdir(*argv[0]) == "/" 
// 		|| chdir(*argv[0]) == "./" || chdir(*argv[0]) == "../")
// 	return (0);
// }

// char	*getcwd(char *buf, size_t size);
// returns a pointer pointing towards an char array where the path of the current working directory is stored in 

// // void	cd_in(char **input)
// // {
// // 	if (input == "cd NAMEofFILE/" || input == "cd NAMEofFILE")
// // 		open FILE;
// // }

// // void	cd_out(char **input)
// // {
// // 	if (input == "cd .." || input == "cd ../")
// // 		get one back in directory;
// // }
// void	check(char **input)
// {
// 	if (input == "/" || input == "." || input == "NAMEofFILE/" || input == "NAMEofFILE")
// 		go directly to path using: chdir() + const char *path;
// 	else
// 		if (input == ".." || input == "../")
// 			go out into path using: chdir() + const char *path;
// }

// void	cd(char **input)
// {
// 	if (input == "cd")
// 		check(input);
// }

#include <unistd.h>
#include <stdio.h>

size_t	ft_strlen(const char *c)
{
	size_t	count;

	count = 0;
	while (*c != '\0')
	{
		count++;
		c++;
	}
	return (count);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*uc1;
	unsigned char	*uc2;
	size_t			i;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	i = 0;
	if ((ft_strlen(s1) == 0 && ft_strlen(s2) == 0))
		return (0);
	if (ft_strlen(s1) == 0)
		return (-1);
	if (ft_strlen(s2) == 0)
		return (1);
	while (uc1[i] != '\0' || uc2[i] != '\0')
	{
		if (uc1[i] == uc2[i])
			return (0);
		if (uc1[i] > uc2[i])
			return (1);
		if (uc1[i] < uc2[i])
			return (-1);
		i++;
	}
	return (0);
}


int	main(int argc, char **argv)
{
	// char *pwd;

	// printf("%s\n", getwd(pwd));
	if (ft_strcmp(argv[1], "cd") == 0)
	{
		chdir(argv[2]);
		// printf("%s\n", getwd(pwd));
	}
	return (0);
}
