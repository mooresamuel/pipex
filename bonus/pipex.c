/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: samoore <samoore@student.42london.com      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/15 16:03:31 by samoore           #+#    #+#             */
/*   Updated: 2024/01/22 12:16:22 by samoore          ###   ########.fr       */
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

void	parent(int fd[2], pid_t pid)
{
	close (fd[1]);
	dup2 (fd[0], STDIN_FILENO);
	close (fd[0]);
	waitpid(pid, NULL, 0);
}

void	final(char *file2, t_cmd *cmds, char *arg)
{
	int	file;

	if (!ft_strncmp(arg, "here_doc", 9))
		file = open (file2, O_CREAT | O_APPEND | O_RDWR, 0666);
	else
	{
		unlink (file2);
		file = open (file2, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
	}
	dup2 (file, STDOUT_FILENO);
	execve (cmds->path, cmds->cmd, NULL);
}

void	execute(t_cmd *cmds, char **argv, char *file2)
{
	int		in_file;
	int		fd[2];
	pid_t	pid;

	if (ft_strncmp(argv[1], "here_doc", 9))
	{
		in_file = open(argv[1], O_RDONLY);
		close (0);
		dup2 (in_file, STDIN_FILENO);
		close (in_file);
	}
	else
		here_doc(argv[2]);
	while (cmds->next)
	{
		pipe (fd);
		pid = fork ();
		if (pid == 0)
			child (cmds->path, cmds->cmd, fd);
		else
			parent(fd, pid);
		cmds = cmds->next;
	}
	final (file2, cmds, argv[1]);
}

int	main(int argc, char **argv)
{
	t_cmd	*cmds;

	cmds = NULL;
	if (argc < 5)
	{
		write(2, "Invalid number of parameters\n", 29);
		exit (1);
	}
	if (ft_strncmp(argv[1], "here_doc", 9))
		cmds = get_commands(argc, argv, 2);
	else
		cmds = get_commands(argc, argv, 3);
	parse_input(argc, argv, cmds);
	execute(cmds, argv, argv[argc - 1]);
	free_cmds(cmds);
}
