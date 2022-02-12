/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlenoch <nlenoch@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 12:22:28 by nlenoch           #+#    #+#             */
/*   Updated: 2022/02/11 19:30:33 by nlenoch          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <unistd.h>

//        char *getcwd(char *buf, size_t size);

// copies absolute pathname of the current working directory 
// to the array pointed to by buf which is of length size

// if length of absolute pathname including the terminating NULL byte 
// exceeds the size bytes NULL is returned and erno is set to ERANGE
// an application should check for this error and allocate a larger buffer if necessary


//			int execve(const char *pathname, char *const argv[], char *const envp[]);

// executes the program referred to by pathname.
// causes the currently running program called by the process 
// to be replaced with a new program with newly initialized stack, heap and data segments

// pathname must be either a binary executable or a script starting with a line of the form

// argv is an array of pointers to strings passed to the new program as its command-line arguments
// the first of the strings (argv[0]) should contain the filename associated with the file being executed
// argv array must be terminated by a NULL pointer

// envp is an array of pointers to strings conventionally of the form key==value 
// which are passed as the environment of the new program. Must be NULL terminated.


void	ft_pwd(int argc, char **argv, char **env)
{
	if (argv[1] == "PWD")
		printf("%s", getcwd(env, size));
}
