/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:03:31 by samoore           #+#    #+#             */
/*   Updated: 2024/01/19 14:54:39 by samoore          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	child(char *path, char **cmd, int fd[2])
{
	close (fd[0]);
	dup2 (fd[1], STDOUT_FILENO);
	close (fd[1]);
	execve (path, cmd, NULL);
}

void	parent(int fd[2])
{
	close (fd[1]);
	dup2 (fd[0], STDIN_FILENO);
	close (fd[0]);
	waitpid(0, NULL, 0);
}

void	final(char *file2, t_cmd *cmds)
{
	int	file;

	unlink (file2);
	file = open (file2, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	dup2 (file, STDOUT_FILENO);
	execve (cmds->path, cmds->cmd, NULL);
	close (file);
}

void	execute(t_cmd *cmds, char *input_file, char *file2)
{
	int		in_file;
	int		fd[2];

	in_file = open(input_file, O_RDONLY);
	close (0);
	dup2 (in_file, STDIN_FILENO);
	close (in_file);
	while (cmds->next)
	{
		pipe (fd);
		if ((fork ()) == 0)
			child (cmds->path, cmds->cmd, fd);
		else
			parent(fd);
		cmds = cmds->next;
	}
	final (file2, cmds);
}

int	main(int argc, char **argv)
{
	t_cmd	*cmds;

	cmds = NULL;
	if (argc != 5)
	{
		write(2, "Invalid number of parameters\n", 29);
		exit (1);
	}
	cmds = get_commands(argc, argv);
	parse_input(argc, argv, cmds);
	execute(cmds, argv[1], argv[argc - 1]);
	free_cmds(cmds);
}
