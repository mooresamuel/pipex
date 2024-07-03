/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/21 15:22:14 by samoore           #+#    #+#             */
/*   Updated: 2024/01/22 12:12:57 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*re_alloc(char *buf, int *size)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(*size * 2);
	while (i < *size)
	{
		res[i] = buf[i];
		i++;
	}
	free (buf);
	*size *= 2;
	return (res);
}

int	gnl(char **str)
{
	char	*buf;
	int		i;
	int		size;

	size = 128;
	i = 0;
	buf = malloc(size);
	write (1, "pipe heredoc> ", 14);
	read (0, &buf[i], 1);
	while (buf[i] != '\n')
	{
		i++;
		if (size < i + 1)
			buf = re_alloc(buf, &size);
		read (0, &buf[i], 1);
	}
	buf[i++] = '\n';
	buf[i] = 0;
	*str = buf;
	return (i);
}

void	get_input(int fd[2], char *delim)
{
	char	*str;
	int		bytes;

	close (fd[0]);
	bytes = 2;
	while (bytes > 1)
	{
		bytes = gnl(&str);
		if (!ft_strncmp(str, delim, 3))
			exit (0);
		write(fd[1], str, bytes);
	}
	close (fd[1]);
}

void	here_doc(char *delim)
{
	pid_t	pid;
	int		fd[2];

	pipe(fd);
	pid = fork ();
	if (pid == 0)
		get_input(fd, delim);
	else
		parent(fd, pid);
}
