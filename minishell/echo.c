/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 12:22:51 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/01 18:51:38 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// string can be in "qotes" or without
// if string includes '$PWD' return print current working directory with rest of string
// if option '-n' do not print a newline

#include <stdio.h>
#include <stdlib.h>

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

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*uc1;
	unsigned char	*uc2;
	size_t			i;

	uc1 = (unsigned char *)s1;
	uc2 = (unsigned char *)s2;
	i = 0;
	if ((ft_strlen(s1) == 0 && ft_strlen(s2) == 0) || n == 0)
		return (0);
	if (ft_strlen(s1) == 0)
		return (-1);
	if (ft_strlen(s2) == 0)
		return (1);
	while ((i <= n && uc1[i] != '\0') || uc2[i] != '\0')
	{
		if ((uc1[i] == uc2[i] && i == n) || i == n)
			return (0);
		if (uc1[i] > uc2[i])
			return (1);
		if (uc1[i] < uc2[i])
			return (-1);
		i++;
	}
	return (0);
}

// void	expandable(char **input)
// {
// 	if (*input == "' '")
// 		printf("Not Expandable\n");
// 	if (*input == " ")
// 		printf("Expandable\n");

// if (input == "$")
// 		printf("GETENV: %s\n", getenv(*argv));

// 	printf("Expandable\n");
// 	if (*input == "?")
// 		printf("Expand to exit status\n");
// 	if (*input == "PWD")
// 		printf("Expand to print working directory\n");
// 	if (*input == "USER")
// 		printf("Expanda to username\n");
// }

void	echo(char **input)
{
	// if (ft_strncmp(*input, "./a.out echo -n", ft_strlen(*input)) == 0)
	// 	printf("ECHO -n CHECK\n");
	// else if (ft_strncmp(*input, "./a.out echo", ft_strlen(*input)) == 0)
	// 	printf("ECHO CHECK\n");
	// else
	// 	printf("FAILED\n");
	if (*input && ft_strncmp(*input, "-n", ft_strlen("-n") + 1) == 0)
	{
		printf("NO NEW LINE\n");
		while (*input && ft_strncmp(*input, "-n", ft_strlen("-n") + 1) == 0)
			input++;
	}
	else
	{
		while (*input && ft_strncmp(*input, "$", ft_strlen(*input)) != 0)
		{
			printf("%s", *input);
			if (*input && ft_strncmp(*input, "$", ft_strlen(*input)) == 0)
			{
				printf("COMMAND\n");
				// expandable(input);
			}
			input++;
		}
	}
}

int	main(int argc, char **argv)
{
	echo(argv);
	// if (argc == 2)
	// 	echo_try(argc, &argv[1]);
	// else if (argc == 3)
	// 	echo_try(argc, &argv[2]);
	return (0);
}
